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
    // Firstly, check if the capacity of the array is fully used, if so reallocate the array to a bigger buffer
    if(!(dyn_arr->len < dyn_arr->capacity)){ // Using this condition felt safer than using dyn_arr->len == dyn_arr->capacity
        char** new_buf = (char**) realloc(dyn_arr->arr, dyn_arr->capacity * GROWTH_FACTOR * sizeof(char*));
        if(new_buf == NULL){ // The reallacotion failed, most probably because of insufficent memory
            return ERROR_ALLOC; // Note: Old buffer is not freed, it's still active to provide flexibility. It must be manually freed.
        }

        dyn_arr->arr = new_buf; // The re-allocation succeeded update the arr pointer.
        dyn_arr->capacity *= GROWTH_FACTOR; // Expand the capacity
    }

    size_t val_len = strlen(val);
    char *val_heap = (char*) malloc(val_len + sizeof(char)); // + sizeof(char) accounts for '\0'
    if(val_heap == NULL){
        return ERROR_ALLOC;
    }

    strncpy(val_heap, val, val_len);
    val_heap[val_len] = '\0';

    dyn_arr->arr[dyn_arr->len] = val_heap;
    dyn_arr->len++;
    return SUCCESS;
}

int dynamic_array_equalize(Dynamic_Array *dyn_arr, int should_finalize){
    char** new_buf;
    if(should_finalize){ // If should_finalize we should also allocate memory for NULL, which we will put at the end of the array
        new_buf = (char**) realloc(dyn_arr->arr, (dyn_arr->len + 1) * sizeof(char*) );
    }
    else{
        new_buf = (char**) realloc(dyn_arr->arr, dyn_arr->len * sizeof(char*));
    }

    if(new_buf == NULL){ // Check if we successfully re-allocated memory
        return ERROR_ALLOC;
    }

    
    //  Change dyn_arr, equalize it's capacity
    dyn_arr->arr = new_buf;

    if(should_finalize){ // If should_finalize we should put NULL at the end of the array, also incerement dyn_arr->len by 1
        dyn_arr->arr[dyn_arr->len] = NULL;  // Put NULL at the last element
        dyn_arr->len++;
    }

    dyn_arr->capacity = dyn_arr->len;
    return SUCCESS;
}

void free_dynamic_array(Dynamic_Array *dyn_arr)
{
    if(dyn_arr == NULL || dyn_arr->arr == NULL){ // Validate the input before freeing memory
        return;
    }

    for (size_t i = 0; i < dyn_arr->len; i++)
    {
        if(dyn_arr->arr[i]){ // Safetly check to avoid free(NULL)
            free(dyn_arr->arr[i]); // Free the heap allocated for the string
        }
    }
    
    free(dyn_arr->arr); // Free the buffer allocated for entire arr, all the capacity
    free(dyn_arr);      // Free the dynamic array itself
}
