#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define MAX 100

int N, M;
char labirinto[MAX][MAX];
int visitado[MAX][MAX];

int movimentos[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; 
//CIMA BAIXO ESQUERDA DIREITA

int buscarSolucao(int linha, int coluna) {
    if (linha == N - 1 && coluna == M - 1) {
        return 1;
    }

    visitado[linha][coluna] = 1;

    for (int i = 0; i < 4; i++) {
        int novaLinha = linha + movimentos[i][0];
        int novaColuna = coluna + movimentos[i][1];

        if (novaLinha >= 0 && novaLinha < N && novaColuna >= 0 && novaColuna < M && !visitado[novaLinha][novaColuna] &&
            labirinto[novaLinha][novaColuna] == '.') {
            if (buscarSolucao(novaLinha, novaColuna)) {
                return 1;
            }
        }
    }

    return 0;
}

int main() {
    scanf("%d %d", &N, &M);

    for (int i = 0; i < N; i++) {
        scanf("%s", labirinto[i]);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            visitado[i][j] = 0;
        }
    }

    if (buscarSolucao(0, 0)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}