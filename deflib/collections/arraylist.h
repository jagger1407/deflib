#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include "../types.h"
#include "array.h"

#define LIST_INC_START 0x10

template<typename T>
class ArrayList {
public:
    /**
     * Creates an empty list.
     */
    ArrayList<T>() {
        _inc = LIST_INC_START;
        _real_size = _inc;
        _arrptr = NULL;
        while(_arrptr = (T*)malloc(_real_size * sizeof(T)), _arrptr == NULL);
        _count = 0;
    }
    /**
     * Creates a list by copying a given array.
     */
    ArrayList<T>(Array<T>& array) {
        _inc = LIST_INC_START;
        _real_size = array.count();
        _arrptr = NULL;
        while(_arrptr = (T*)malloc(_real_size * sizeof(T)), _arrptr == NULL);
        Array<T>::Copy_n(_arrptr, array.ptr(), _real_size);
        _count = array.count();
    }
    /**
     * Creates a list by wrapping around an existing pointer.
     * @note Pointer needs to be allocated via malloc/calloc.
     */
    ArrayList<T>(s64 element_size, T* ptr) {
        _inc = LIST_INC_START;
        _arrptr = ptr;
        _real_size = element_size;
        _count = element_size;
    }
    /**
     * Creates a list with the specified size.
     */
    ArrayList<T>(s64 initial_size) {
        _inc = LIST_INC_START;
        _real_size = initial_size;
        _arrptr = NULL;
        while(_arrptr = (T*)malloc(_real_size * sizeof(T)), _arrptr == NULL);
        fill_mem(_arrptr, 0x00, initial_size * sizeof(T));
        _count = 0;
    }
    /**
     * Creates a list by copying an existing one.
     */
    ArrayList<T>(const ArrayList<T>& list) {
        _inc = list._inc;
        _real_size = list._real_size;
        _arrptr = NULL;
        while(_arrptr = (T*)malloc(_real_size * sizeof(T)), _arrptr == NULL);
        Array<T>::Copy_n(_arrptr, list._arrptr, list._count);
        _count = list._count;
    }
    /**
     * Casts a list to another type.
     * @note Each element will be converted to the new type.
     */
    template<typename O>
    ArrayList<T>(ArrayList<O>& list) {
        O* p = list.ptr();
        u64 cnt = list.count();
        _inc = LIST_INC_START;
        _arrptr = NULL;
        while(_arrptr = (T*)malloc(cnt * sizeof(T)), _arrptr == NULL);
        _count = cnt;
        fill_mem(_arrptr, 0x00, _count * sizeof(T));
        for(int i=0;i<cnt;i++) {
            _arrptr[i] = (T)p[i];
        }
    }
    /**
     * Destructor.
     */
    ~ArrayList<T>() {
        if(_arrptr != NULL) {
            free(_arrptr);
            _arrptr = NULL;
        }
        _real_size = 0;
        _count = 0;
    }

    ArrayList<T>& operator=(ArrayList<T> list) {
        if(_arrptr != NULL) {
            free(_arrptr);
        }
        _real_size = list._real_size;
        _arrptr = NULL;
        while(_arrptr = (T*)malloc(_real_size * sizeof(T)), _arrptr == NULL);
        Array<T>::Copy_n(_arrptr, list._arrptr, list._count);
        _count = list._count;
        return *this;
    }
    ArrayList<T>& operator+=(T element) {
        add(element);
        return *this;
    }
    T& operator[](s64 index) {
        if(index >= _count || index < 0) {
            raise(SIGSEGV);
        }
        return _arrptr[index];
    }
    bool operator==(const Array<T>& arr) {
        if(_arrptr == arr._arrptr) {
            return true;
        }
        if(_count != arr._count) {
            return false;
        }
        if(_arrptr == NULL || arr._arrptr == NULL) {
            return false;
        }
        for(int i=0;i<_count;i++) {
            if(_arrptr[i] != arr._cur[i]) {
                return false;
            }
        }
        return true;
    }

    /**
     * Resizes the List.
     * @note If new_size < count, elements will be truncated.
     */
    void resize(s64 new_size) {
        _real_size = new_size;
        T* new_ptr = NULL;
        while(new_ptr = (T*)realloc(_arrptr, new_size * sizeof(T)), new_ptr == NULL);
        _arrptr = new_ptr;
        if(new_size < _count) {
            _count = new_size;
        }
    }

    /**
     * Copies the data of the List into an Array.
     */
    Array<T> copyToArray() {
        Array<T> a(_count);
        Array<T>::Copy_n(a.ptr(), _arrptr, _count);
        return a;
    }
    /**
     * Converts the List into an Array.
     * @note Will invalidate this List object! Only use in assignments.
     */
    Array<T> convertToArray() {
        Array<T> a(_count, _arrptr);
        _arrptr = NULL;
        return a;
    }
    /**
     * Reinterprets the List into another type.
     * @note Warning! Will invalidate previous pointer!
     * Only use in assignments.
     */
    template<typename O>
    ArrayList<O> reinterpret() {
        ArrayList<O> list((_count * sizeof(T)) / sizeof(O), (O*)_arrptr);
        _arrptr = NULL;
        return list;
    }
    /**
     * Copies a list and reinterprets its data to another type.
     * @note if the types aren't aligned, the last element will be discarded.
     */
    template<typename O>
    ArrayList<O> reinterpretCopy() {
        s64 new_size = (_count * sizeof(T)) / sizeof(O);
        ArrayList<O> new_arr(new_size);
        for(int i=0;i<new_size;i++) {
            new_arr.add(((O*)_arrptr)[i]);
        }
        return new_arr;
    }
    /**
     * Adds an element to the List.
     */
    void add(T element) {
        if(_count == _real_size) {
            resize(_real_size + _inc);
            _inc *= 2;
        }
        _arrptr[_count] = element;
        _count++;
    }
    /**
     * Removes an element from the List.
     */
    T remove(s64 index) {
        if(index < 0 || _arrptr == NULL || _count == 0) {
            return (T)NULL;
        }
        T el = _arrptr[index];
        if(index == _count-1) {
            _arrptr[index] = (T)NULL;
            return el;
        }
        Array<T> arr(_count - index - 1);
        copy_mem(arr.ptr(), _arrptr + index + 1, arr.size());
        copy_mem(_arrptr + index, arr.ptr(), arr.size());
        _count--;
        return el;
    }
    /**
     * Removes all elements from the List.
     * @note doesn't resize the list.
     */
    void clear() {
        fill_mem(_arrptr, 0x00, _real_size);
        _count = 0;
    }
    /**
     * Gets the element with the specified index.
     */
    T get(s64 index) {
        if(index >= _count || index < 0) {
            raise(SIGSEGV);
        }
        return _arrptr[index];
    }
    /**
     * Reverses the contents of the array.
     * For all your endian needs.
     */
    ArrayList<T> reverse() {
        ArrayList<T> arr(_count);
        T* ptr = arr._arrptr;
        for(s64 i = 0; i < _count / 2; i++) {
            s64 right = _count - 1 - i;
            T tmp = ptr[i];
            ptr[i] = ptr[right];
            ptr[right] = tmp;
        }
    }
    /**
     * Extracts elements of this array starting at index start to the end.
     */
    ArrayList<T> subarray(s64 start)  {
        if(start < 0 || start >= _count || _arrptr == NULL || _count <= 0) {
            return ArrayList<T>();
        }
        u64 cnt = _count - start;
        Array<T> sub(cnt);
        copy_mem(sub._arrptr, _arrptr + start, cnt * sizeof(T));
        return sub;
    }
    /**
     * Extracts n elements of this array starting at index start.
     */
    ArrayList<T> subarray(s64 start, s64 n) {
        if(start < 0 || start >= _count || _arrptr == NULL || _count <= 0) {
            return ArrayList<T>();
        }
        if(n > _count - start) {
            n = _count - start;
        }
        ArrayList<T> sub(n);
        copy_mem(sub._arrptr, _arrptr + start, n * sizeof(T));
        return sub;
    }

    /**
     * Checks whether the list contains the given value.
     * @note uses operator==().
     */
    bool contains(T value) {
        for(int i=0;i<_count;i++) {
            if(_arrptr[i] == value) {
                return true;
            }
        }
        return false;
    }

    /**
     * Finds the index of a given value.
     * @note returns -1 if no value was found.
     * uses operator==().
     */
    s64 indexOf(T value) {
        if(_arrptr == NULL || _count == 0) {
            return -1;
        }
        for(int i=0;i<_count;i++) {
            if(_arrptr[i] == value) {
                return i;
            }
        }
        return -1;
    }

    /**
     * Checks whether this list is empty.
     * For the very lazy.
     */
    bool isEmpty() {
        return _count == 0;
    }

    /**
     * Gets the total amount of elements in the list.
     * Same as length().
     */
    s64 count() {
        return _count;
    }
    /**
     * Gets the length of the list in elements.
     * Same as count().
     */
    s64 length() {
        return _count;
    }
    /**
     * Gets the total size of the list in bytes.
     */
    u64 size() {
        return _count * sizeof(T);
    }
    /**
     * Returns the underlying C-Style pointer (T*).
     */
    T* ptr() {
        return _arrptr;
    }
private:
    T* _arrptr;
    s64 _count;
    s64 _real_size;
    s64 _inc;
};

#endif // ARRAYLIST_H
