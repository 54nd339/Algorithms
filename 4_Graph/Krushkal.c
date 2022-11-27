#include <stdio.h>
#include <stdlib.h>

typedef struct edge {
    int u, v, w;
} edge;
typedef struct heap {
    int size;
    edge *arr;
} heap;
void swap(edge *a, edge *b) {
    edge t = *a;
    *a = *b;
    *b = t;
}

void heapify(heap *h, int i) {
    int smallest = i, l = 2*i+1, r = 2*i+2;
    if (l < h->size && h->arr[l].w < h->arr[smallest].w)
        smallest = l;
    if (r < h->size && h->arr[r].w < h->arr[smallest].w)
        smallest = r;
    if (smallest != i) {
        swap(&(h->arr[i]), &(h->arr[smallest]));
        heapify(h, smallest);
    }
}
edge extractMin(heap *h) {
    if (h->size == 0) {
        printf("Heap is empty\n");
        exit(0);
    }
    edge min = h->arr[0];
    h->arr[0] = h->arr[h->size-1];
    h->size--;
    heapify(h, 0);
    return min;
}
void insertNode(heap *h, edge e) {
    h->size++;
    int i = h->size - 1;
    h->arr[i] = e;
    int j = (i-1)/2;
    while (i != 0 && h->arr[j].w > h->arr[i].w) {
        swap(&(h->arr[i]), &(h->arr[j]));
        i = j;
        j = (i-1)/2;
    }
}
void print(heap h) {
    if (h.size == 0) {
        printf("Heap is empty\n");
        return;
    }
    for (int i = 0; i < h.size; ++i)
        printf("%d %d %d\n", h.arr[i].u, h.arr[i].v, h.arr[i].w);
    printf("\n");
}

typedef struct subset {
    int parent, rank;
} subset;
int find(subset *subsets, int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}
void Union(subset *subsets, int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

void KruskalMST(heap *h, int V) {
    edge *result = malloc(V*sizeof(edge));
    subset *subsets = (subset *)malloc(V * sizeof(subset));
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
    int e = 0, total = 0; 
    while (e < V - 1) {
        edge next_edge = extractMin(h);
        int x = find(subsets, next_edge.u);
        int y = find(subsets, next_edge.v);
        if (x != y) {
            result[e++] = next_edge;
            total += next_edge.w;
            Union(subsets, x, y);
        }
    }
    for (int i = 0; i < e; ++i)
        printf("%d %d %d\n", result[i].u, result[i].v, result[i].w);
    printf("Total weight: %d\n", total);
}

int main() {
    printf("Enter no. of vertices and edges: ");
    int V, E; scanf("%d %d", &V, &E);

    heap h; h.size = 0;
    h.arr = (edge *)malloc(E * sizeof(edge));
    for (int i = 0; i < E; ++i) {
        scanf("%d %d %d", &(h.arr[i].u), &(h.arr[i].v), &(h.arr[i].w));
        insertNode(&h, h.arr[i]);
    }
    printf("MST:\n");
    KruskalMST(&h, V);
    return 0;
}

/*
Enter no. of vertices and edges: 4 5
0 1 10
0 2 6
0 3 5
1 3 15
2 3 4
MST:
0 3 5
2 3 4
0 1 10
*/