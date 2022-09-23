#include <stdio.h>
int Search(int arr[], int l, int r, int x) {
    if (r >= l) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == x) return mid;
        if (arr[mid] > x)
            return Search(arr, l, mid - 1, x);
        return Search(arr, mid + 1, r, x);
    }
    return -1;
}
  
int main() {
    printf("Enter the size of array : ");
    int n; scanf("%d", &n);
    int arr[n];
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