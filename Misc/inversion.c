// Find the number of inversions in an array
#include <stdio.h>
#include <stdlib.h>

int find_inversions(int arr[], int n) {
    if (n == 1)
        return 0;
    else {
        int mid = n / 2;
        int *left = (int *)malloc(mid * sizeof(int));
        for (int i = 0; i < mid; i++) {
            left[i] = arr[i];
        }
        int *right = (int *)malloc((n - mid) * sizeof(int));
        for (int i = mid; i < n; i++) {
            right[i - mid] = arr[i];
        }

        int inversions = find_inversions(left, mid) + find_inversions(right, n - mid);
        int i = 0, j = 0, k = 0;
        while (i < mid && j < n - mid) {
            if (left[i] <= right[j]) {
                arr[k++] = left[i++];
            } else {
                arr[k++] = right[j++];
                inversions += mid - i;
            }
        }
        while (i < mid) {
            arr[k++] = left[i++];
        }
        while (j < n - mid) {
            arr[k++] = right[j++];
        }
        return inversions;
    }
}

int main() {
    int arr[] = {4, 8, 9, 3, 7, 6, 2, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int inversions = find_inversions(arr, n);
    printf("Number of inversions: %d\n", inversions);
    return 0;
}