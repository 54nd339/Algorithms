#include <stdio.h>
int countWays(int n, int m) {
	int res[n + 1], temp = 0;
	res[0] = 1;
	for (int i = 1; i <= n; i++) {
		int s = i - m-1;
		int e = i - 1;
		if (s >= 0)
			temp -= res[s];

		temp += res[e];
		res[i] = temp;
	}
	return res[n];
}

int main() {
    printf("Enter the number of stairs: ");
    int n; scanf("%d", &n);
    printf("Enter the number of steps: ");
    int m; scanf("%d", &m);
    printf("Number of ways to climb %d stairs with %d steps is %d", n, m, countWays(n, m));
	return 0;
}

/*
Enter the number of stairs: 4
Enter the number of steps: 2
Number of ways to climb 4 stairs with 2 steps is 5
*/