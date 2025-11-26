# Linked List Integer Sum in C

## Project Overview

This project implements a modular integer addition system using singly linked lists in C, where each node stores a single digit and numbers are represented in reverse order (least significant digit first). A small example program (`main.c`) demonstrates how to construct the lists, sum two numbers, and print both the integer and list representations.

## Features

- Singly linked list structure with head and tail pointers.
- Creation of empty lists and insertion of digits at the end.
- Conversion from a reversed-digit list to an integer.
- Conversion from an integer back to a reversed-digit linked list.
- Addition of two numbers represented as linked lists.
- Utility functions to print lists and free all allocated memory.

## Project Structure

- `linked-list_sum.h` – Type definitions (`Node`, `List`) and function declarations.
- `linked-list_sum.c` – Implementation of list operations, conversions, and integer sum.
- `main.c` – Example program to build lists, compute the sum, and display results.

## How the Number Representation Works

The key idea is that numbers are stored “ao contrário” (reversed):

- Each node stores a single digit (`0–9`) in `val`.
- The head of the list always stores the units (least significant digit).
- The next node stores the tens, then hundreds, and so on.

Example:

- The list `2 -> 0 -> 1 -> NULL` represents the number `102`:
  - First node: `2 * 1`   → units = 2  
  - Second node: `0 * 10` → tens = 0  
  - Third node: `1 * 100` → hundreds = 100  
  - Total: `102`

Similarly, the list `3 -> 0 -> 1 -> NULL` represents `103`.  
Adding these two lists yields the integer `205`, and the resulting list is `5 -> 0 -> 2 -> NULL` (5 units, 0 tens, 2 hundreds).

## Data Structures

The number is stored as a singly linked list with pointers to the first and last nodes:

```c
typedef struct Node {
int val; // digit (0–9)
struct Node *next; // next node
} Node;

typedef struct List {
Node *head; // first node (units)
Node *tail; // last node (most significant digit)
} List;
```


This design makes it easy to:

- Append digits at the end of the list while maintaining a pointer to the last node.
- Traverse the list starting from `head` to reconstruct the integer using positional weights `1, 10, 100, ...`.

## Core Functions

### Utility list operations

- `List *createList(void)`  
  Allocates and initializes an empty list (`head = tail = NULL`).

- `Node *createNode(int value)`  
  Creates a node containing the digit `value` with `next = NULL`.

- `void insertAtEnd(List *list, int value)`  
  Inserts a new node with digit `value` at the end of the list, updating `head` and `tail` appropriately.

- `void freeList(List *list)`  
  Iterates through all nodes, freeing each one, then frees the `List` structure.

- `void printList(const List *list)`  
  Prints the list in the format: d1 -> d2 -> ... -> NULL
  The first printed digit is always the least significant digit (units).

### Converting a list to an integer

```c
int listToInteger(const List *list);
```


- If the list is empty, returns `0`.
- Traverses the list starting at `head` with a `decimal` factor initialized to `1`.
- For each node:
  - Adds `cur->val * decimal` to the result.
  - Multiplies `decimal` by `10` for the next digit.

Because `decimal` starts at `1` and increases by powers of `10`, the first node contributes as units, the second as tens, the third as hundreds, and so on. This matches the reversed representation: list order is opposite to normal written order.

### Adding two numbers

```c
int addTwoNumbers(const List *l1, const List *l2);
```

- Converts each list to an integer using `listToInteger`.
- Returns the sum `n1 + n2`.
- Converting this sum back to a linked list is done with `integerToList`.

### Converting an integer to a list

```c
List *integerToList(int number);
```

- If `number < 0`, the implementation reports an error and returns `NULL` (negative numbers are not supported).
- If `number == 0`, creates a list containing a single node with digit `0`.
- For `number > 0`:
  - While `number > 0`:
    - Computes `digit = number % 10` (least significant digit).
    - Inserts `digit` at the end of the list with `insertAtEnd`.
    - Updates `number /= 10` to move to the next more significant digit.

Example with `number = 205`:

- Iteration 1: `digit = 5` → list: `5`
- Iteration 2: `digit = 0` → list: `5 -> 0`
- Iteration 3: `digit = 2` → list: `5 -> 0 -> 2`

The final list `5 -> 0 -> 2 -> NULL` represents `205` with the least significant digit first, consistent with the input lists.

## Example Usage

A typical `main.c` follows this flow:

1. Create two empty lists `l1` and `l2` with `createList()`.
2. Insert digits into each list with `insertAtEnd`, already in reversed order (units first).
3. Print the original lists using `printList`.
4. Compute the integer sum with `addTwoNumbers(l1, l2)`.
5. Convert the resulting integer into a list with `integerToList`.
6. Print the resulting list with `printList`.
7. Free all allocated memory using `freeList` for `l1`, `l2`, and the result list.

Compile and run, for example:

```bash
gcc -Wall -Wextra -O2 -o linked_list_sum main.c linked-list_sum.c
./linked_list_sum
```

## Learning Outcomes

- Practice implementing and using singly linked lists in C with both `head` and `tail` pointers.
- Understanding how to encode integers as sequences of digits inside dynamic data structures.
- Working with reversed digit representations and converting between list and integer forms.
- Improving dynamic memory management skills (allocation, traversal, and deallocation).

## Possible Improvements

- Implement digit-by-digit addition with carry directly on the lists, avoiding conversion to `int`, to support very large numbers.
- Handle lists of different lengths directly in the addition logic.
- Add subtraction, multiplication, and comparison for numbers represented as lists.
- Improve validation of digit values and error handling for invalid inputs.
- Create an interactive CLI for the user to input numbers and visualize both list and integer forms.

## Author

Paulo Fonseca  
Information Systems student, Universidade Federal de Uberlândia  
GitHub: [github.com/paulo-fonseca28](https://github.com/paulo-fonseca28)




