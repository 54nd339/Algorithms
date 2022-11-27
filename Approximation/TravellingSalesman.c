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
void addEdge(Graph *G, int u, int v, int w) {
    G->adjMat[u][v] = w;
    G->adjMat[v][u] = w;
}

void printGraph(Graph *G) {
    for (int i = 0; i < G->V; i++) {
        for (int j = 0; j < G->V; j++) {
            if (G->adjMat[i][j] != 0)
                printf("%d -> %d (%d)\n", i, j, G->adjMat[i][j]);
        }
    }
}
void DFS(int **mst, int V, int start, int *visited, int **path, int *pathIndex) {
    path[*pathIndex][0] = start;
    path[*pathIndex][1] = mst[start][1];
    (*pathIndex)++;
    visited[start] = 1;
    for (int i = 0; i < V; i++) {
        if (mst[i][0] == start && visited[i] == 0) {
            DFS(mst, V, i, visited, path, pathIndex);
        }
    }
}

int minKey(int key[], int mstSet[], int V) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++) {
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v], min_index = v;
        }
    }
    return min_index;
}
int **prim(Graph *G) {
    int *parent = (int *)malloc(G->V * sizeof(int));
    int *key = (int *)malloc(G->V * sizeof(int));
    int *mstSet = (int *)malloc(G->V * sizeof(int));
    for (int i = 0; i < G->V; i++) {
        key[i] = INT_MAX, mstSet[i] = 0;
    }

    key[0] = 0; parent[0] = -1;
    for (int count = 0; count < G->V - 1; count++) {
        int u = minKey(key, mstSet, G->V);
        mstSet[u] = 1;
        for (int v = 0; v < G->V; v++) {
            if (G->adjMat[u][v] && mstSet[v] == 0 && G->adjMat[u][v] < key[v]) {
                parent[v] = u, key[v] = G->adjMat[u][v];
            }
        }
    }

    int **mst = (int **)malloc(G->V * sizeof(int *));
    for (int i = 0; i < G->V; i++) {
        mst[i] = (int *)malloc(2 * sizeof(int));
    }
    for (int i = 1; i < G->V; i++) {
        mst[i][0] = parent[i];
        mst[i][1] = i;
    }

    return mst;
}

int main() {
    printf("Enter number of vertices: ");
    int V; scanf("%d", &V);
    printf("Enter number of edges: ");
    int E; scanf("%d", &E);
    Graph *G = createGraph(V, E);
    printf("Enter edges (u v w):\n");
    for (int i = 0; i < E; i++) {
        int u, v, w; scanf("%d %d %d", &u, &v, &w);
        addEdge(G, u, v, w);
    }
    printf("\nGraph:\n");
    printGraph(G);

    int **mst = prim(G);
    printf("\nMST:\n");
    for (int i = 1; i < G->V; i++) {
        printf("%d -> %d\n", mst[i][0], mst[i][1]);
    }

    int *visited = (int *)calloc(G->V, sizeof(int));
    int **path = (int **)malloc(G->V * sizeof(int *));
    for (int i = 0; i < G->V; i++) {
        path[i] = (int *)malloc(2 * sizeof(int));
    }
    int pathIndex = 0;
    DFS(mst, G->V, 0, visited, path, &pathIndex);

    printf("\nPath:\n");
    for (int i = 0; i < pathIndex; i++)
        printf("%d -> ", path[i][0]);
    printf("%d\n", path[0][0]);

    return 0;
}

/*
Enter number of vertices: 5
Enter number of edges: 10
Enter edges (u v w):
0 1 10
0 2 15
0 3 40
0 4 20
1 2 35
1 3 15
1 4 12
2 3 10
2 4 25
3 4 30

Graph:
0 -> 1 (10)
0 -> 2 (15)
0 -> 3 (40)
0 -> 4 (20)
1 -> 0 (10)
1 -> 2 (35)
1 -> 3 (15)
1 -> 4 (12)
2 -> 0 (15)
2 -> 1 (35)
2 -> 3 (10)
2 -> 4 (25)
3 -> 0 (40)
3 -> 1 (15)
3 -> 2 (10)
3 -> 4 (30)
4 -> 0 (20)
4 -> 1 (12)
4 -> 2 (25)
4 -> 3 (30)

MST:
0 -> 1
0 -> 2
1 -> 4
2 -> 3

Path:
0 -> 1 -> 4 -> 2 -> 3 -> 0
*/