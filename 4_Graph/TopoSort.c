#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXVEX 100
#define INFINITY 65535

typedef struct EdgeNode {
    int adjvex;
    struct EdgeNode *next;
}EdgeNode;
typedef struct VertexNode {
    char data;
    EdgeNode *firstedge;
}VertexNode, AdjList[MAXVEX];
typedef struct {
    AdjList adjList;
    int numVertexes, numEdges;
}GraphAdjList;

void CreateALGraph(GraphAdjList *G) {
    EdgeNode *e;
    printf("Input the number of vertexes and edges: ");
    scanf("%d,%d", &G->numVertexes, &G->numEdges);
    for (int i = 0; i < G->numVertexes; i++) {
        printf("Input the value of vertex %d: ", i);
        scanf("%s", &G->adjList[i].data);
        G->adjList[i].firstedge = NULL;
    }
    for (int k = 0; k < G->numEdges; k++) {
        printf("Input the edge(vi, vj): ");
        int i, j; scanf("%d%d", &i, &j);
        e = (EdgeNode *)malloc(sizeof(EdgeNode));
        e->adjvex = j;
        e->next = G->adjList[i].firstedge;
        G->adjList[i].firstedge = e;
    }
}

void TopologicalSort(GraphAdjList GL) {
    int top = 0;
    int count = 0;
    int *indegree = (int *)malloc(GL.numVertexes * sizeof(int));
    int *stack = (int *)malloc(GL.numVertexes * sizeof(int));
    for (int i = 0; i < GL.numVertexes; i++)
        indegree[i] = 0;
    for (int i = 0; i < GL.numVertexes; i++) {
        EdgeNode *e = GL.adjList[i].firstedge;
        while (e) {
            indegree[e->adjvex]++;
            e = e->next;
        }
    }

    for (int i = 0; i < GL.numVertexes; i++)
        if (indegree[i] == 0)
            stack[++top] = i;
    while (top != 0) {
        int gettop = stack[top--];
        printf("%c -> ", GL.adjList[gettop].data);
        count++;
        for (EdgeNode *e = GL.adjList[gettop].firstedge; e; e = e->next) {
            int k = e->adjvex;
            if (!(--indegree[k]))
                stack[++top] = k;
        }
    }

    if (count < GL.numVertexes)
        printf("There is a cycle in the graph.\n");
    else
        printf("Topological sort is successful.\n");
}

int main() {
    GraphAdjList GL;
    CreateALGraph(&GL);
    TopologicalSort(GL);
    return 0;
}

/*
Input the number of vertexes and edges: 6, 9
Input the value of vertex 0: v0
Input the value of vertex 1: v1
Input the value of vertex 2: v2
Input the value of vertex 3: v3
Input the value of vertex 4: v4
Input the value of vertex 5: v5
Input the edge(vi, vj): 0 1
Input the edge(vi, vj): 0 2
Input the edge(vi, vj): 1 3
Input the edge(vi, vj): 1 4
Input the edge(vi, vj): 3 5
Input the edge(vi, vj): 4 5
Input the edge(vi, vj): 2 4
Input the edge(vi, vj): 2 3
Input the edge(vi, vj): 5 0
v0 -> v1 -> v2 -> v3 -> v4 -> v5 -> Topological sort is successful.
*/