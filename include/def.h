#ifndef DEF_H
#define DEF_H

/*
    def.h - Definition of common macros and enums to be used throughout the system
*/

// Exit Codes
#define SUCCESS 0               // Successfully exited 
#define ERROR_GENERAL 1         // General Error
#define ERROR_ALLOC 2           // Failed to allocate memory
#define INDEX_OUT_OF_BOUNDS 3   // Tried to access an index out of bounds
#define NULL_DEREF 4            // Tried to dereference a NULL pointer

#endif