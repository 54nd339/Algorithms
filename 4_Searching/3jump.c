#include <stdio.h>
#include <math.h>
int min(int a, int b) {
    return a < b ? a : b;
}
int Search(int arr[], int x, int n) {
    int step = sqrt(n), prev = 0;
	while (arr[min(step, n)-1] < x) {
		prev = step;
		step += sqrt(n);
		if (prev >= n)
			return -1;
	}
    while (arr[prev] < x) {
		prev++;
        if (prev == min(step, n))
			return -1;
	}
    if (arr[prev] == x)
		return prev;
    return -1;
}

int main(){
    printf("Enter the size of array : ");
    int n; scanf("%d", &n);
    int arr[n];
    printf("Enter array elements (Sorted) : ");
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    printf("Enter the element to be searched : ");
    int ele; scanf("%d", &ele);
    int result = Search(arr, ele, n);
    (result == -1)
        ? printf("Element is not present in array")
        : printf("Element is present at index %d", result);
    return 0;
}