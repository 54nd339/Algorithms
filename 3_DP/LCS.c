#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SIZE 100
#define max(a,b) ((a > b) ? a : b)

int tabulate(char *X, char *Y, int m, int n ) {
    int **dp = (int **)malloc((m+1)*sizeof(int *));
    for (int i = 0; i <= m; i++) {
        dp[i] = (int *)malloc((n+1)*sizeof(int));
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (X[i-1] == Y[j-1])
                dp[i][j] = dp[i-1][j-1] + 1;
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }

    return dp[m][n];
}

int memoize(char *X, char *Y, int m, int n) {
    int **dp = (int **)malloc((m+1)*sizeof(int *));
    for (int i = 0; i <= m; i++) {
        dp[i] = (int *)malloc((n+1)*sizeof(int));
        for (int j = 0; j <= n; j++)
            dp[i][j] = -1;
    }

    if (dp[m][n] != -1)
        return dp[m][n];
    if (m == 0 || n == 0)
        return 0;
    if (X[m-1] == Y[n-1])
        return dp[m][n] = 1 + memoize(X, Y, m-1, n-1);
    else
        return dp[m][n] = max(memoize(X, Y, m, n-1), memoize(X, Y, m-1, n));
}

int main() {
    printf("Enter the first string: ");
    char X[SIZE]; scanf("%s", X);
    printf("Enter the second string: ");
    char Y[SIZE]; scanf("%s", Y);

    int m = strlen(X), n = strlen(Y);
    printf("\nLength of LCS is %d", tabulate(X, Y, m, n));
    printf("\nLength of LCS is %d", memoize(X, Y, m, n));
    return 0;
}
/*
Enter the first string: ABCDGH
Enter the second string: AEDFHR

Length of LCS is 3
Length of LCS is 3
*/