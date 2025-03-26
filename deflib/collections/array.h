#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>
#include <initializer_list>
#include <signal.h>
#include "../types.h"

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
        _arrptr = NULL;
    }
    /**
     * Creates an array the size of num_el.
     */
    Array<T>(u32 num_el) {
        _arrptr = NULL;
        while(_arrptr = (T*)malloc(num_el * sizeof(T)), _arrptr == NULL);
        _cur = _arrptr;
        _count = num_el;
    }
    /**
     * Creates an array by copying an existing one.
     */
    Array<T>(const Array<T>& arr) {
        _arrptr = NULL;
        while(_arrptr = (T*)malloc(arr._count * sizeof(T)), _arrptr == NULL);
        _cur = _arrptr;
        _count = arr._count;
        for(int i=0;i<_count;i++) {
            _arrptr[i] = arr._arrptr[i];
        }
    }
    /**
     * Creates an array by wrapping around an existing C-Style array.
     */
    Array<T>(u32 size, const T* ptr) {
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
            _arrptr = NULL;
            _cur = NULL;
        }
    }

    Array<T> operator+(s32 add) {
        Array<T> arr = Array<T>(_count, _cur);
        arr += add;
        return arr;
    }
    Array<T> operator-(s32 sub) {
        Array<T> arr = Array<T>(_count, _cur);
        arr -= sub;
        return arr;
    }
    Array<T>& operator++() {
        _cur++;
        return *this;
    }
    Array<T>& operator--() {
        _cur--;
        return *this;
    }
    Array<T>& operator +=(s32 increase) {
        _cur += increase;
        return *this;
    }
    Array<T>& operator -=(s32 decrease) {
        _cur -= decrease;
        return *this;
    }
    T& operator[](u32 index) {
        if(index < 0 || index >= _count) {
            raise(SIGSEGV);
        }
        return _cur[index];
    }
    T& operator*() {
        return *_cur;
    }
    /**
     * Returns the underlying C-Style pointer (T*).
     */
    T* ptr() { return _cur; }
    /**
     * Returns the amount of elements within this array.
     */
    u32 length() { return _count; }
private:
    T* _arrptr;
    T* _cur;
    u32 _count;
};

#endif // ARRAY_H
