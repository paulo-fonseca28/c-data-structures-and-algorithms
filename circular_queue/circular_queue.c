#include "circular_queue.h"
#include <stdio.h>
#include <stdlib.h>

CircularQueue* createQueue(void) {
    CircularQueue* q = (CircularQueue*)malloc(sizeof(CircularQueue));
    if (!q) {
        printf("\nFailed to allocate memory for queue.\n");
        exit(EXIT_FAILURE);
    }
    q->head = q->tail = NULL;
    return q;
}

void enqueue(CircularQueue* q, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("\nFailed to allocate memory for node.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = value;
    if (!q->tail) { // queue is empty
        q->head = q->tail = newNode;
        newNode->next = newNode;
    } else {
        newNode->next = q->head;
        q->tail->next = newNode;
        q->tail = newNode;
    }
}

int dequeue(CircularQueue* q) {
    if (!q->head) {
        printf("\nQueue is empty.\n");
        return -1;
    }
    Node* temp = q->head;
    int value = temp->data;
    if (q->head == q->tail) { // single node
        q->head = q->tail = NULL;
    } else {
        q->head = q->head->next;
        q->tail->next = q->head;
    }
    free(temp);
    return value;
}

void printQueue(const CircularQueue* q) {
    if (!q->head) {
        printf("\nQueue is empty.\n");
        return;
    }
    Node* temp = q->head;
    do {
        printf("%d\n", temp->data);
        temp = temp->next;
    } while (temp != q->head);
    printf("\n");
}

void freeQueue(CircularQueue* q) {
    if (!q->head) {
        free(q);
        return;
    }
    Node* temp = q->head;
    Node* nextNode;
    do {
        nextNode = temp->next;
        free(temp);
        temp = nextNode;
    } while (temp != q->head);
    free(q);
    printf("Queue freed successfully!\n");
}
