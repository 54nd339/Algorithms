#include <stdio.h>
#include <stdlib.h>
typedef struct heap {
    int data, size;
    struct heap *left, *right;
}Heap;
Heap *createHeap(int data) {
    Heap *newHeap = (Heap *)malloc(sizeof(Heap));
    newHeap->data = data;
    newHeap->size = 1;
    newHeap->left = newHeap->right = NULL;
    return newHeap;
}

void insertNode(Heap *h, int Key) {
    if (h == NULL) {
        h = createHeap(Key);
        return;
    }
    if (h->left == NULL) {
        h->left = createHeap(Key);
        h->size++; return;
    }
    if (h->right == NULL) {
        h->right = createHeap(Key);
        h->size++; return;
    }
    if (h->left->size <= h->right->size) {
        insertNode(h->left, Key);
        h->size++;
    }
    else {
        insertNode(h->right, Key);
        h->size++;
    }
}
void deleteNode(Heap *h, int i) {
    if (h == NULL) return;
    if (h->left == NULL && h->right == NULL) {
        if (i == 1) {
            free(h);
            h = NULL;
        }
        return;
    }
    if (h->left->size == i - 1) {
        free(h->left);
        h->left = NULL;
        h->size--; return;
    }
    if (h->right->size == i - 1) {
        free(h->right);
        h->right = NULL;
        h->size--; return;
    }
    if (h->left->size >= i) {
        deleteNode(h->left, i);
        h->size--;
    }
    else {
        deleteNode(h->right, i - h->left->size);
        h->size--;
    }
}
void print(Heap h) {
    if(h.size == 0) {
        printf("Heap is empty\n");
        return;
    }
    printf("%d ", h.data);
    if(h.left != NULL) print(*(h.left));
    if(h.right != NULL) print(*(h.right));
}

int main() {
    Heap *h = (Heap*)malloc(sizeof(Heap));
    h->size = 0;

    while (1) {
        printf("\n1. Insert\n2. Delete\n3. Print\n0. Exit\nEnter choice : ");
        int ch; scanf("%d", &ch);
        switch (ch) {
            case 1: 
                    printf("Enter the key to be inserted: ");
                    int key; scanf("%d", &key);
                    insertNode(h, key);
                    print(*h);
                    break;
            case 2: if (h->size == 0) {
                        printf("Heap is empty\n");
                        break;
                    }
                    printf("Enter the index of the node to be deleted: ");
                    int i; scanf("%d", &i);
                    deleteNode(h, i);
                    print(*h);
                    break;
            case 3: print(*h);
                    break;
            case 0: exit(0);
            default: printf("Invalid choice\n");
        }
    }
    return 0;
}