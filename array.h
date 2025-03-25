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
        _count = num_el;
    }
    Array<T>(const Array<T>& arr) {
        _arr = NULL;
        while(_arr = (T*)malloc(arr._count * sizeof(T)), _arr == NULL);
        _count = arr._count;
        for(int i=0;i<_count;i++) {
            _arr[i] = arr._arr[i];
        }
    }
    ~Array<T>() {
        if(_arr != NULL) {
            free(_arr);
        }
    }

    T& operator[](u32 index) {
        return _arr[index];
    }

    u32 length() { return _count; }
private:
    T* _arr;
    u32 _count;
};

#endif // ARRAY_H
