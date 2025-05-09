#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

/*
    A dynamic array implementation for strings, used to store tokens obtained from a line in shell's perspective.
*/

#include <stdlib.h>
#include <string.h>
#include "def.h"

#define GROWTH_FACTOR 2 // How much the array should grow in case of an overflow

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
    free_dynamic_array - Frees all allocated buffers that belongs to a dynamic array
*/
void free_dynamic_array(Dynamic_Array *dyn_arr);

#endif