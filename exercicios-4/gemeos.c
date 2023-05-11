#include <stdio.h>
#include <stdlib.h>

// Função de comparação para o qsort
int compara(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int encontrarMenorQuantidade(int n, int *moedas) {
    // Ordena as moedas em ordem crescente
    qsort(moedas, n, sizeof(int), compara);

    int somaTotal = 0;
    for (int i = 0; i < n; i++) {
        somaTotal += moedas[i];
    }

    int metadeSomaTotal = somaTotal / 2;

    int quantidadeMoedas = 0;
    int somaAtual = 0;

    for (int i = n - 1; i >= 0; i--) {
        somaAtual += moedas[i];
        quantidadeMoedas++;

        if (somaAtual > metadeSomaTotal) {
            break;
        }
    }

    return quantidadeMoedas;
}

int main() {
    int n;
    scanf("%d", &n);

    int *moedas = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d", &moedas[i]);
    }

    int resultado = encontrarMenorQuantidade(n, moedas);
    printf("%d\n", resultado);

    free(moedas);

    return 0;
}
