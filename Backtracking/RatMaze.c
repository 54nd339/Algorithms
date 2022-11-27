#include <stdio.h>
#include <stdlib.h>

int isSafe(int x, int y, int **maze, int n) {
    return (x >= 0 && x < n && y >= 0 && y < n && maze[x][y] == 1);
}
int solveMazeUtil(int x, int y, int **sol, int n, int *xMove, int *yMove) {
    if (x == n - 1 && y == n - 1) {
        sol[x][y] = 1;
        return 1;
    }
    for (int k = 0; k < 4; k++) {
        int next_x = x + xMove[k];
        int next_y = y + yMove[k];
        if (isSafe(next_x, next_y, sol, n)) {
            sol[next_x][next_y] = 1;
            if (solveMazeUtil(next_x, next_y, sol, n, xMove, yMove) == 1)
                return 1;
            else
                sol[next_x][next_y] = 0;
        }
    }
    return 0;
}
int **solveMaze(int **maze, int n) {
    int **sol = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        sol[i] = calloc(n, sizeof(int));

    int xMove[4] = {0, 1, 0, -1};
    int yMove[4] = {1, 0, -1, 0};
    if (solveMazeUtil(0, 0, sol, n, xMove, yMove) == 0) {
        printf("Solution does not exist\n");
        return NULL;
    }
    return sol;
}

int main() {
    printf("Enter the size of the maze: ");
    int n; scanf("%d", &n);

    printf("Enter the maze:\n");
    int **maze = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        maze[i] = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &maze[i][j]);

    printf("The solution is:\n");
    int **sol = solveMaze(maze, n);
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
Enter the size of the maze: 4
Enter the maze:
1 0 0 0
1 1 0 1
0 1 0 0
1 1 1 1
The solution is:
1       0       0       0
1       1       0       0
0       1       0       0
0       1       1       1
*/