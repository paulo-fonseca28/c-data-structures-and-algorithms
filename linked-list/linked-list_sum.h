#ifndef LINKED_LIST_SUM_H
#define LINKED_LIST_SUM_H

typedef struct Node {
    int val;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    Node *tail;
} List;

/* Funções de lista genéricas */
List *createList(void);
Node *createNode(int value);
void insertAtEnd(List *list, int value);
void freeList(List *list);
void printList(const List *list);

/* Funções específicas do problema */
int listToInteger(const List *list);
int addTwoNumbers(const List *l1, const List *l2);
List *integerToList(int number);

#endif /* LINKED_LIST_SUM_H */