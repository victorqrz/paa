#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n;
    scanf("%d", &n);
    int *joias = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &joias[i]);
    }
    int *dp = malloc(n * sizeof(int));
    dp[0] = joias[0];
    dp[1] = max(joias[0], joias[1]);
    dp[2] = max(max(joias[0], joias[1]), joias[2]);
    for (int i = 3; i < n; i++) {
        dp[i] = max(max(joias[i] + dp[i - 3], dp[i - 2]), dp[i - 1]);
    }
    printf("%d\n", dp[n - 1]);
    free(joias);
    free(dp);
    return 0;
}
