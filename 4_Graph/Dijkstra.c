#include <stdio.h>
#include <stdlib.h>
#define INF 99999
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
        for (int j = 0; j < vertices; j++) {
            g->adjMatrix[i][j] = 0;
        }
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

int minDistance(int *dist, int *visited, int vertices) {
    int min = INF, minIndex;
    for (int i = 0; i < vertices; i++) {
        if (visited[i] == 0 && dist[i] <= min) {
            min = dist[i]; minIndex = i;
        }
    }
    return minIndex;
}
void dijkstra(graph *g, int src) {
    int *dist = malloc(g->vertices * sizeof(int));
    int *visited = malloc(g->vertices * sizeof(int));
    for (int i = 0; i < g->vertices; i++) {
        dist[i] = INF; visited[i] = 0;
    }
    dist[src] = 0;
    for (int i = 0; i < g->vertices - 1; i++) {
        int u = minDistance(dist, visited, g->vertices);
        visited[u] = 1;
        for (int v = 0; v < g->vertices; v++) {
            if (visited[v] == 0 && g->adjMatrix[u][v] != 0 && dist[u] != INF && dist[u] + g->adjMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + g->adjMatrix[u][v];
            }
        }
    }
    int sum = 0;
    for (int i = 0; i < g->vertices; i++) {
        printf("%d ", dist[i]); sum += dist[i];
    }
    printf("\nTotal distance: %d\n", sum);
}

int main() {
    printf("Enter number of vertices: ");
    int vertices; scanf("%d", &vertices);
    printf("Enter number of edges: ");
    int edges; scanf("%d", &edges);
    graph *g = createGraph(vertices, edges);

    printf("\nGraph:\n");
    printGraph(g);
    
    printf("\nEnter source vertex: ");
    int src; scanf("%d", &src);
    dijkstra(g, src);
    return 0;
}
/*
Enter number of vertices: 9
Enter number of edges: 14
Enter edge 0: 0 1 4
Enter edge 1: 0 7 8
Enter edge 2: 1 2 8
Enter edge 3: 1 7 11
Enter edge 4: 2 3 7
Enter edge 5: 2 8 2
Enter edge 6: 2 5 4
Enter edge 7: 3 4 9
Enter edge 8: 3 5 14
Enter edge 9: 4 5 10
Enter edge 10: 5 6 2
Enter edge 11: 6 7 1
Enter edge 12: 6 8 6
Enter edge 13: 7 8 7

Graph:
Vertex 0 is connected to: 1 (4) 7 (8)
Vertex 1 is connected to: 0 (4) 2 (8) 7 (11)
Vertex 2 is connected to: 1 (8) 3 (7) 8 (2) 5 (4)
Vertex 3 is connected to: 2 (7) 4 (9) 5 (14)
Vertex 4 is connected to: 3 (9) 5 (10)
Vertex 5 is connected to: 2 (4) 3 (14) 4 (10) 6 (2)
Vertex 6 is connected to: 5 (2) 7 (1) 8 (6)
Vertex 7 is connected to: 0 (8) 1 (11) 6 (1) 8 (7)
Vertex 8 is connected to: 2 (2) 6 (6) 7 (7)

Enter source vertex: 0
0 4 12 19 21 11 9 8 14
Total distance: 98
*/