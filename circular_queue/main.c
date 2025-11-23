#include <stdio.h>
#include "circular_queue.h"

int main(void) {
    CircularQueue* queue = createQueue();

    enqueue(queue, 246);
    enqueue(queue, 42);
    enqueue(queue, 1);
    enqueue(queue, 934);
    enqueue(queue, 453);
    enqueue(queue, 4324);
    enqueue(queue, 4);
    enqueue(queue, 123);
    enqueue(queue, 1000);

    printf("Initial queue:\n");
    printQueue(queue);

    printf("Removed values: %d, %d, %d\n", dequeue(queue), dequeue(queue), dequeue(queue));

    enqueue(queue, 732);
    enqueue(queue, 435);

    printf("Queue after more enqueues:\n");
    printQueue(queue);

    freeQueue(queue);

    return 0;
}
