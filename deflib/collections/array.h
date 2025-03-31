#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>
#include <initializer_list>
#include <signal.h>
#include "../types.h"

/**
*  Copies n bytes from dest to src.
*  Essentially a custom memcpy().
*  @note Does not stop when encountering a null terminator.
*/
static void * copy_mem(void* dest, const void* src, u64 n) {
    u8* p1 = (u8*)dest;
    u8* p2 = (u8*)src;
    for(u64 i=0;i<n;i++) {
        p1[i] = p2[i];
    }
    return dest;
}
/**
 * Fills n bytes of dest with given byte.
 */
static void * fill_mem(void* dest, u8 byte, u64 n) {
    u8* ptr = (u8*)dest;
    for(u64 i=0;i<n;i++) {
        ptr[i] = byte;
    }
    return dest;
}

/**
 * Array class
 * Wrapper for any kind of array, but with memory safety and all that
 */
template<typename T>
class Array
{
public:
    /**
     * Creates an empty array.
     */
    Array<T>() {
        _arrptr = (T*)NULL;
        _cur = (T*)NULL;
        _count = 0;
    }
    /**
     * Creates an array the size of num_el.
     */
    Array<T>(u64 num_el) {
        _arrptr = (T*)NULL;
        while(_arrptr = (T*)malloc(num_el * sizeof(T)), _arrptr == NULL);
        fill_mem(_arrptr, 0x00, num_el * sizeof(T));
        _cur = _arrptr;
        _count = num_el;
    }
    /**
     * Creates an array by copying an existing one.
     */
    Array<T>(const Array<T>& arr) {
        _arrptr = (T*)NULL;
        while(_arrptr = (T*)malloc(arr._count * sizeof(T)), _arrptr == NULL);
        _cur = _arrptr + (arr._cur - arr._arrptr);
        _count = arr._count;
        fill_mem(_arrptr, 0x00, _count * sizeof(T));
        Copy_n(_arrptr, arr._cur, _count);
    }
    /**
     * Casts an array to another type.
     * @note Each element will be converted to the new type.
     */
    template<typename O>
    Array<T>(Array<O>& arr) {
        O* p = arr.ptr();
        u64 cnt = arr.count();

        _arrptr = (T*)NULL;
        while(_arrptr = (T*)malloc(cnt * sizeof(T)), _arrptr == NULL);
        _cur = _arrptr;
        _count = cnt;
        fill_mem(_arrptr, 0x00, _count * sizeof(T));
        for(int i=0;i<cnt;i++) {
            _arrptr[i] = (T)p[i];
        }
    }
    /**
     * Creates an array by wrapping around an existing C-Style array.
     * @note ptr should already be allocated via malloc/calloc.
     */
    Array<T>(u64 size, T* ptr) {
        _arrptr = ptr;
        _cur = ptr;
        _count = size;
    }
    /**
     * Creates an array by initializer list.
     * e.g. Array<int> arr = { 1, 2, 3 };
     * I genuinely have no idea how std does it here
     * TODO: Fucking get rid of stds entirely
     */
    Array<T>(std::initializer_list<T> list) : Array<T>(list.size()) {
        fill_mem(_arrptr, 0x00, _count * sizeof(T));
        const T* ptr = list.begin();
        for(int i=0;i<list.size();i++) {
            _arrptr[i] = *ptr++;
        }
    }
    /**
     * Destructor
     */
    ~Array<T>() {
        if(_arrptr != NULL) {
            free(_arrptr);
            _arrptr = (T*)NULL;
            _cur = (T*)NULL;
        }
    }

    friend Array<T> operator+(Array<T>& left, s64 right) {
        return left.subarray(right);
    }
    friend Array<T> operator+(s64 left, Array<T> right) {
        return right.subarray(left);
    }
    friend Array<T> operator-(Array<T>& left, s64 right) {
        return left.subarray(left._cur - left._arrptr - right);
    }
    friend Array<T> operator-(s64 left, Array<T>& right) {
        return right.subarray(right._cur - right._arrptr - left);
    }
    Array<T>& operator++() {
        _cur++;
        return *this;
    }
    Array<T>& operator++(int) {
        _cur++;
        return *this;
    }
    Array<T>& operator--() {
        _cur--;
        return *this;
    }
    Array<T>& operator--(int) {
        _cur++;
        return *this;
    }
    Array<T>& operator +=(s64 increase) {
        _cur += increase;
        return *this;
    }
    Array<T>& operator -=(s64 decrease) {
        _cur -= decrease;
        return *this;
    }
    T& operator[](s64 index) const {
        if(_cur + index >= _arrptr + _count || _cur + index < _arrptr) {
            raise(SIGSEGV);
        }
        return _cur[index];
    }
    T& operator*() {
        return *_cur;
    }
    Array<T>& operator=(Array<T> arr) {
        if(_arrptr != NULL) {
            free(_arrptr);
        }
        _arrptr = arr._arrptr;
        _cur = _arrptr;
        _count = arr._count;
        arr._arrptr = NULL;
        arr._cur = NULL;
        arr._count = 0;
        return *this;
    }
    /**
     * Returns the underlying C-Style pointer (T*).
     */
    T* ptr() { return _cur; }
    /**
     * Returns the amount of elements within this array.
     */
    u64 length() { return _count; }
    /**
     * Returns the amount of elements within this array.
     */
    u64 count() { return _count; }
    /**
     * Returns the total size of this array in Bytes.
     */
    u64 size() { return _count * sizeof(T); }
    /**
     * Fills array with 0x00 Bytes.
     * Returns the total amount of elements cleared.
     */
    u64 clear() {
        if(_arrptr == NULL || _count == 0) {
            return 0;
        }
        _cur = _arrptr;
        fill_mem(_cur, 0x00, _count * sizeof(T));
        return _count;
    }
    /**
     * Resets the current array pointer to the inital allocation position.
     */
    void resetPtr() {
        _cur = _arrptr;
    }

    /**
     * Extracts elements of this array starting at index start to the end.
     */
    Array<T> subarray(u64 start)  {
        if(start < 0 || start >= _count || _arrptr == NULL || _count <= 0) {
            return Array<T>();
        }
        u64 cnt = _count - start;
        Array<T> sub(cnt);
        copy_mem(sub._arrptr, _cur + start, cnt * sizeof(T));
        return sub;
    }
    /**
     * Extracts n elements of this array starting at index start.
     */
    Array<T> subarray(u64 start, u64 n) {
        if(start < 0 || start >= _count || _arrptr == NULL || _count <= 0) {
            return Array<T>();
        }
        if(n > _count - start) {
            n = _count - start;
        }
        Array<T> sub(n);
        copy_mem(sub._arrptr, _cur + start, n * sizeof(T));
        return sub;
    }
    /**
     * Reverses the contents of the array.
     * For all your endian needs.
     */
    Array<T> reverse() {
        Array<T> arr(_count);
        T* ptr = arr._cur;
        for(u64 i = 0; i < _count / 2; i++) {
            u64 right = _count - 1 - i;
            T tmp = ptr[i];
            ptr[i] = ptr[right];
            ptr[right] = tmp;
        }
        return arr;
    }

    /**
     * Reinterprets an array to an array of another type.
     * @note if the types aren't aligned, the last element will be discarded.
     * Will invalidate previous pointer! Only use in assignments!
     */
    template<typename O>
    Array<O> reinterpret() {
        Array<O> warr = Array<O>((_count * sizeof(T)) / sizeof(O), (O*)_cur);
        _arrptr = (T*)NULL;
        _cur = (T*)NULL;
        return warr;
    }
    /**
     * Copies an array and reinterprets its data to another type.
     * @note if the types aren't aligned, the last element will be discarded.
     */
    template<typename O>
    Array<O> reinterpretCopy() {
        Array<O> new_arr((_count * sizeof(T)) / sizeof(O));
        copy_mem(new_arr.ptr(), _cur, new_arr.count() * sizeof(O));
        return new_arr;
    }

    /**
    *  Copies n elements from dest to src.
    */
    static T* Copy_n(T* dest, const T* src, u32 n) {
        for(int i=0;i<n;i++) {
            dest[i] = src[i];
        }
        return dest;
    }
    /**
     * Copies n elements from an array into another.
     */
    static Array<T>& ArrayCopy(Array<T>& dest, const Array<T>& src, u64 n) {
        Copy_n(dest._arrptr, src._arrptr, n);
        return dest;
    }
    /**
     * Copies an array into another.
     * If dest < src, copy until dest full
     * If dest > src, copy until src fully copied
     */
    static Array<T>& ArrayCopy(Array<T>& dest, const Array<T>& src) {
        if(dest._cur == NULL || src._cur == NULL) {
            return dest;
        }
        u64 n = dest._count < src._count ? dest._count : src._count;
        for(int i=0;i<n;i++) {
            dest[i] = src[i];
        }
        return dest;
    }

private:
    T* _arrptr;
    T* _cur;
    u64 _count;
};

#endif // ARRAY_H
