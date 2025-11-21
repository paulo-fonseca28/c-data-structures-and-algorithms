# Huffman Coding (C Implementation)

## Project Overview
Huffman Coding is a classic greedy algorithm for lossless data compression. This project implements a console-based compressor and decompressor for text files in C, applying fundamental data structure concepts like binary trees and priority queues. Developed in 2023 as part of my learning path in algorithms and C programming.

---

## Features

- Analyze character frequency in input files
- Build and visualize a Huffman tree for compression
- Generate and assign prefix-free codes to each character
- Compress and decompress text files efficiently
- Display compression ratio and compare file sizes
- Graceful handling of edge cases (empty files, single-character files, etc.)
- Modular and beginner-friendly codebase

---

## How It Works

### Workflow

1. **Frequency Analysis**: Reads the input file and counts the occurrences of each character.
2. **Huffman Tree Construction**: Uses a priority queue (sorted array/min-heap) to combine least frequent nodes into a binary tree.
3. **Code Generation**: Traverses the tree recursively, assigning binary codes to each character.
4. **Compression**: Encodes the original content, writes a frequency header and bit-packed data to output.
5. **Decompression**: Reads the header, reconstructs the tree, and decodes the binary data back to text.

### Menu Options

- Compress file
- Decompress file
- Compare original and compressed file sizes
- Option to remove last generated files
- Robust error messages for invalid input or file access issues

---

## Project Structure

| File            | Contents                                                        |
|-----------------|-----------------------------------------------------------------|
| `main.c`        | User interface, menu logic, file orchestration                  |
| `huffman.c`     | Huffman tree management, encoding/decoding, file compression    |
| `huffman.h`     | Type definitions and function prototypes                        |
| Test files      | Example `.txt` files for running and benchmarking               |

---

## Example Data Structure

Huffman tree node:

```c
typedef struct node {
char character;
int frequency;
struct node *left, *right;
} Node;
```

Codes are stored in a lookup table (array of strings) indexed by character.

---

## Compilation & Execution

### Dependencies
- GCC (or compatible C compiler)
- Terminal / command line access

### How to Compile

```bash
gcc -Wall -Wextra -O2 -o huffman main.c huffman.c
```

### How to Run

Launch in terminal:

```bash
./huffman 
```

Follow the menu prompts to compress, decompress or compare files.

---

## Learning Outcomes

By developing this project, I practiced:

- Applying greedy algorithms in practical scenarios
- Building and traversing binary trees in C
- Dynamic memory allocation and management
- Using bitwise operations for file encoding and decoding
- Modular programming and separation of concerns
- Handling edge cases and user input validation
- Writing documentation and user-friendly command-line interfaces

---

## Possible Improvements & Next Steps

- Add visualization for Huffman tree (text/graphical output)
- Support for more file formats (binary, utf-8)
- Improve error handling and robustness
- Add unit tests and additional edge-case checks
- Refactor into multiple source files for even clearer separation
- Persist compression metadata for future compatibility
- Add benchmark and performance reports

---

## References

- [Wikipedia: Huffman coding](https://en.wikipedia.org/wiki/Huffman_coding)
- [Codecademy: Huffman Coding - Algorithm](https://www.codecademy.com/resources/docs/general/algorithm/huffman-coding)
- [Project Huffman Code - Scribd](https://www.scribd.com/document/841290191/Project-Huffman-Code-Final)

---

## Author

Paulo Fonseca  
Information Systems student, Universidade Federal de Uberlândia  
GitHub: [github.com/paulo-fonseca28](https://github.com/paulo-fonseca28)


