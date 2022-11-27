#include <stdio.h>
#include <stdlib.h>
#define max(a,b) ((a > b) ? a : b)

int knapsack(int *val, int *wt, int W, int n) {
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)malloc((W + 1) * sizeof(int));
        for (int j = 0; j <= W; j++)
            dp[i][j] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= W; j++) {
            if (wt[i - 1] <= j)
                dp[i][j] = max(val[i - 1] + dp[i - 1][j - wt[i - 1]], dp[i - 1][j]);
            else
                dp[i][j] = dp[i - 1][j];
        }
    }

    return dp[n][W];
}

int main() {
    printf("Enter the number of elements: ");
    int n; scanf("%d", &n);
    printf("Enter the capacity of the knapsack: ");
    int W; scanf("%d", &W);

    int *val = (int *)malloc(n * sizeof(int));
    printf("Enter the values: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &val[i]);

    int *wt = (int *)malloc(n * sizeof(int));
    printf("Enter the weights: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &wt[i]);

    printf("The maximum value that can be obtained is %d\n", knapsack(val, wt, W, n));
    return 0;
}
/*
Enter the number of elements: 4
Enter the capacity of the knapsack: 5
Enter the values: 1 4 5 7
Enter the weights: 1 3 4 5
The maximum value that can be obtained is 7
*/