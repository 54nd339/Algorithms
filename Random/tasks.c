// C program to find minimum average completion time of tasks using greedy approach
#include <stdio.h>
#include <stdlib.h>

typedef struct task {
    int id, pi;
}Task;

int compare(const void *a, const void *b) {
    return ((Task *)a)->pi - ((Task *)b)->pi;
}
void findMinAvgTime(Task *arr, int n) {
    qsort(arr, n, sizeof(arr[0]), compare);

    int total = 0, completionTime = 0;
    for (int i = 0; i < n; i++) {
        completionTime += arr[i].pi;
        total += completionTime;
        printf("Task %c has completion time %d, total time %d, processing time %d\n", arr[i].id, completionTime, total, arr[i].pi);
    }

    printf("Minimum average completion time = %f\n", (float)total / n);
}

int main() {
    Task arr[] = {{'a', 5}, {'b', 3}, {'c', 2}, {'d', 4}, {'e', 1}};
    int n = sizeof(arr) / sizeof(arr[0]);
    findMinAvgTime(arr, n);
    return 0;
}