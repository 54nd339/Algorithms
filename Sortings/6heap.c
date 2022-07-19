#include <stdio.h>
#include <stdlib.h>
void swap(int* a, int* b) {
	int t = *a;
	*a = *b;
	*b = t;
}
void heapify(int *arr, int n, int i){
    int largest = i;
    int l = 2*i+1, r = 2*i+2;
 
    if (l < n && arr[l] > arr[largest])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;
    if (largest != i) {
        swap(&(arr[i]), &(arr[largest]));
        heapify(arr, n, largest);
    }
}
 
void heapSort(int *arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
 
    for (int i = n - 1; i > 0; i--) {
        swap(&(arr[0]), &(arr[i]));
        heapify(arr, i, 0);
    }
}

void print(int *arr, int size) {
	for (int i=0; i < size; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

int main() {
    printf("Enter no. of elements : ");
    int n; scanf("%d", &n);
    int *ar = malloc(n * sizeof(int));
    printf("Enter Elements : ");
    for (int i = 0; i < n; i++)
        scanf("%d", &ar[i]);
	
    printf("Original array : ");
	print(ar, n);

    heapSort(ar, n);
	printf("Sorted array : ");
	print(ar, n);
	return 0;
}