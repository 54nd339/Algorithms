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

void insert(Heap *root, int k) {
	if (root->size == root->capacity) {
		printf("\nOverflow: Could not insertKey\n");
		return;
	}

	root->size++; int i = root->size - 1;
	root->arr[i] = k; int j = (i-1)/2;
    while (i != 0 && root->arr[j] < root->arr[i]) {
        swap(&(root->arr[i]), &(root->arr[j]));
        i = j; j = (i-1)/2;
    }
}
void print(Heap root) {
    if(root.size == 0) {
        printf("Heap is empty\n");
        return;
    }
    for (int i = 0; i < root.size; ++i)
        printf("%d ", root.arr[i]);
    printf("\n");
}

void heapify(Heap* root, int i) {
    int smallest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;
    if (l < root->size && root->arr[l] < root->arr[smallest])
        smallest = l;
    if (r < root->size && root->arr[r] < root->arr[smallest])
        smallest = r;
    if (smallest != i) {
        swap(&(root->arr[i]), &(root->arr[smallest]));
        heapify(root, smallest);
    }
}
void convertMinHeap(Heap* root) {
    for (int i = (root->size - 2)/2; i >= 0; --i)
        heapify(root, i);
}

int main() {
    //Min Heap array : 3 5 9 6 8 20 10 12 18 9 
    //Max Heap array : 20 18 10 12 9 9 3 5 6 8 
    Heap *root = malloc(sizeof(Heap));
    printf("Enter size of the Heap : ");   
    scanf("%d", &root->capacity);
    root->size = 0;
    root->arr = malloc(root->capacity * sizeof(int));

    printf("Enter Elements : ");
    while(root->size < root->capacity){
        int in; scanf("%d", &in);
        insert(root, in);
	}
    printf("Max Heap : ");
    print(*root);
    
    convertMinHeap(root);
    printf("Min Heap : ");
    print(*root);
	return 0;
}