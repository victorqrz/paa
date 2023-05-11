#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include <float.h>
#include <string.h>

void imprimirMaiorDuracao(int** tabela, int* duracoes, int numMusicas, int capacidade) {
    int i = numMusicas;
    int j = capacidade;
    int selecionadas[numMusicas];
    int numSelecionadas = 0;

    while (i > 0 && j > 0) {
        if (tabela[i][j] != tabela[i-1][j]) {
            selecionadas[numSelecionadas] = duracoes[i-1];
            numSelecionadas++;
            j -= duracoes[i-1];
        }
        i--;
    }

    for (int k = numSelecionadas - 1; k >= 0; k--) {
        printf("%d ", selecionadas[k]);
    }
    printf("sum:%d\n", capacidade - j);
}

void encontrarMaiorDuracao(int* duracoes, int numMusicas, int capacidade) {
    int** tabela = (int**)malloc((numMusicas+1) * sizeof(int*));
    for (int i = 0; i <= numMusicas; i++) {
        tabela[i] = (int*)malloc((capacidade+1) * sizeof(int));
    }

    for (int i = 0; i <= numMusicas; i++) {
        for (int j = 0; j <= capacidade; j++) {
            if (i == 0 || j == 0) {
                tabela[i][j] = 0;
            }
            else if (duracoes[i-1] <= j) {
                tabela[i][j] = fmax(duracoes[i-1] + tabela[i-1][j-duracoes[i-1]], tabela[i-1][j]);
            }
            else {
                tabela[i][j] = tabela[i-1][j];
            }
        }
    }

    imprimirMaiorDuracao(tabela, duracoes, numMusicas, capacidade);

    for (int i = 0; i <= numMusicas; i++) {
        free(tabela[i]);
    }
    free(tabela);
}

int main() {
  while(1){
    int capacidade, numMusicas;
    scanf("%d %d", &capacidade, &numMusicas);

    int* duracoes = (int*)malloc(numMusicas * sizeof(int));
    for (int i = 0; i < numMusicas; i++) {
        scanf("%d", &duracoes[i]);
    }

    encontrarMaiorDuracao(duracoes, numMusicas, capacidade);

    free(duracoes);
  }

    return 0;
}
