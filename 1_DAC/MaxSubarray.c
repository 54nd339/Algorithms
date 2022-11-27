#include <stdio.h>
#include <stdlib.h>
#define max(a,b) ((a > b) ? a : b)

int maxSubarray(int *A, int low, int high, int *start, int *end) {
    if (low == high) {
        *start = low;
        *end = high;
        return A[low];
    }
    int mid = (low + high) / 2;
    int leftLow, leftHigh;
    int leftSum = maxSubarray(A, low, mid, &leftLow, &leftHigh);
    int rightLow, rightHigh;
    int rightSum = maxSubarray(A, mid + 1, high, &rightLow, &rightHigh);
    
    int crossLow, crossHigh, crossSum = A[mid];
    int sum = 0;
    for (int i = mid; i >= low; i--) {
        sum += A[i];
        if (sum > crossSum) {
            crossSum = sum;
            crossLow = i;
        }
    }
    sum = crossSum;
    for (int i = mid + 1; i <= high; i++) {
        sum += A[i];
        if (sum > crossSum) {
            crossSum = sum;
            crossHigh = i;
        }
    }

    if (leftSum >= rightSum && leftSum >= crossSum) {
        *start = leftLow;
        *end = leftHigh;
        return leftSum;
    }
    else if (rightSum >= leftSum && rightSum >= crossSum) {
        *start = rightLow;
        *end = rightHigh;
        return rightSum;
    }
    else {
        *start = crossLow;
        *end = crossHigh;
        return crossSum;
    }
}

int main() {
    printf("Enter the number of elements: ");
    int n; scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    printf("Enter the elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int start, end;
    int sum = maxSubarray(arr, 0, n - 1, &start, &end);
    printf("The maximum subarray is A[%d] to A[%d], sum is %d\n", start, end, sum);

    return 0;
}