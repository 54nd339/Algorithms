#include <stdio.h>
#include <stdlib.h>
typedef struct heap {
    int *arr, size, capacity;
}Heap;
void swap(int* a, int* b) {
	int t = *a;
	*a = *b;
	*b = t;
}

void insertNode(Heap *h, int Key) {
    h->size++; int i = h->size - 1;
    h->arr[i] = Key; int j = (i-1)/2;
    while (i != 0 && h->arr[j] < h->arr[i]) {
        swap(&(h->arr[i]), &(h->arr[j]));
        i = j; j = (i-1)/2;
    }
}
void deleteNode(Heap *h, int i) {
    if(i >= h->size) {
        printf("Invalid Index\n");
        return;
    }
    h->arr[i] = h->arr[h->size - 1]; h->size--;
    int l = 2*i + 1, r = 2*i + 2, largest = i;
    while(l < h->size) {
        if(h->arr[l] > h->arr[largest]) largest = l;
        if(h->arr[r] > h->arr[largest]) largest = r;
        if(largest != i) {
            swap(&(h->arr[i]), &(h->arr[largest]));
            i = largest;
            l = 2*i + 1; r = 2*i + 2;
        }
        else break;
    }
}
void print(Heap h) {
    if(h.size == 0) {
        printf("Heap is empty\n");
        return;
    }
    for (int i = 0; i < h.size; ++i)
        printf("%d ", h.arr[i]);
    printf("\n");
}

int main() {
    Heap *h = (Heap*)malloc(sizeof(Heap));
    printf("Enter the size of the array: ");
    scanf("%d", &h->capacity);
    h->arr = (int*)malloc(h->capacity * sizeof(int));
    h->size = 0;

    while (1) {
        printf("\n1. Insert\n2. Delete\n3. Print\n0. Exit\nEnter choice : ");
        int ch; scanf("%d", &ch);
        switch (ch) {
            case 1: if (h->size == h->capacity)
                        printf("Heap is full :\n");
                    else {
                        printf("Enter the key to be inserted: ");
                        int key; scanf("%d", &key);
                        insertNode(h, key);
                    }
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