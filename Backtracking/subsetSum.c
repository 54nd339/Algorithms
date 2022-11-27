#include <stdio.h>
#include <stdlib.h>

static int n;
int comparator(const void *a, const void *b) {
    return *(int *)a > *(int *)b;
}
void subsetSum(int *s, int *t, int s_size, int t_size, int sum, int ite, int const target_sum) {
    n++;
    if(target_sum == sum) {
        // for(int i = 0; i < t_size; i++)
        //     printf("%d ",t[i]);
        // printf("\n");
        if(ite + 1 < s_size && sum - s[ite] + s[ite + 1] <= target_sum) {
            subsetSum(s, t, s_size, t_size - 1, sum - s[ite], ite + 1, target_sum);
        }
        return;
    }
    else {
        if(ite < s_size && sum + s[ite] <= target_sum) {
            for(int i = ite; i < s_size; i++) {
                t[t_size] = s[i];
                if( sum + s[i] <= target_sum ) {
                    subsetSum(s, t, s_size, t_size + 1, sum + s[i], i + 1, target_sum);
                }
            }
        }
    }
}

void generateSubsets(int *s, int size, int target_sum) {
    int *tuplet_vector = (int *)malloc(size * sizeof(int));
    int total = 0;
    qsort(s, size, sizeof(int), &comparator);
    for(int i = 0; i < size; i++) {
        total += s[i];
    }
    if(s[0] <= target_sum && total >= target_sum) {
        subsetSum(s, tuplet_vector, size, 0, 0, 0, target_sum);
    }
    free(tuplet_vector);
}

int main() {
    printf("Enter the number of elements in the set: ");
    int size; scanf("%d", &size);
    int *weight = (int *)malloc(size * sizeof(int));
    printf("Enter the elements of the set:\n");
    for(int i = 0; i < size; i++)
        scanf("%d", &weight[i]);

    printf("Enter the target sum: ");
    int target_sum; scanf("%d", &target_sum);
    
    generateSubsets(weight, size, target_sum);
    printf("n = %d\n", n);
    return 0;
}
/*
Enter the number of elements in the set: 8
Enter the elements of the set:
15 22 14 26 32 9 16 8
Enter the target sum: 53
n = 68
*/