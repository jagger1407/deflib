#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>
#include "types.h"

#define TYPE template<typename T>

/**
 * @todo write docs
 */
TYPE
class Array
{
public:
    Array<T>() {
        _arr = NULL;
    }
    Array<T>(u32 num_el) {
        _arr = NULL;
        while(_arr = (T*)malloc(num_el * sizeof(T)), _arr == NULL);
        _cur = _arr;
        _count = num_el;
    }
    Array<T>(const Array<T>& arr) {
        _arr = NULL;
        while(_arr = (T*)malloc(arr._count * sizeof(T)), _arr == NULL);
        _cur = _arr;
        _count = arr._count;
        for(int i=0;i<_count;i++) {
            _arr[i] = arr._arr[i];
        }
    }
    ~Array<T>() {
        if(_arr != NULL) {
            free(_arr);
            _arr = NULL;
            _cur = NULL;
        }
    }

    Array<T>& operator+(s32 add) {
        Array<T> arr = Array<T>(*this);
        arr += add;
        return arr;
    }
    Array<T>& operator-(s32 sub) {
        Array<T> arr = Array<T>(*this);
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
        return _cur[index];
    }
    T& operator*() {
        return *_cur;
    }
    T* ptr() {
        return _cur;
    }

    u32 length() { return _count; }
private:
    T* _arr;
    T* _cur;
    u32 _count;
};

#endif // ARRAY_H
