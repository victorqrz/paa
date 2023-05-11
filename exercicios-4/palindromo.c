#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 1000

int dp[MAX_N][MAX_N];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int t;
    char palavra[MAX_N];
    scanf("%d", &t);
    while (t--) {
        scanf("%s", palavra);
        int n = strlen(palavra);
        if (n == 0) n=1;
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < n; i++) {
            dp[i][i] = 1;
        }
        for (int k = 1; k < n; k++) {
            for (int i = 0; i < n-k; i++) {
                int j = i+k;
                if (palavra[i] == palavra[j]) {
                    dp[i][j] = dp[i+1][j-1] + 2;
                } else {
                    dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
                }
            }
        }
        printf("%d\n", dp[0][n-1]);
    }
    return 0;
}
