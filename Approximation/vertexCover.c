#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int V, E;
    int **adjMat;
} Graph;

Graph *createGraph(int V, int E) {
    Graph *G = (Graph *)malloc(sizeof(Graph));
    G->V = V; G->E = E;
    G->adjMat = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++) {
        G->adjMat[i] = calloc(V, sizeof(int));
    }
    return G;
}
void printGraph(Graph *G) {
    for (int i = 0; i < G->V; i++) {
        for (int j = 0; j < G->V; j++) {
            if (G->adjMat[i][j] != 0)
                printf("%d -> %d (%d)\n", i, j, G->adjMat[i][j]);
        }
    }
}

void vertexCover(Graph *G) {
    int *visited = calloc(G->V, sizeof(int));
    int *cover = calloc(G->V, sizeof(int));
    int count = 0;
    for (int i = 0; i < G->V; i++) {
        if (!visited[i]) {
            for (int j = 0; j < G->V; j++) {
                if (G->adjMat[i][j] != 0) {
                    visited[j] = 1;
                }
            }
            cover[count++] = i;
        }
    }
    printf("Vertex Cover: ");
    for (int i = 0; i < count; i++) {
        printf("%d ", cover[i]);
    }
    printf("\n");
}

int main() {
    printf("Enter number of vertices: ");
    int V; scanf("%d", &V);
    printf("Enter number of edges: ");
    int E; scanf("%d", &E);
    Graph *G = createGraph(V, E);
    printf("Enter edges (u v):\n");
    for (int i = 0; i < E; i++) {
        int u, v; scanf("%d %d %d", &u, &v);
        G->adjMat[u][v] = 1;
    }

    vertexCover(G);
    return 0;
}

/*
Enter number of vertices: 6
Enter number of edges: 8
Enter edges (u v):
0 1
0 2
0 3
1 2
1 3
2 3
3 4
4 5
Vertex Cover: 0 3 5
*/