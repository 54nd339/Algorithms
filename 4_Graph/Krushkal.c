#include <stdio.h>
#include <stdlib.h>

typedef struct dsu {
    int *parent;
    int *rank;
    int n;
} DSU;
typedef struct graph {
    int vertices, edges;
    int **adjMatrix;
} graph;

graph *createGraph(int vertices, int edges) {
    graph *g = (graph *)malloc(sizeof(graph));
    g->vertices = vertices;
    g->edges = edges;
    g->adjMatrix = (int **)malloc(sizeof(int *) * vertices);
    for (int i = 0; i < vertices; i++) {
        g->adjMatrix[i] = (int *)malloc(sizeof(int) * vertices);
        for (int j = 0; j < vertices; j++) {
            g->adjMatrix[i][j] = 0;
        }
    }
    int src, dest, weight;
    for (int i = 0; i < g->edges; i++) {
        printf("Enter Edge %d: ", i + 1);
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

DSU *createDSU(int n) {
    DSU *dsu = (DSU *)malloc(sizeof(DSU));
    dsu->parent = (int *)malloc(sizeof(int) * n);
    dsu->rank = (int *)malloc(sizeof(int) * n);
    dsu->n = n;
    for (int i = 0; i < n; i++) {
        dsu->parent[i] = i;
        dsu->rank[i] = 0;
    }
    return dsu;
}
int find(DSU *dsu, int x) {
    if (dsu->parent[x] != x) {
        dsu->parent[x] = find(dsu, dsu->parent[x]);
    }
    return dsu->parent[x];
}
void unionDSU(DSU *dsu, int x, int y) {
    int xRoot = find(dsu, x);
    int yRoot = find(dsu, y);
    if (dsu->rank[xRoot] < dsu->rank[yRoot]) {
        dsu->parent[xRoot] = yRoot;
    } else if (dsu->rank[xRoot] > dsu->rank[yRoot]) {
        dsu->parent[yRoot] = xRoot;
    } else {
        dsu->parent[yRoot] = xRoot;
        dsu->rank[xRoot]++;
    }
}

void Krushkal(graph *g) {
    DSU *dsu = createDSU(g->vertices);
    int **adjMatrix = g->adjMatrix;
    int minWeight = 0;
    for (int i = 0; i < g->vertices - 1; i++) {
        int minSrc, minDest, min = 9999;
        for (int j = 0; j < g->vertices; j++) {
            for (int k = 0; k < g->vertices; k++) {
                if (adjMatrix[j][k] != 0 && adjMatrix[j][k] < min) {
                    if (find(dsu, j) != find(dsu, k)) {
                        min = adjMatrix[j][k];
                        minSrc = j; minDest = k;
                    }
                }
            }
        }
        unionDSU(dsu, minSrc, minDest);
        printf("Edge %d: (%d, %d) cost: %d\n", i+1, minSrc, minDest, min);
        minWeight += min;
        adjMatrix[minSrc][minDest] = 0;
        adjMatrix[minDest][minSrc] = 0;
    }
    printf("Minimum Weight: %d\n", minWeight);
}
int main() {
    printf("Enter number of vertices: ");
    int vertices; scanf("%d", &vertices);
    printf("Enter number of edges: ");
    int edges; scanf("%d", &edges);
    graph *g = createGraph(vertices, edges);
    

    printf("\nGraph:\n");
    printGraph(g);
    
    printf("\nKrushkal:\n");
    Krushkal(g);
    return 0;
}
/*
Enter number of vertices: 4
Enter number of edges: 5
Enter edge 0: 0 1 10
Enter edge 1: 0 2 6
Enter edge 2: 0 3 5
Enter edge 3: 1 3 15
Enter edge 4: 2 3 4

Graph:
Vertex 0 is connected to: 1 (10) 2 (6) 3 (5)
Vertex 1 is connected to: 0 (10) 3 (15)
Vertex 2 is connected to: 0 (6) 3 (4)
Vertex 3 is connected to: 0 (5) 1 (15) 2 (4)

Krushkal:
Edge 1: (2, 3) cost: 4
Edge 2: (0, 3) cost: 5
Edge 3: (0, 1) cost: 10
Minimum cost: 19
*/