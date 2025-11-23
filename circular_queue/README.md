# Circular Queue in C

## Project Overview

This repository implements a classic dynamically-linked **Circular Queue** (also called a circular linked-list queue) in C. It demonstrates how to efficiently manage FIFO (First-In-First-Out) data using pointer manipulation and dynamic memory allocation without wasting any memory slots, and is a great exercise for data structures and algorithms learning.

---

## Features

- Dynamically stores integer elements in a circular fashion (no fixed size)
- Supports insertion (`enqueue`) and removal (`dequeue`) in constant time
- Robust memory management (dynamic allocation and complete cleanup)
- Comprehensive error checks for memory allocation and queue state
- Modular, documented, and easy to read/modify C code
- Ready for extension: could be adapted for generic types or thread-safe contexts

---

## File Structure

| File                | Description                                            |
|---------------------|-------------------------------------------------------|
| `circular_queue.h`  | Header file: type definitions and function prototypes |
| `circular_queue.c`  | Source file: all queue logic and implementation       |
| `main.c`            | Example usage and test driver                         |

---

## How It Works

- The queue consists of **Nodes** connected in a circular singly-linked list.
- `enqueue()` adds a value to the back (tail); the node’s `next` pointer is always updated to keep the ring.
- `dequeue()` removes a value from the front (head); queue automatically loops when crossing the boundary.
- The queue is empty if the head pointer is `NULL`.

### Example Operations

- **Enqueue multiple values**
- **Print queue contents**
- **Dequeue (removes front element)**
- **Print updated queue**
- **Cleanup (frees all memory)**

---

## Example Usage

**Compiling:**

```bash
gcc -Wall -Wextra -O2 -o circular_queue main.c circular_queue.c
```

**Running:**

```bash
./circular_queue
```


---

## Learning Outcomes

- Dynamic pointer manipulation in C (linked structures)
- Managing circular data structures for efficient FIFO access
- Defensive programming: robust error checking and memory safety
- Modular code design (header/source separation)
- Clean coding standards for professional GitHub projects

---

## Possible Extensions

- Make queue generic using `void*`/templates or macros
- Add thread-safety (mutex locks for multi-threaded use)
- Add peek, isEmpty, length, or other utility functions
- Implement fixed-size (array-based) circular queue
- Create unit tests for all boundary cases

---

## Author

Paulo Fonseca  
Information Systems student, Universidade Federal de Uberlândia  
GitHub: [github.com/paulo-fonseca28](https://github.com/paulo-fonseca28)
