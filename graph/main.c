#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    Graph* g = createGraph();
    char filename[128];
    int isDirected = 1;
    printf("Enter graph edge file name: ");
    scanf("%127s", filename);

    printf("Is the graph directed? (1 = yes, 0 = no): ");
    scanf("%d", &isDirected);

    if (loadGraphFromFile(g, filename, isDirected)) {
        printf("Failed to load graph.\n");
        freeGraph(g);
        return 1;
    }

    int running = 1;
    while (running) {
        printf("\n--- Graph Menu ---\n"
               "1. Show vertex degree\n"
               "2. Remove edge\n"
               "3. Show connected components\n"
               "4. Show max degree\n"
               "5. Show average degree\n"
               "6. Show average shortest path\n"
               "0. Exit\nChoose option: ");
        int opt;
        scanf("%d", &opt);

        switch (opt) {
            case 1: {
                printf("Enter vertex label: ");
                char label[MAX_LABEL_LEN];
                scanf("%s", label);
                int index = -1;
                for (int i = 0; i < g->numVertices; ++i)
                    if (strcmp(g->labels[i], label) == 0) index = i;
                if (index == -1) printf("Vertex not found.\n");
                else printf("Degree of '%s': %d\n", label, vertexDegree(g, index));
                break;
            }
            case 2: {
                printf("Enter edge to remove ('label_from' 'label_to'): ");
                char labelFrom[MAX_LABEL_LEN], labelTo[MAX_LABEL_LEN];
                scanf("%s %s", labelFrom, labelTo);
                int u = -1, v = -1;
                for (int i = 0; i < g->numVertices; ++i) {
                    if (strcmp(g->labels[i], labelFrom) == 0) u = i;
                    if (strcmp(g->labels[i], labelTo) == 0) v = i;
                }
                int res = removeEdge(g, u, v);
                if (res == -1) printf("Invalid vertex.\n");
                else if (res == 0) printf("Edge not found.\n");
                else printf("Edge removed successfully.\n");
                break;
            }
            case 3: {
                int numComp, maxSize;
                connectedComponents(g, &numComp, &maxSize);
                printf("Connected components: %d\n", numComp);
                printf("Largest component size: %d\n", maxSize);
                break;
            }
            case 4: {
                int vertex;
                int maxDeg = maxDegree(g, &vertex);
                if (vertex == -1) printf("No vertices in graph.\n");
                else printf("Vertex '%s' has max degree %d\n", g->labels[vertex], maxDeg);
                break;
            }
            case 5: {
                printf("Average degree: %.2f\n", averageDegree(g));
                break;
            }
            case 6: {
                float avg = averageShortestPath(g);
                if (avg == INF) printf("No connected paths in graph.\n");
                else printf("Avg. shortest path: %.2f\n", avg);
                break;
            }
            case 0:
                running = 0;
                break;
            default:
                printf("Invalid option.\n");
        }
    }

    freeGraph(g);
    printf("Graph memory freed. Exiting...\n");
    return 0;
}