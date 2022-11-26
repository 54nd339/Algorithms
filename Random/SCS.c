// Find the length of shortest common supersequence of two strings using iterative bottom up approach
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define min(a,b) (((a) < (b)) ? (a) : (b))

// int SCS_recur(char *X, char *Y, int m, int n) {
//     if (m == 0 || n == 0)
//         return m + n;
//     if (X[m - 1] == Y[n - 1])
//         return 1 + find_scs(X, Y, m - 1, n - 1);
// 
//     return 1 + min(find_scs(X, Y, m - 1, n), find_scs(X, Y, m, n - 1));
// }

int SCS_memoized(char *X, char *Y, int m, int n, int **dp) {
    if (m == 0 || n == 0) return m + n;
    if (dp[m][n] != -1) return dp[m][n];

    if (X[m - 1] == Y[n - 1])
        return dp[m][n] = 1 + SCS(X, Y, m - 1, n - 1, dp);

    return dp[m][n] = 1 + min(SCS(X, Y, m - 1, n, dp), SCS(X, Y, m, n - 1, dp));
}

// int SCS_tabulated(char *X, char *Y, int m, int n) {
//     int dp[m + 1][n + 1];
//     for (int i = 0; i <= m; i++) {
//         for (int j = 0; j <= n; j++) {
//             if (i == 0 || j == 0) dp[i][j] = i + j;
//             else if (X[i - 1] == Y[j - 1]) dp[i][j] = 1 + dp[i - 1][j - 1];
//             else dp[i][j] = 1 + min(dp[i - 1][j], dp[i][j - 1]);
//         }
//     }
//     return dp[m][n];
// }

int main() {
    char *str1 = "ABCBDAB";
    char *str2 = "BDCABA";
    int m = strlen(str1);
    int n = strlen(str2);
    printf("Length of shortest common supersequence is %d", SCS_tabulated(str1, str2, m, n));
    return 0;
}