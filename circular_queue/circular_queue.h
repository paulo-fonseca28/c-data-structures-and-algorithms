#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct CircularQueue {
    Node* head;
    Node* tail;
} CircularQueue;

/**
 * Creates an empty circular queue.
 * @return Pointer to an empty queue, or NULL on failure.
 */
CircularQueue* createQueue(void);

/**
 * Inserts a value at the end of the queue.
 * @param q Pointer to the queue.
 * @param value Value to insert.
 */
void enqueue(CircularQueue* q, int value);

/**
 * Removes and returns the value at the front of the queue.
 * @param q Pointer to the queue.
 * @return The value at the front, or -1 if the queue is empty.
 */
int dequeue(CircularQueue* q);

/**
 * Prints all values in the queue (one per line).
 * @param q Pointer to the queue.
 */
void printQueue(const CircularQueue* q);

/**
 * Frees all memory consumed by the queue.
 * @param q Pointer to the queue.
 */
void freeQueue(CircularQueue* q);

#endif // CIRCULAR_QUEUE_H
