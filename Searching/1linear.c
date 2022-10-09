#include <stdio.h>
void search(int arr[], int n, int x) {
    int left = 0, right = n - 1;
    int index = -1;
       
    for(left = 0; left <= right;) {
        if (arr[left] == x) {
            index = left; break;
        }
        if (arr[right] == x) {
            index = right; break;
        }
        left++; right--;
    }
    (index == -1)
        ? printf("Element is not present in array")
        : printf("Element is present at index %d", index);
}
 
int main() {
    printf("Enter the size of array : ");
    int n; scanf("%d", &n);
    int arr[n];
    printf("Enter array elements : ");
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    printf("Enter the element to be searched : ");
    int ele; scanf("%d", &ele);
    search(arr, n, ele);
    return 0;
}