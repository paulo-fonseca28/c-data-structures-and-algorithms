#include <stdio.h>
#include "linked-list_sum.h"

int main(void) {
    List *l1 = createList();
    insertAtEnd(l1, 1);
    insertAtEnd(l1, 0);
    insertAtEnd(l1, 2);

    List *l2 = createList();
    insertAtEnd(l2, 1);
    insertAtEnd(l2, 0);
    insertAtEnd(l2, 3);

    printf("Lista l1: ");
    printList(l1);

    printf("Lista l2: ");
    printList(l2);

    int soma = addTwoNumbers(l1, l2);
    printf("Resultado da soma (inteiro): %d\n", soma);

    List *sumList = integerToList(soma);
    printf("Resultado da soma (lista): ");
    printList(sumList);

    freeList(l1);
    freeList(l2);
    freeList(sumList);

    return 0;
}
