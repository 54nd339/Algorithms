#include <stdio.h>
#include <stdlib.h>

int getMax(int arr[], int n) {
	int mx = arr[0];
	for (int i = 1; i < n; i++) {
		if (arr[i] > mx)
			mx = arr[i];
	}
	return mx;
}
void countSort(int arr[], int n, int exp) {
	int *output = malloc(n * sizeof(int));
	int *count = malloc(10 * sizeof(int));
    for (int i = 0; i < n; i++)
		count[(arr[i] / exp) % 10]++;
	for (int i = 1; i < 10; i++)
		count[i] += count[i - 1];
	for (int i = n - 1; i >= 0; i--) {
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}
    for (int i = 0; i < n; i++)
		arr[i] = output[i];
}
void radixsort(int arr[], int n) {
    int m = getMax(arr, n);
    for (int exp = 1; m / exp > 0; exp *= 10) 
		countSort(arr, n, exp);
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

    radixsort(ar, n);
	printf("Sorted array : ");
	print(ar, n);
	return 0;
}

// Time Complexity: O(d(n+k)), θ(d(n+k)), Ω(d(n+k))
// Space Complexity: O(n+k)