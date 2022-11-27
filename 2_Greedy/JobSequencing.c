#include <stdio.h>
#include <stdlib.h>

typedef struct Job {
    int ind, deadline, profit;
}job;
int cmp(const void *a, const void *b) {
    return ((job *)b)->profit - ((job *)a)->profit;
}

int main() {
    printf("Enter the number of jobs : ");
    int n; scanf("%d", &n);
    job *arr = malloc(n * sizeof(job));
    printf("Enter the deadline and profit of each job :\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &arr[i].deadline, &arr[i].profit);
        arr[i].ind = i + 1;
    }
    qsort(arr, n, sizeof(job), cmp);

    int max = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i].deadline > max) {
            max = arr[i].deadline;
        }
    }
    int *slot = malloc(max * sizeof(int));
    for (int i = 0; i < max; i++) {
        slot[i] = -1;
    }
    int count = 0, profit = 0;
    for (int i = 0; i < n; i++) {
        for (int j = arr[i].deadline - 1; j >= 0; j--) {
            if (slot[j] == -1) {
                slot[j] = arr[i].ind;
                profit += arr[i].profit;
                count++; break;
            }
        }
    }
    printf("The jobs selected are:\nIndex\tDeadline\tProfit");
    for (int i = 0; i < max; i++) {
        if (slot[i] != -1) {
            printf("\n%d\t%d\t%d", slot[i], i + 1, arr[slot[i] - 1].profit);
        }
    }
    printf("\nTotal profit is %d", profit);
    return 0;
}

/*
Enter the number of jobs : 4
Enter the deadline and profit of each job :
2 100
1 19
2 27
1 25
The jobs selected are:
Index   Deadline        Profit
2       1       19
4       1       25
1       2       100
Total profit is 144
*/