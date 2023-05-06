#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include <float.h>
#include <string.h>

typedef struct item{
	int p;
	int w;
} item;

int max(int a, int b) {
    return a > b ? a : b;
}

int T, n, p[1010], w[1010], g, i, j, m[110];

int memo[1010][110];

int dp() {
    for (int rc=0; rc <= g; ++rc)
    {
        for (int i = n; i >= 0; --i)
        {
            if(m[rc] == 0 || i == n){
                memo[i][rc] = 0;
            } else if (w[rc] > m[rc]) {
                memo[i][rc] = memo[i+1][rc];
            } else {
                memo[i][rc] = max(p[i] + memo[i+1][rc-w[i]], memo[i+1][rc]);
            }
        }
    }
    return memo[0][g];
}

int main(int argc, char const *argv[])
{

    scanf("%d", &T);

    for (i = 0; i < T; i++)
    {
        scanf("%d", &n);
        for (j = 1; j <= n; j++)
        {
            scanf("%d %d", &p[j], &w[j]);
        }

        scanf("%d", &g);


        for (int k = 0; k < g; k++)
        {
            scanf("%d", &m[k]);
        }

        for(i = 0; i<g; i++){
            memo[n-1][i] = 0;
        }
        
        for(i = 0; i<n; i++){
            memo[i][0] = 0;
        }

        printf("res 1: %d\n", dp());
        
    }
    
    return 0;
}
