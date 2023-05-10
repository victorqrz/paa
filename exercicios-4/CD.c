#include <stdio.h>
#include <stdlib.h>

#define MAX_MUSICAS 20

int max_duracao, num_musicas;
int duracoes[MAX_MUSICAS];
int musica_escolhida[MAX_MUSICAS];

int max(int a, int b) {
  return a > b ? a : b;
}

int escolhe_musicas(int duracao_atual, int indice_atual) {
  if (indice_atual == num_musicas) {
    return 0;
  }

  if (duracao_atual + duracoes[indice_atual] > max_duracao) {
    return escolhe_musicas(duracao_atual, indice_atual + 1);
  }

  int escolhe = escolhe_musicas(duracao_atual + duracoes[indice_atual], indice_atual + 1) + duracoes[indice_atual];
  int nao_escolhe = escolhe_musicas(duracao_atual, indice_atual + 1);

  if (escolhe > nao_escolhe) {
    musica_escolhida[indice_atual] = 1;
    return escolhe;
  } else {
    musica_escolhida[indice_atual] = 0;
    return nao_escolhe;
  }
}

int main() {
  while (scanf("%d %d", &max_duracao, &num_musicas) == 2) {
    for (int i = 0; i < num_musicas; i++) {
      scanf("%d", &duracoes[i]);
      musica_escolhida[i] = 0;
    }

    int duracao_total = escolhe_musicas(0, 0);

    for (int i = 0; i < num_musicas; i++) {
      if (musica_escolhida[i]) {
        printf("%d ", duracoes[i]);
      }
    }

    printf("sum:%d\n", duracao_total);
  }

  return 0;
}
