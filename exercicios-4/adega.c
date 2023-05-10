#include <stdio.h>
#include <string.h>

#define MAXN 305

int n, p[MAXN];
int memo[MAXN][MAXN];

int max_profit(int l, int r, int year) {
    if (l > r) return 0;
    if (memo[l][r] != -1) return memo[l][r];
    int left = p[l] * year + max_profit(l+1, r, year+1);
    int right = p[r] * year + max_profit(l, r-1, year+1);
    return memo[l][r] = left > right ? left : right;
}

int main() {
    while (scanf("%d", &n) == 1 && n > 0) {
        memset(memo, -1, sizeof memo);
        for (int i = 0; i < n; i++) {
            scanf("%d", &p[i]);
        }
        printf("%d\n", max_profit(0, n-1, 1));
    }
    return 0;
}
