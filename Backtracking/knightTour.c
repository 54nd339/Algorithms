#include <stdio.h>
#include <stdlib.h>

int isSafe(int x, int y, int **sol, int n) {
    return (x >= 0 && x < n && y >= 0 && y < n && sol[x][y] == -1);
}
int solveKTUtil(int x, int y, int movei, int **sol, int n, int *xMove, int *yMove) {
    if (movei == n * n)
        return 1;
    for (int k = 0; k < 8; k++) {
        int next_x = x + xMove[k];
        int next_y = y + yMove[k];
        if (isSafe(next_x, next_y, sol, n)) {
            sol[next_x][next_y] = movei;
            if (solveKTUtil(next_x, next_y, movei + 1, sol, n, xMove, yMove) == 1)
                return 1;
            else
                sol[next_x][next_y] = -1;
        }
    }
}
int **solveKT(int n) {
    int **sol = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        sol[i] = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            sol[i][j] = -1;

    int xMove[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int yMove[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    sol[0][0] = 0;
    if (solveKTUtil(0, 0, 1, sol, n, xMove, yMove) == 0) {
        printf("Solution does not exist\n");
        return NULL;
    }
    return sol;
}

int main() {
    printf("Enter the size of the board: ");
    int n; scanf("%d", &n);

    printf("The solution is:\n");
    int **sol = solveKT(n);
    if (sol != NULL) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                printf("%d\t", sol[i][j]);
            printf("\n");
        }
    }
    return 0;
}
/*
Enter the size of the board: 8
0 59 38 33 30 17 8 63
37 34 31 60 9 62 29 16
58 1 36 39 32 27 18 7
35 48 41 26 61 10 15 28
42 57 2 49 40 23 6 19
47 50 45 54 25 20 11 14
56 43 52 3 22 13 24 5
51 46 55 44 53 4 21 12
*/