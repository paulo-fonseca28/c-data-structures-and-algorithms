#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void expandCapacity(Graph* g);

Graph* createGraph() {
    Graph* g = malloc(sizeof(Graph));
    g->numVertices = 0;
    g->capacity = INITIAL_CAPACITY;
    g->labels = malloc(g->capacity * sizeof(char*));
    g->adjLists = malloc(g->capacity * sizeof(AdjNode*));
    for (int i = 0; i < g->capacity; ++i) {
        g->adjLists[i] = NULL;
        g->labels[i] = NULL;
    }
    return g;
}

void freeGraph(Graph* g) {
    if (!g) return;
    for (int i = 0; i < g->numVertices; ++i) {
        free(g->labels[i]);
        AdjNode* curr = g->adjLists[i];
        while (curr) {
            AdjNode* tmp = curr;
            curr = curr->next;
            free(tmp);
        }
    }
    free(g->labels);
    free(g->adjLists);
    free(g);
}

static void expandCapacity(Graph* g) {
    int newCap = g->capacity * 2;
    g->labels = realloc(g->labels, newCap * sizeof(char*));
    g->adjLists = realloc(g->adjLists, newCap * sizeof(AdjNode*));
    for (int i = g->capacity; i < newCap; ++i) {
        g->labels[i] = NULL;
        g->adjLists[i] = NULL;
    }
    g->capacity = newCap;
}

int addVertex(Graph* g, const char* label) {
    if (g->numVertices == g->capacity) expandCapacity(g);
    g->labels[g->numVertices] = strdup(label);
    g->adjLists[g->numVertices] = NULL;
    return g->numVertices++;
}

int addEdge(Graph* g, int from, int to, float weight) {
    if (from >= g->numVertices || to >= g->numVertices) return 0;
    AdjNode* node = malloc(sizeof(AdjNode));
    node->vertex = to;
    node->weight = weight;
    node->next = g->adjLists[from];
    g->adjLists[from] = node;
    return 1;
}

int removeEdge(Graph* g, int from, int to) {
    if (from < 0 || from >= g->numVertices || to < 0 || to >= g->numVertices) return -1;
    AdjNode **curr = &g->adjLists[from];
    while (*curr) {
        if ((*curr)->vertex == to) {
            AdjNode* tmp = *curr;
            *curr = tmp->next;
            free(tmp);
            return 1;
        }
        curr = &((*curr)->next);
    }
    return 0;
}

// Flexible loader for two or three columns
int loadGraphFromFile(Graph* g, const char* filename, int isDirected) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file '%s'\n", filename);
        return 1;
    }
    char line[256], labelFrom[MAX_LABEL_LEN], labelTo[MAX_LABEL_LEN];
    float weight;
    while (fgets(line, sizeof(line), file)) {
        int count = sscanf(line, "%s %s %f", labelFrom, labelTo, &weight);
        if (count < 2) continue;
        if (count == 2) weight = 1.0;
        int from = -1, to = -1;
        for (int i = 0; i < g->numVertices; ++i) {
            if (strcmp(g->labels[i], labelFrom) == 0) from = i;
            if (strcmp(g->labels[i], labelTo) == 0) to = i;
        }
        if (from == -1) from = addVertex(g, labelFrom);
        if (to == -1) to = addVertex(g, labelTo);
        addEdge(g, from, to, weight);
        if (!isDirected) addEdge(g, to, from, weight);
    }
    fclose(file);
    return 0;
}

int vertexDegree(const Graph* g, int v) {
    if (v < 0 || v >= g->numVertices) return -1;
    int count = 0;
    AdjNode* curr = g->adjLists[v];
    while (curr) {
        count++;
        curr = curr->next;
    }
    return count;
}

int maxDegree(const Graph* g, int* vertex) {
    int max = -1;
    *vertex = -1;
    for (int i = 0; i < g->numVertices; ++i) {
        int deg = vertexDegree(g, i);
        if (deg > max) {
            max = deg;
            *vertex = i;
        }
    }
    return max;
}

float averageDegree(const Graph* g) {
    int sum = 0;
    for (int i = 0; i < g->numVertices; ++i)
        sum += vertexDegree(g, i);
    return g->numVertices == 0 ? 0 : (float)sum / g->numVertices;
}

void dfs(const Graph* g, int v, bool* visited, int* size) {
    visited[v] = true;
    (*size)++;
    AdjNode* curr = g->adjLists[v];
    while (curr) {
        if (!visited[curr->vertex])
            dfs(g, curr->vertex, visited, size);
        curr = curr->next;
    }
}

void connectedComponents(const Graph* g, int* nComp, int* maxSize) {
    bool* visited = calloc(g->numVertices, sizeof(bool));
    *nComp = 0, *maxSize = 0;
    for (int i = 0; i < g->numVertices; ++i) {
        if (!visited[i]) {
            int size = 0;
            dfs(g, i, visited, &size);
            (*nComp)++;
            if (size > *maxSize) *maxSize = size;
        }
    }
    free(visited);
}

float dijkstra(const Graph* g, int origin) {
    int n = g->numVertices;
    float* dist = malloc(n * sizeof(float));
    bool* visited = calloc(n, sizeof(bool));
    for (int i = 0; i < n; i++) dist[i] = INF;
    dist[origin] = 0;
    for (int c = 0; c < n; ++c) {
        int u = -1;
        float minDist = INF;
        for (int i = 0; i < n; i++)
            if (!visited[i] && dist[i] < minDist) minDist = dist[i], u = i;
        if (u == -1) break;
        visited[u] = true;
        AdjNode* curr = g->adjLists[u];
        while (curr) {
            if (!visited[curr->vertex] && dist[curr->vertex] > dist[u] + curr->weight)
                dist[curr->vertex] = dist[u] + curr->weight;
            curr = curr->next;
        }
    }
    float sum = 0.0;
    int count = 0;
    for (int i = 0; i < n; ++i)
        if (i != origin && dist[i] < INF) sum += dist[i], count++;
    free(dist);
    free(visited);
    return count ? sum / count : INF;
}

float averageShortestPath(const Graph* g) {
    float total = 0;
    int valid = 0;
    for (int i = 0; i < g->numVertices; ++i) {
        float avg = dijkstra(g, i);
        if (avg < INF) total += avg, valid++;
    }
    return valid ? total / valid : INF;
}