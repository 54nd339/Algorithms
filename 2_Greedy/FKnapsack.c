#include <stdio.h>
#include <stdlib.h>
typedef struct Item {
    int value, weight;
}item;
 
void sort(item *a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((double)a[i].value/a[i].weight < 
                (double)a[j].value/a[j].weight) {
                item temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}
 
double fractionalKnapsack(int W, item arr[], int n) {
    sort(arr, n);
    double finalvalue = 0.0;
 
    for (int i = 0; i < n; i++) {
        if (arr[i].weight <= W) {
            W -= arr[i].weight;
            finalvalue += arr[i].value;
        }
        else {
            finalvalue += arr[i].value * ((double)W / arr[i].weight);
            break;
        }
    } 
    return finalvalue;
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