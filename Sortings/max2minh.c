#include <stdio.h>
#include <stdlib.h>
void swap(int *x, int *y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}

typedef struct Heap {
	int *harr; // pointer to array of elements in heap
	int capacity; // maximum possible size of min heap
	int size; // Current number of elements in min heap
} heap;

heap *createMaxHeap(){
    heap *root = malloc(sizeof(heap));
    printf("Enter size of the Heap : ");   
    scanf("%d",&root->capacity);
    root->size = 0;
    root->harr = malloc(root->capacity * sizeof(int));
    return root;
}

int parent(int i) { return (i-1)/2; }
// to get index of left child of node at index i
int left(int i) { return (2*i + 1); }
// to get index of right child of node at index i
int right(int i) { return (2*i + 2); }

void insert(heap *root, int k) {
	if (root->size == root->capacity) {
		printf("\nOverflow: Could not insertKey\n");
		return;
	}

	// First insert the new key at the end
	root->size++;
	int i = root->size - 1;
	root->harr[i] = k;

	// Fix the max heap property if it is violated
	while (i != 0 && root->harr[parent(i)] < root->harr[i]) {
        swap(&(root->harr[i]), &(root->harr[parent(i)]));
        i = parent(i);
	}
}

void print(heap* root) {
    for (int i=0; i<root->size; i++) {
        printf("%d ", root->harr[i]);
    }
    printf("\n");
}

void heapify(heap* root, int i) {
    int l = left(i), r = right(i), m = i;
    if (l < root->capacity && root->harr[i] > root->harr[l])
        m = l;
    if (r < root->capacity && root->harr[m] > root->harr[r])
        m = r;
    if (m != i) {
        swap(&(root->harr[m]), &(root->harr[i]));
        heapify(root, m);
    }
}
void convertMinHeap(heap *root) {
    for (int i = (root->capacity-2)/2; i >= 0; --i)
        heapify(root, i);
}

int main() {
    //Min Heap array : 3 5 9 6 8 20 10 12 18 9 
    //Max Heap array : 20 18 10 12 9 9 3 5 6 8 
	heap *root = createMaxHeap(); int in;
    printf("Enter Elements : ");
    while(root->size < root->capacity){
        scanf("%d", &in);
        insert(root, in);
	}
    printf("Max Heap : ");
    print(root);
    
    convertMinHeap(root);
    printf("Min Heap : ");
    print(root);
	return 0;
}