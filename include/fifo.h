#ifndef FIFO_H
#define FIFO_H

/*
    fifo.h - A generic FIFO queue implementation
    --------------------------------------------
*/

#include <stdlib.h>
#include <string.h>

// Forward declaration for Node
struct Node;

typedef struct Node{
    void *data; // Generic data that can be casted
    struct Node *next; // Pointer to the next node
}Node;

typedef struct Fifo{
    Node *front;
    Node *rear;
}Fifo;

/*
    init_fifo - Sets the initial node for the fifo in memory and returns a pointer to it
*/
Fifo *init_fifo();

/*
    enqueue - enqueues a new node to the rear of the given queue with the specified value

    val is a pointer data of any type
    val_size is the size of the pointed data

    memory is dynamically allocated for data, it should be freed while dequeueing
*/
void enqueue(Fifo *q, void* val, size_t val_size);

/*
    dequeue - dequeues a node from the front of the given queue
*/
void dequeue(Fifo *q);

/*
    peek - peek and get the element at the front of the queue

        Returns: A void pointer that can be casted to the wanted type.
*/
void *peek(Fifo *q);

/*
    free_fifo - Free all allocated memory for all elements and data of the given queue
*/
void free_fifo(Fifo *q);

#endif