#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./dyn_array.c"

#define __concat_tokens(x, y) x ## y
#define __concat_tokens_fix(x, y) __concat_tokens(x, y)
#define for_each(type, item_name, arr, len, body) \
    for (int __concat_tokens_fix(idx_, __LINE__) = 0; __concat_tokens_fix(idx_, __LINE__) < len; __concat_tokens_fix(idx_, __LINE__)++) { \
        type item_name = arr[__concat_tokens_fix(idx_, __LINE__)]; \
        body; \
    } \

#define for_range(type, var_name, start, end, block) \
    for(type var_name = start; var_name < end; var_name++) \
        block; \

typedef struct todo_item {
    char* description;
    bool completed;
} todo_item;

decl_dyn_array(todo_dyn_array, todo_item*)

#define i8 int8_t
#define ui8 uint8_t
#define i16 int16_t
#define ui16 uint16_t
#define i32 int32_t
#define ui32 uint32_t
#define i64 int64_t
#define ui64 uint64_t
#define i128 int128_t
#define ui128 uint128_t
#define f32 float
#define f64 double


int main(void) {
    todo_dyn_array* ida = new_todo_dyn_array();
    todo_item item = {
        .completed = false,
        .description = "Do something"
    };
    todo_item item_2 = {
        .completed = false,
        .description = "Do something else"
    };
    todo_item item_3 = {
        .completed = false,
        .description = "What?"
    };

    todo_dyn_array_append(ida, &item);
    todo_dyn_array_append(ida, &item_2);
    todo_dyn_array_append(ida, &item_3);
    
    for_each(todo_item*, it, ida->data, ida->length, {
        printf("{ Completed %d, Description: \"%s\" } %d %d\n",
            it->completed,
            it->description,
            ida->length,
            ida->capacity
        );
    });
    
    exit(0);
}
