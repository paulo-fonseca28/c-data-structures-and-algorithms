# Graph Algorithms in C

## Project Overview

This repository provides a modular C implementation of graph data structures and algorithms, focused on loading and processing edge-list formatted graphs for analysis and exploration. The project is suitable for research, portfolio, and educational use, offering flexible support for both directed and undirected graphs, weighted or unweighted. Developed in 2023 as part of my learning path in algorithms and C programming.

---

## Features

- Load graphs from plain text files with flexible edge formats
- User-prompt selection for directed or undirected graph interpretation
- Dynamic creation of vertices from string labels
- Edge support: add, remove, with optional weights
- Calculation of vertex degree, maximum degree, and average degree
- Connected components and largest component size (undirected)
- Dijkstra’s algorithm for shortest path and average shortest path length
- Robust CLI and memory management

---

## Project Structure

| File            | Description                                             |
|-----------------|--------------------------------------------------------|
| `graph.h`       | Header: data types, function declarations              |
| `graph.c`       | Graph structures, algorithm implementations            |
| `main.c`        | CLI, user interaction, program orchestration           |
| `macaques.edges`| Example edge-list file (see format below)              |

---

## Edge File Format: `macaques.edges`

This file serves as a practical demonstration for working with animal social network data (macaques):

**Accepted formats:**
- **Unweighted:** Two values per line: `LABEL_FROM LABEL_TO`
- **Weighted:** Three values per line: `LABEL_FROM LABEL_TO WEIGHT`

All vertices (nodes) are automatically created from encountered labels.

- If `WEIGHT` is omitted, the edge is treated with default weight `1.0` (unweighted).
- For weighted edges, supply a third value.

---

## How the Code Operates

- Vertices are mapped from string labels and created automatically.
- The user chooses whether the graph is **directed** (`1`) or **undirected** (`0`) on startup.
    - _Directed:_ Each line is a one-way edge (`from` to `to`).
    - _Undirected:_ Each line creates edges both ways (`from` to `to` and `to` to `from`).
- The loader supports `.edges` files containing either format, detecting the number of columns per line.

---

## Example Usage

**Compiling:**

```bash
gcc -Wall -Wextra -O2 -o graph main.c graph.c
```

**Running:**
```bash
./graph
```

**Session:**

Enter graph edge file ('label_from' 'label_to' [weight] per line): macaques.edges
Is the graph directed? (1=yes, 0=no): 0

--- Graph Menu ---

1. Show vertex degree
2. Remove edge
3. Show connected components
4. Show max degree
5. Show average degree
6. Show average shortest path
7. Exit

---

## Data Structures

Graph is represented as a list of adjacency lists with string labels for each vertex:

```c
typedef struct AdjNode {
int vertex;
float weight;
struct AdjNode* next;
} AdjNode;
```

Labels are mapped to indices for efficient lookup and printing.

---

## Learning Outcomes

- Advanced handling of strings, pointers, and dynamic memory in C
- Modular programming and separation of interface, implementation, and CLI
- In-depth graph analytics: degree, connectivity, shortest paths
- Support for scientific and exploratory analysis of network data
- Clear documentation for professional/project portfolio or open-source contribution

---

## Possible Improvements

- Better input validation (duplicate/invalid edges or nodes)
- Exporting/loading graph states and results
- Integration with visualization libraries/tools (ASCII or external)
- Additional graph algorithms: centrality, BFS, DFS, Minimum Spanning Tree
- Customizable weight interpretation (e.g., negative weights, transforms)

---

## Author

Paulo Fonseca  
Information Systems student, Universidade Federal de Uberlândia  
GitHub: [github.com/paulo-fonseca28](https://github.com/paulo-fonseca28)
