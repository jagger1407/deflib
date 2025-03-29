#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include "../types.h"
#include "array.h"

#define LIST_INC_STEP 0x10

template<typename T>
class ArrayList {
public:
    /**
     * Creates an empty list.
     */
    ArrayList<T>() {
        _real_size = LIST_INC_STEP;
        _arrptr = NULL;
        while(_arrptr = (T*)malloc(_real_size * sizeof(T)), _arrptr == NULL);
        _count = 0;
    }
    /**
     * Creates a list by copying a given array.
     */
    ArrayList<T>(Array<T>& array) {
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
    ArrayList<T>(u64 element_size, T* ptr) {
        _arrptr = ptr;
        _real_size = element_size;
        _count = element_size;
    }
    /**
     * Creates a list with the specified size.
     */
    ArrayList<T>(u32 initial_size) {
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
    T operator[](u64 index) {
        if(index >= _count || index < 0) {
            raise(SIGSEGV);
        }
        return _arrptr[index];
    }

    /**
     * Resizes the List.
     * @note If new_size < count, elements will be truncated.
     */
    void resize(u64 new_size) {
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
        ArrayList<O> new_arr((_count * sizeof(T)) / sizeof(O));
        Array<O>::Copy_n(new_arr.ptr(), _arrptr, new_arr.count());
        return new_arr;
    }
    /**
     * Adds an element to the List.
     */
    void add(T element) {
        if(_count == _real_size) {
            resize(_real_size + LIST_INC_STEP);
        }
        _arrptr[_count] = element;
        _count++;
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
    T get(u64 index) {
        if(index >= _count || index < 0) {
            raise(SIGSEGV);
        }
        return _arrptr[index];
    }
    /**
     * Gets the total amount of elements in the list.
     * Same as length().
     */
    u64 count() {
        return _count;
    }
    /**
     * Gets the length of the list in elements.
     * Same as count().
     */
    u64 length() {
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
    u64 _count;
    u64 _real_size;
};

#endif // ARRAYLIST_H
