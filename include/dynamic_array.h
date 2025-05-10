#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

/*
    A dynamic array implementation for strings, used to store tokens obtained from a line in shell's perspective.
*/

#include <stdlib.h>
#include <string.h>
#include "def.h"

#define GROWTH_FACTOR 2 // How much the array should grow in case of an overflow

#define DYNAMIC_ARRAY_FINALIZE 1 // The flag that specifies array should be finalized for dynamic_array_equalize
#define DYNAMIC_ARRAY_DO_NOT_FINALIZE 0 

typedef struct dynamic_array
{
    char** arr;         // A string array to store the tokens
    size_t capacity;    // The capacity of the array which is doubled in case of an overflow
    size_t len;         // The actual length of the array
}Dynamic_Array;

/*
    init_dynamic_array - Initializes a dynamic array with given initial size in memory and returns a pointer to it.
*/

Dynamic_Array *init_dynamic_array(size_t cap);

/* 
    dynamic_array_push - Pushes a value to the next available position of the dynamic array

        Returns: An exit code based on success and failure
*/
int dynamic_array_push(Dynamic_Array *dyn_arr, char* val);

/*
    dynamic_array_equalize - Shrinks the dynamic array's capacity to the size of it's length, getting rid of unused memory
    if should_finalize == 1 it puts a NULL at the end of the array.

        Returns: An exit code based on success and failure
*/
int dynamic_array_equalize(Dynamic_Array *dyn_arr, int should_finalize);

/*
    free_dynamic_array - Frees all allocated buffers that belongs to a dynamic array
*/
void free_dynamic_array(Dynamic_Array *dyn_arr);

#endif