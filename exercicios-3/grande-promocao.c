#include <stdio.h>
#include <stdlib.h>

// Lucro maximo
int calculateMaximumProfit(int N, int P[], int W[], int MW, int *DP)
{
    int i, j;
    for (i = 0; i <= MW; i++)
    {
        DP[i] = 0;
    }

    // Itens e pesos
    for (i = 0; i < N; i++)
    {
        for (j = MW; j >= W[i]; j--)
        {
            // Atualizando o valor maximo de lucro possivel para o peso
            if (DP[j - W[i]] + P[i] > DP[j])
            {
                DP[j] = DP[j - W[i]] + P[i];
            }
        }
    }
    // Valor maximo de lucro para MW da mochila
    return DP[MW];
}

int main()
{
    int T, i, j;

    scanf("%d", &T);

    // Processando cada caso de teste
    while (T--)
    {
        int N, MW, G, maxProfit, totalProfit = 0;
        int *prices, *weights, *DP;

        scanf("%d", &N);

        // tentando dinamico
        prices = (int *)malloc(N * sizeof(int));
        weights = (int *)malloc(N * sizeof(int));
        DP = (int *)malloc(10001 * sizeof(int));

        // Precos e Pesos dos itens
        for (i = 0; i < N; i++)
        {
            scanf("%d %d", &prices[i], &weights[i]);
        }

        scanf("%d", &G);

        for (i = 0; i < G; i++)
        {
            scanf("%d", &MW);
            maxProfit = calculateMaximumProfit(N, prices, weights, MW, DP);
            totalProfit += maxProfit;
        }

        printf("%d\n", totalProfit);

        free(prices);
        free(weights);
        free(DP);
    }

    return 0;
}