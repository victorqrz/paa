#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include <float.h>
#include <string.h>

int calculoDeOtimizacao(int N, int P[], int W[], int MW, int *DP);
void processaCasosDeTeste();
void leituraDaEntrada(int *N, int **precos, int **pesos, int *G);
void liberaMemoria(int *precos, int *pesos, int *DP);

int main() {
    int T;

    scanf("%d", &T);

    for (int i = 0; i < T; i++) {
        processaCasosDeTeste();
    }

    return 0;
}

void processaCasosDeTeste() {
    int N, G, lucroMaximo, lucroTotal = 0;
    int *precos, *pesos, *DP;

    leituraDaEntrada(&N, &precos, &pesos, &G);

    DP = (int *)malloc(10001 * sizeof(int));
    if (DP == NULL) {
        printf("Erro de alocacao de memoria.\n");
        exit(1);
    }

    for (int i = 0; i < G; i++) {
        int MW;
        scanf("%d", &MW);
        lucroMaximo = calculoDeOtimizacao(N, precos, pesos, MW, DP);
        lucroTotal += lucroMaximo;
    }

    printf("%d\n", lucroTotal);

    liberaMemoria(precos, pesos, DP);
}

void leituraDaEntrada(int *N, int **precos, int **pesos, int *G) {
    scanf("%d", N);

    *precos = (int *)malloc(*N * sizeof(int));
    *pesos = (int *)malloc(*N * sizeof(int));

    if (*precos == NULL || *pesos == NULL) {
        printf("Erro de alocacao de memoria.\n");
        exit(1);
    }

    for (int i = 0; i < *N; i++) {
        scanf("%d %d", &(*precos)[i], &(*pesos)[i]);
    }

    scanf("%d", G);
}

int calculoDeOtimizacao(int N, int P[], int W[], int MW, int *DP) {
    int i, j;
    for (i = 0; i <= MW; i++) {
        DP[i] = 0;
    }

    for (i = 0; i < N; i++) {
        for (j = MW; j >= W[i]; j--) {
            if (DP[j - W[i]] + P[i] > DP[j]) {
                DP[j] = DP[j - W[i]] + P[i];
            }
        }
    }

    return DP[MW];
}

void liberaMemoria(int *precos, int *pesos, int *DP) {
    free(precos);
    free(pesos);
    free(DP);
}