#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include <float.h>
#include <string.h>

typedef struct {
    char nome[26];
    float preco;
} Item;

void encontrarCombinacao(Item* itens, int numItens, Item* combinacaoAtual, int numAtual, float dinheiroRestante, int* maxNumItens, float* maxTroco, Item* melhorCombinacao) {
    if (dinheiroRestante < 0) {
        return;
    }

    if (numItens == 0) {
        if (numAtual > *maxNumItens || (numAtual == *maxNumItens && dinheiroRestante > *maxTroco)) {
            *maxNumItens = numAtual;
            *maxTroco = dinheiroRestante;
            memcpy(melhorCombinacao, combinacaoAtual, numAtual * sizeof(Item));
        }
        return;
    }

    encontrarCombinacao(itens + 1, numItens - 1, combinacaoAtual, numAtual, dinheiroRestante, maxNumItens, maxTroco, melhorCombinacao);
    combinacaoAtual[numAtual] = *itens;
    encontrarCombinacao(itens + 1, numItens - 1, combinacaoAtual, numAtual + 1, dinheiroRestante - itens->preco, maxNumItens, maxTroco, melhorCombinacao);
}

int compararItens(const void* a, const void* b) {
    Item* itemA = (Item*)a;
    Item* itemB = (Item*)b;
    return strcmp(itemA->nome, itemB->nome);
}

int main() {
    float dinheiro;
    scanf("%f", &dinheiro);

    int numItens;
    scanf("%d", &numItens);

    Item* itens = (Item*)malloc(numItens * sizeof(Item));
    for (int i = 0; i < numItens; i++) {
        scanf("%s %f", itens[i].nome, &itens[i].preco);
    }

    qsort(itens, numItens, sizeof(Item), compararItens);

    Item* combinacaoAtual = (Item*)malloc(numItens * sizeof(Item));
    Item* melhorCombinacao = (Item*)malloc(numItens * sizeof(Item));
    int maxNumItens = 0;
    float maxTroco = 0;

    encontrarCombinacao(itens, numItens, combinacaoAtual, 0, dinheiro, &maxNumItens, &maxTroco, melhorCombinacao);

    for (int i = 0; i < maxNumItens; i++) {
        printf("%s %.2f\n", melhorCombinacao[i].nome, melhorCombinacao[i].preco);
    }
    printf("%.2f\n", maxTroco);

    free(itens);
    free(combinacaoAtual);
    free(melhorCombinacao);

    return 0;
}
