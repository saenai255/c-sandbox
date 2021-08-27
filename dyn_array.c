#ifndef DYN_ARRAY_IMPL
#define DYN_ARRAY_IMPL

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>

#define decl_dyn_array(S, T) \
    typedef struct S { \
        T* data; \
        int capacity; \
        int length; \
    } S; \
    \
    S* new_##S() { \
        S* arr = malloc(sizeof(S)); \
        arr->data = malloc(sizeof(T) * 2); \
        arr->capacity = 2; \
        arr->length = 0; \
        return arr; \
    } \
    \
    int S##_append(S* arr, T item) { \
        if (arr->capacity == arr->length) { \
            T* new_data = malloc(sizeof(T) * arr->capacity * 2); \
            for (int i = 0; i < arr->length; i++) { \
                new_data[i] = arr->data[i]; \
            } \
            free(arr->data); \
            arr->capacity *= 2; \
            arr->data = new_data; \
        } \
        \
        arr->data[arr->length] = item; \
        return arr->length++; \
    } \
    \
    bool S##_set(S* arr, T item, int idx) {\
        if (idx >= arr->length) { \
            return false; \
        } \
        \
        arr->data[idx] = item; \
        \
        return true; \
    } \
    \
    bool S##_remove(S* arr, int idx) { \
        if (idx >= arr->length) { \
            return false; \
        } \
        \
        for(int i = idx; i < arr->length - 1; i++) { \
            arr->data[i] = arr->data[i + 1]; \
        } \
        arr->length--; \
        return true; \
        \
    } \
    \
    int S##_find(const S* arr, const T item) { \
        for(int i = 0; i < arr->length; i++) { \
            if (arr->data[i] == item) { \
                return i; \
            } \
        } \
        \
        return -1; \
    } \
    \
    bool S##_remove_all(S* arr, const T item) { \
        int initial_len = arr->length; \
        int pos = S##_find(arr, item); \
        while(pos != -1) { \
            S##_remove(arr, pos); \
            pos = S##_find(arr, item); \
        } \
        \
        if (initial_len == arr->length) { \
            return false; \
        } \
        \
        return true; \
    } \
    \
    void S##_free(S* arr) { \
        free(arr->data); \
        free(arr); \
    } \

#endif
