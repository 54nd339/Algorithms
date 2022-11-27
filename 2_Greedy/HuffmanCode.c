#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    int freq;
    struct Node *left, *right;
}node;
typedef struct Heap {
    int size;
    node **arr;
}heap;

node *newNode(char data, int freq) {
    node *temp = malloc(sizeof(node));
    temp->data = data;
    temp->freq = freq;
    temp->left = temp->right = NULL;
    return temp;
}
heap *newHeap(int size) {
    heap *temp = malloc(sizeof(heap));
    temp->size = size;
    temp->arr = malloc(size * sizeof(node *));
    return temp;
}

void swap(node **a, node **b) {
    node *temp = *a;
    *a = *b;
    *b = temp;
}
void minHeapify(heap *h, int i) {
    int smallest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;
    if (left < h->size && h->arr[left]->freq < h->arr[smallest]->freq)
        smallest = left;
    if (right < h->size && h->arr[right]->freq < h->arr[smallest]->freq)
        smallest = right;
    if (smallest != i) {
        swap(&h->arr[smallest], &h->arr[i]);
        minHeapify(h, smallest);
    }
}
node *extractMin(heap *h) {
    node *temp = h->arr[0];
    h->arr[0] = h->arr[h->size - 1];
    h->size--;
    minHeapify(h, 0);
    return temp;
}

void insert(heap *h, node *temp) {
    h->size++;
    int i = h->size - 1;
    while (i && temp->freq < h->arr[(i - 1) / 2]->freq) {
        h->arr[i] = h->arr[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    h->arr[i] = temp;
}
void buildHeap(heap *h) {
    int n = h->size - 1;
    for (int i = (n - 1) / 2; i >= 0; i--) {
        minHeapify(h, i);
    }
}

node *buildHuffmanTree(char data[], int freq[], int size) {
    node *left, *right, *top;
    heap *h = newHeap(size);
    for (int i = 0; i < size; i++) {
        h->arr[i] = newNode(data[i], freq[i]);
    }
    buildHeap(h);
    while (h->size != 1) {
        left = extractMin(h);
        right = extractMin(h);
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insert(h, top);
    }
    return extractMin(h);
}

void printCodes(node *root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
    if (!root->left && !root->right) {
        printf("%c: ", root->data);
        for (int i = 0; i < top; i++) {
            printf("%d", arr[i]);
        }
        printf("\n");
    }
}
void HuffmanCodes(char data[], int freq[], int size) {
    node *root = buildHuffmanTree(data, freq, size);
    int arr[100]; float sum = 0.0f;
    printCodes(root, arr, 0);
}

int main() {
    printf("Enter the number of characters : ");
    int n; scanf("%d", &n);
    char *data = malloc(n * sizeof(char));
    int *freq = malloc(n * sizeof(int));
    printf("Enter the characters and frequencies :\n");
    for (int i = 0; i < n; i++)
        scanf(" %c %d", &data[i], &freq[i]);

    printf("Huffman Codes are :\n");
    HuffmanCodes(data, freq, n);
    return 0;
}
/*
Enter the number of characters : 5
Enter the characters and frequencies :
a 5
b 9
c 12
d 13
e 16
f 45
Huffman Codes are :
f: 0
c: 100
d: 101
a: 1100
b: 1101
e: 111
*/