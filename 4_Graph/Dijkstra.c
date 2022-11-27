#include <stdio.h>
#include <stdlib.h>

typedef struct edge {
    int u, v, w;
} Edge;
typedef struct vertex {
    int parent, dist, visited;
} Vertex;
typedef struct graph {
    int V, E;
    Edge *edge;
} graph;

graph *createGraph(int vertices, int edges) {
    graph *g = malloc(sizeof(graph));
    g->V = vertices; g->E = edges;
    g->edge = malloc(edges * sizeof(Edge));

    printf("Enter edges (u v w):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d %d", &g->edge[i].u, &g->edge[i].v, &g->edge[i].w);
    }
    return g;
}
void printGraph(graph *g) {
    for (int i = 0; i < g->E; i++) {
        printf("Edge %d: %d -> %d (%d)\n", i, g->edge[i].u, g->edge[i].v, g->edge[i].w);
    }
}

int minKey(Vertex *V, int vertices) {
    int min = 9999, minIndex;
    for (int i = 0; i < vertices; i++) {
        if (V[i].visited == 0 && V[i].dist < min) {
            min = V[i].dist; minIndex = i;
        }
    }
    return minIndex;
}
void Dijkstra(graph *g, int start) {
    Vertex *vertex = malloc(g->V * sizeof(Vertex));
    for (int i = 0; i < g->V; i++) {
        vertex[i].parent = -1;
        vertex[i].dist = 9999;
        vertex[i].visited = 0;
    }
    vertex[start].dist = 0;
    for (int i = 0; i < g->V - 1; i++) {
        int u = minKey(vertex, g->V);
        vertex[u].visited = 1;
        for (int j = 0; j < g->E; j++) {
            int v = g->edge[j].v;
            int w = g->edge[j].w;
            if (g->edge[j].u == u && vertex[v].visited == 0 && w + vertex[u].dist < vertex[v].dist) {
                vertex[v].parent = u;
                vertex[v].dist = w + vertex[u].dist;
            }
        }
    }
    int total = 0;
    for (int i = 1; i < g->V; i++) {
        printf("%d -> %d (%d)\n", vertex[i].parent, i, vertex[i].dist);
        total += vertex[i].dist;
    }
    printf("Total weight: %d\n", total);
}

int main() {
    printf("Enter number of vertices: ");
    int vertices; scanf("%d", &vertices);
    printf("Enter number of edges: ");
    int edges; scanf("%d", &edges);
    graph *g = createGraph(vertices, edges);

    printf("\nGraph:\n");
    printGraph(g);

    printf("\nEnter start vertex: ");
    int start; scanf("%d", &start);
    Dijkstra(g, start);
    return 0;
}
/*
Enter number of vertices: 5
Enter number of edges: 7
Enter edges (u v w):
0 1 2
0 2 4
0 3 1
1 2 3
1 4 10
2 3 2
3 4 7
Graph:
Edge 0: 0 -> 1 (2)
Edge 1: 0 -> 3 (6)
Edge 2: 1 -> 2 (3)
Edge 3: 1 -> 3 (8)
Edge 4: 1 -> 4 (5)
Edge 5: 2 -> 4 (7)
Edge 6: 3 -> 4 (9)

Enter start vertex: 0
0 -> 1 (2)
0 -> 3 (6)
1 -> 2 (5)
1 -> 4 (7)
Total weight: 20
*/