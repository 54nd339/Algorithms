#include <stdio.h>
#include <stdlib.h>
typedef struct Item {
    int value, weight;
}item;
 
int cmp(const void *a, const void *b) {
    return ((item *)b)->value - ((item *)a)->value;
}
double fractionalKnapsack(int W, item arr[], int n) {
    qsort(arr, n, sizeof(item), cmp);
    double res = 0.0;
 
    for (int i = 0; i < n; i++) {
        if (arr[i].weight <= W) {
            W -= arr[i].weight;
            res += arr[i].value;
        }
        else {
            res += arr[i].value * ((double)W / arr[i].weight);
            break;
        }
    } 
    return res;
}
 
int main() {
    printf("Enter the number of items: ");
    int n; scanf("%d", &n);
    item *arr = malloc(n * sizeof(item));
    printf("Enter the value and weight of each item :\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &arr[i].value, &arr[i].weight);
    }
    printf("Enter the capacity of the knapsack: ");
    int W; scanf("%d", &W);
    printf("Maximum value in a knapsack of capacity %d is %.2lf", W, 
        fractionalKnapsack(W, arr, n));
    return 0;
}

/*
Enter the number of items: 3
Enter the value and weight of each item :
60 10
100 20
120 30
Enter the capacity of the knapsack: 50
Maximum value in a knapsack of capacity 50 is 240.00
*/