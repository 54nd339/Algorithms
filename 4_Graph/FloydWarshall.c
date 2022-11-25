#include <stdio.h>
#include <stdlib.h>
typedef struct graph {
    int vertices, edges;
    int **adjMatrix;
} graph;

graph *createGraph(int vertices, int edges) {
    graph *g = malloc(sizeof(graph));
    g->vertices = vertices;
    g->adjMatrix = malloc(vertices * sizeof(int *));
    for (int i = 0; i < vertices; i++) {
        g->adjMatrix[i] = malloc(vertices * sizeof(int));
    }
    int src, dest, weight;
    for (int i = 0; i < edges; i++) {
        printf("Enter edge %d: ", i);
        scanf("%d %d %d", &src, &dest, &weight);
        g->adjMatrix[src][dest] = weight;
        g->adjMatrix[dest][src] = weight;
    }
    return g;
}
void printGraph(graph *g) {
    for (int i = 0; i < g->vertices; i++) {
        printf("Vertex %d is connected to: ", i);
        for (int j = 0; j < g->vertices; j++) {
            if (g->adjMatrix[i][j] != 0) {
                printf("%d (%d) ", j, g->adjMatrix[i][j]);
            }
        }
        printf("\n");
    }
}

void floyydWarshall(graph *g) {
    int **dist = malloc(g->vertices * sizeof(int *));
    for (int i = 0; i < g->vertices; i++) {
        dist[i] = malloc(g->vertices * sizeof(int));
        for (int j = 0; j < g->vertices; j++)
            dist[i][j] = g->adjMatrix[i][j];
    }
    for (int k = 0; k < g->vertices; k++) {
        for (int i = 0; i < g->vertices; i++) {
            for (int j = 0; j < g->vertices; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
    for (int i = 0; i < g->vertices; i++) {
        for (int j = 0; j < g->vertices; j++) {
            printf("%d ", dist[i][j]);
        }
        printf("\n");
    }
}
int main() {
    printf("Enter number of vertices: ");
    int vertices; scanf("%d", &vertices);
    printf("Enter number of edges: ");
    int edges; scanf("%d", &edges);
    graph *g = createGraph(vertices, edges);

    printf("\nGraph:\n");
    printGraph(g);
    printf("\nFloyd-Marshall:\n");
    floyydMarshall(g);
    return 0;
}

/*
Enter number of vertices: 4
Enter number of edges: 5
Enter edge 0: 0 1 5
Enter edge 1: 0 3 10
Enter edge 2: 1 2 3
Enter edge 3: 2 3 1
Enter edge 4: 3 1 2

Graph:
Vertex 0 is connected to: 1 (5) 3 (10)
Vertex 1 is connected to: 0 (5) 2 (3) 3 (2)
Vertex 2 is connected to: 1 (3) 3 (1)
Vertex 3 is connected to: 0 (10) 1 (2) 2 (1)

Floyd-Marshall:
0 5 8 9
5 0 3 5
8 3 0 1
9 5 1 0
*/