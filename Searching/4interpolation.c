#include <stdio.h>
#include <stdlib.h>

int Search(int arr[], int lo, int hi, int x) {
    if (lo <= hi && x >= arr[lo] && x <= arr[hi]) {
        int pos = lo + (((double)(hi - lo) / (arr[hi] - arr[lo]))
				* (x - arr[lo]));

		if (arr[pos] == x) return pos;
		if (arr[pos] < x) Search(arr, pos + 1, hi, x);
        return Search(arr, lo, pos - 1, x);
	}
	return -1;
}

int main(){
    printf("Enter the size of array : ");
    int n; scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    printf("Enter array elements (Sorted) : ");
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter the element to be searched : ");
    int ele; scanf("%d", &ele);
    int result = Search(arr, 0, n - 1, ele);
    (result == -1)
        ? printf("Element is not present in array")
        : printf("Element is present at index %d", result);

	return 0;
}

// Time Complexity: O(log log n), θ(log log n), Ω(1)
// Space Complexity: O(1)