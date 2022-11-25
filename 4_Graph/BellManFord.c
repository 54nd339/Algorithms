#include <stdio.h>
#include <stdlib.h>

typedef struct edge {
    int u, v, w;
} Edge;
typedef struct vertex {
    int dist, visited;
} Vertex;
typedef struct graph {
    int V, E;
    Edge *edge;
} graph;

graph *createGraph(int vertices, int edges) {
    graph *g = malloc(sizeof(graph));
    g->V = vertices;
    g->E = edges;
    g->edge = malloc(edges * sizeof(Edge));

    for (int i = 0; i < edges; i++) {
        printf("Enter edge %d: ", i);
        scanf("%d %d %d", &g->edge[i].u, &g->edge[i].v, &g->edge[i].w);
    }

    return g;
}
void printGraph(graph *g) {
    for (int i = 0; i < g->E; i++) {
        printf("Edge %d: %d -> %d (%d)\n", i, g->edge[i].u, g->edge[i].v, g->edge[i].w);
    }
}

void BellmanFord(graph *g, int start) {
    Vertex *vertex = malloc(g->V * sizeof(Vertex));
    for (int i = 0; i < g->V; i++) {
        vertex[i].dist = 9999;
        vertex[i].visited = 0;
    }
    vertex[start].dist = 0;
    for (int i = 0; i < g->V - 1; i++) {
        for (int j = 0; j < g->E; j++) {
            int u = g->edge[j].u;
            int v = g->edge[j].v;
            int w = g->edge[j].w;
            if (vertex[u].dist + w < vertex[v].dist) {
                vertex[v].dist = vertex[u].dist + w;
            }
        }
    }

    for (int i = 0; i < g->E; i++) {
        int u = g->edge[i].u;
        int v = g->edge[i].v;
        int w = g->edge[i].w;
        if (vertex[u].dist + w < vertex[v].dist) {
            printf("Graph contains negative weight cycle\n");
            return;
        }
    }
    for (int i = 0; i < g->V; i++) {
        printf("Vertex %d: %d\n", i, vertex[i].dist);
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

    printf("\nEnter start vertex: ");
    int start; scanf("%d", &start);
    BellmanFord(g, start);
    return 0;
}

/*
Enter number of vertices: 5
Enter number of edges: 8
Enter edge 0: 0 1 -1
Enter edge 1: 0 2 4
Enter edge 2: 1 2 3
Enter edge 3: 1 3 2
Enter edge 4: 1 4 2
Enter edge 5: 3 2 5
Enter edge 6: 3 1 1
Enter edge 7: 4 3 -3

Graph:
Edge 0: 0 -> 1 (-1)
Edge 1: 0 -> 2 (4)
Edge 2: 1 -> 2 (3)
Edge 3: 1 -> 3 (2)
Edge 4: 1 -> 4 (2)
Edge 5: 3 -> 2 (5)
Edge 6: 3 -> 1 (1)
Edge 7: 4 -> 3 (-3)

Enter start vertex: 0
Vertex 0: 0
Vertex 1: -1
Vertex 2: 2
Vertex 3: -2
Vertex 4: 1
*/