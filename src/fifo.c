#include "fifo.h"

Fifo *init_fifo(){
    Fifo* q = (Fifo*) malloc(sizeof(Fifo));

    // Both front and rear node pointers are assigned NULL at initialization.
    q->front = NULL;
    q->rear = NULL;

    return q;
}

void enqueue(Fifo *q, void *val, size_t val_size)
{
    Node *new = (Node*) malloc(sizeof(Node)); // Allocate memory for the new node

    new->data = malloc(val_size); // Allocate memory for the data

    memcpy(new->data, val, val_size); // Copy the contents of the given generic data to new->data 
    
    new->next = NULL;   // New node's next points to NULL since it will be the last in the linked list

    // If the queue is empty, than BOTH front and rear should point to the newly created node.
    if(q->front == NULL && q->rear == NULL){
        q->front = new;
        q->rear = new;
        return;
    }

    // Otherwise ONLY rear should point to the new node and front should stay the same.
    q->rear->next = new; // Add the new node to the linked list
    q->rear = new; // rear pointer should now point to the last element in the linked list
}

void dequeue(Fifo *q)
{
    // Early terminate in case of a queue underflow - There is nothing to dequeue
    if(q->front == NULL && q->rear == NULL){
        return;
    }

    Node *temp = q->front;  // Keep the pointer to the front pointer since we need to free it after dequeueing.

    // If there is only 1 element in the queue (front and rear points to the same thing other than NULL, which is checked above),
    // than assign both front and rear to NULL to empty the queue
    if(q->front == q->rear){
        q->front = NULL;
        q->rear = NULL;
    }
    // Otherwise, just perform usual dequeueing, moving the front pointer to point to the next element
    else{
        q->front = q->front->next;
    }

    // Free the unused memory of front's previous pointed location.
    free(temp->data);
    free(temp);
}

void *peek(Fifo *q)
{
    // Early-terminate the function when the queue itself or the front of the queue points to nothing. Return NULL pointer
    if(q == NULL){
        return NULL;
    }
    if(q->front == NULL){
        return NULL;
    }

    return q->front->data;
}

void free_fifo(Fifo *q)
{
    // Early-terminate if q is null;
    if(q == NULL){
        return;
    }

    // dequeue every node iteratively
    while (q->front != NULL)
    {
        dequeue(q);
    }

    // Free the queue itself
    free(q);
}