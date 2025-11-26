#include <stdio.h>
#include <stdlib.h>
#include "linked-list_sum.h"

/* ================== Funções utilitárias ================== */

List *createList(void) {
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) {
        fprintf(stderr, "Erro ao alocar memoria para a lista.\n");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    list->tail = NULL;
    return list;
}

Node *createNode(int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Erro ao alocar memoria para o no.\n");
        exit(EXIT_FAILURE);
    }
    newNode->val = value;
    newNode->next = NULL;
    return newNode;
}

void insertAtEnd(List *list, int value) {
    if (list == NULL) return;

    Node *newNode = createNode(value);

    if (list->tail == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

void freeList(List *list) {
    if (list == NULL) return;

    Node *current = list->head;
    while (current != NULL) {
        Node *nextNode = current->next;
        free(current);
        current = nextNode;
    }
    free(list);
}

void printList(const List *list) {
    if (list == NULL || list->head == NULL) {
        printf("Lista vazia\n");
        return;
    }

    const Node *current = list->head;
    while (current != NULL) {
        printf("%d", current->val);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf(" -> NULL\n");
}

/* ================== Funções específicas do problema ================== */

int listToInteger(const List *list) {
    if (list == NULL || list->head == NULL) {
        return 0;
    }

    const Node *cur = list->head;
    int decimal = 1;
    int result = 0;

    while (cur != NULL) {
        result += cur->val * decimal;
        decimal *= 10;
        cur = cur->next;
    }

    return result;
}

int addTwoNumbers(const List *l1, const List *l2) {
    int n1 = listToInteger(l1);
    int n2 = listToInteger(l2);
    return n1 + n2;
}

List *integerToList(int number) {
    if (number < 0) {
        fprintf(stderr, "Numero negativo nao suportado nesta implementacao.\n");
        return NULL;
    }

    List *list = createList();

    if (number == 0) {
        insertAtEnd(list, 0);
        return list;
    }

    while (number > 0) {
        int digit = number % 10;
        insertAtEnd(list, digit);
        number /= 10;
    }

    return list;
}
