#include <stdio.h>
#include <stdlib.h>

typedef struct edge {
    int u, v, w;
} Edge;
typedef struct vertex {
    int parent, visited;
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

int findPath(graph *g, int s, int t, Vertex *vertex) {
    if (s == t) return 1;
    vertex[s].visited = 1;
    for (int i = 0; i < g->E; i++) {
        if (g->edge[i].u == s && !vertex[g->edge[i].v].visited && g->edge[i].w > 0) {
            vertex[g->edge[i].v].parent = i;
            if (findPath(g, g->edge[i].v, t, vertex)) return 1;
        }
    }
    return 0;
}
int fordFulkerson(graph *g, int s, int t) {
    int maxFlow = 0;
    Vertex *vertex = malloc(g->V * sizeof(Vertex));
    while (findPath(g, s, t, vertex)) {
        int pathFlow = 1000000;
        for (int v = t; v != s; v = g->edge[vertex[v].parent].u) {
            int e = vertex[v].parent;
            pathFlow = pathFlow < g->edge[e].w ? pathFlow : g->edge[e].w;
        }
        for (int v = t; v != s; v = g->edge[vertex[v].parent].u) {
            int e = vertex[v].parent;
            g->edge[e].w -= pathFlow;
            g->edge[e^1].w += pathFlow;
        }
        maxFlow += pathFlow;
        for (int i = 0; i < g->V; i++) {
            vertex[i].visited = 0;
            vertex[i].parent = -1;
        }
    }
    return maxFlow;
}

int main() {
    int vertices, edges;
    printf("Enter number of vertices: ");
    scanf("%d", &vertices);
    printf("Enter number of edges: ");
    scanf("%d", &edges);
    graph *g = createGraph(vertices, edges);
    printf("Graph:\n");
    printGraph(g);
    printf("Max Flow: %d\n", fordFulkerson(g, 0, vertices-1));
    return 0;
}
/*
Enter number of vertices: 6
Enter number of edges: 8
Enter edges (u v w):
0 1 16
0 2 13
1 2 10
1 3 12
2 1 4
2 4 14
3 2 9
3 5 20

Graph:
Edge 0: 0 -> 1 (16)
Edge 1: 0 -> 2 (13)
Edge 2: 1 -> 2 (10)
Edge 3: 1 -> 3 (12)
Edge 4: 2 -> 1 (4)
Edge 5: 2 -> 4 (14)
Edge 6: 3 -> 2 (9)
Edge 7: 3 -> 5 (20)
Max Flow: 23
*/