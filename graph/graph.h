#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

#define INITIAL_CAPACITY 10
#define INF 1e9
#define MAX_LABEL_LEN 64

typedef struct AdjNode {
    int vertex;
    float weight;
    struct AdjNode* next;
} AdjNode;

typedef struct {
    char** labels;
    AdjNode** adjLists;
    int numVertices;
    int capacity;
} Graph;

// Creation & Memory Management
Graph* createGraph();
void freeGraph(Graph* g);

// Vertex & Edge Operations
int addVertex(Graph* g, const char* label);
int addEdge(Graph* g, int from, int to, float weight);
int removeEdge(Graph* g, int from, int to);

// Loading from File
int loadGraphFromFile(Graph* g, const char* filename, int isDirected);

// Analysis & Algorithms
int vertexDegree(const Graph* g, int v);
int maxDegree(const Graph* g, int* vertex);
float averageDegree(const Graph* g);

void dfs(const Graph* g, int v, bool* visited, int* size);
void connectedComponents(const Graph* g, int* nComp, int* maxSize);

float dijkstra(const Graph* g, int origin);
float averageShortestPath(const Graph* g);

#endif // GRAPH_H
