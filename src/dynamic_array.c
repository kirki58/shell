#include "dynamic_array.h"

Dynamic_Array *init_dynamic_array(size_t cap){
    char **arr = (char**) malloc(cap * sizeof(char*));  // Allocate memory for the internal storage (Free this later!!)

    // Early terminate and handle the error as needed externally
    if(arr == NULL){
        return NULL;
    }

    Dynamic_Array *dyn_arr = (Dynamic_Array*) malloc(sizeof(Dynamic_Array)); // Allocate memory for the dynamic array itself (Free this later!!)
    // Properly assign variables of dynamic array
    dyn_arr->arr = arr;
    dyn_arr->capacity = cap;
    dyn_arr->len = 0;

    return dyn_arr;
}

int dynamic_array_push(Dynamic_Array *dyn_arr, char *val)
{
    if(dyn_arr == NULL){ // Validation
        return NULL_DEREF;
    }

    // Firstly, check if the capacity of the array is fully used, if so reallocate the array to a bigger buffer
    if(!(dyn_arr->len < dyn_arr->capacity)){ // Using this condition felt safer than using dyn_arr->len == dyn_arr->capacity
        char** new_buf = (char**) realloc(dyn_arr->arr, dyn_arr->capacity * GROWTH_FACTOR * sizeof(char*));
        if(new_buf == NULL){ // The reallacotion failed, most probably because of insufficent memory
            return ERROR_ALLOC; // Note: Old buffer is not freed, it's still active to provide flexibility it must be manually freed.
        }

        dyn_arr->arr = new_buf; // The re-allocation succeeded update the arr pointer.
        dyn_arr->capacity *= GROWTH_FACTOR; // Expand the capacity
    }

    size_t val_len = strlen(val);
    char* val_heap = (char*) malloc(val_len + sizeof(char)); // + sizeof(char) accounts for '\0'
    if(val_heap == NULL){
        return ERROR_ALLOC;
    }

    strncpy(val_heap, val, val_len);
    val_heap[val_len] = '\0';

    dyn_arr->arr[dyn_arr->len] = val_heap;
    dyn_arr->len++;
    return SUCCESS;
}

void free_dynamic_array(Dynamic_Array *dyn_arr){
    if(dyn_arr == NULL || dyn_arr->arr == NULL){ // Validate the input before freeing memory
        return;
    }

    for (size_t i = 0; i < dyn_arr->len; i++)
    {
        free(dyn_arr->arr[i]);  // Free allocated heap for strings
    }
    
    free(dyn_arr->arr); // Free the buffer allocated for entire arr, all the capacity
    free(dyn_arr);      // Free the dynamic array itself
}
