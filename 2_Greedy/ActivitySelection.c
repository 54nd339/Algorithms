#include <stdio.h>
#include <stdlib.h>

typedef struct Activity {
    int ind, start, finish;
}act;
int cmp(const void *a, const void *b) {
    act *x = (act *)a;
    act *y = (act *)b;
    return x->finish - y->finish;
}

int main() {
    printf("Enter the number of activities : ");
    int n; scanf("%d", &n);
    act *arr = malloc(n * sizeof(act));
    printf("Enter the start and finish time of each activity :\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &arr[i].start, &arr[i].finish);
        arr[i].ind = i + 1;
    }
    qsort(arr, n, sizeof(act), cmp);

    printf("The activities selected are:\nIndex\tStart\tFinish");
    int i = 0;
    printf("\n%d\t%d\t%d", arr[i].ind, arr[i].start, arr[i].finish);
    for (int j = 1; j < n; j++) {
        if (arr[j].start >= arr[i].finish) {
            printf("\n%d\t%d\t%d", arr[j].ind, arr[j].start, arr[j].finish);
            i = j;
        }
    }
    return 0;
}

/*
Enter the number of activities : 6
Enter the start and finish time of each activity :
1 2
3 4
0 6
5 7
8 9
5 9
The activities selected are:
Index   Start   Finish
1       1       2
4       5       7
8       8       9
*/