# Huffman Coding in C

## Overview

This repository contains an implementation of the Huffman coding algorithm in C, developed as part of my practical learning journey through classic data structures and algorithms in 2023. The main focus is on building a functional and well-organized compressor and decompressor for text files using lossless compression. [web:27][web:24]

## How Huffman Coding Works

Huffman coding is a greedy algorithm used for lossless data compression. It assigns shorter codes to more frequent characters and longer codes to less frequent ones, reducing the overall size of the encoded data. The key steps are:

- **Frequency Analysis:** Scan the input data to count the occurrence of each character.
- **Huffman Tree Construction:** Insert all characters as leaf nodes into a priority queue (min-heap) based on frequency. Repeatedly merge the two nodes with the lowest frequency into a new parent node, continuing until only one node (the root) remains.
- **Code Generation:** Traverse the tree to assign variable-length binary codes to each character—assigning '0' to a left branch and '1' to a right branch.
- **Encoding:** Replace each character in the input with its Huffman code to produce the compressed output.
- **Decoding:** The compressed file stores both the encoded data and a serialization of the tree. The decoder reconstructs the tree and uses it to map the binary codes back to the original characters. [web:31][web:32][web:34]

## Concepts and Techniques Applied

- Greedy Algorithms
- Binary Trees
- Priority Queues (Min-Heaps)
- Recursive Tree Traversal
- File I/O in C
- Bitwise Manipulation
- Prefix-Free Encoding

## What I Learned

- Applying greedy strategies for optimal solutions in tree-based algorithms
- Working with dynamic memory allocation and pointer-based data structures in C
- Handling edge cases, input validation, and organizing modular code in larger projects
- Using bitwise operations for custom file encoding and decoding
- Documenting code, building user-friendly CLIs, and debugging algorithmic logic

## Usage

### Compilation

```bash
gcc -o huffman main.c huffman.c
```


### Compressing a File

Run the program and select the “Compress” option when prompted. Provide the input and output filenames as requested.

### Decompressing a File

Select the “Decompress” option and provide the compressed file and the desired output filename.

## File Structure

- `main.c`: Command-line interface and orchestration of user interactions
- `huffman.c` / `huffman.h`: Huffman logic, tree handling, encoding/decoding functions
- Sample text files for testing

## References & Further Reading

- [Huffman coding on Wikipedia](https://en.wikipedia.org/wiki/Huffman_coding) [web:34]
- [Project report and algorithm analysis](https://www.scribd.com/document/841290191/Project-Huffman-Code-Final) [web:32]
- Classic textbooks and coursework exercises on data compression and greedy algorithms

