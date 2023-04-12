#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void construir_tabela_prefixo(char *padrao, int *tabela_prefixo) {
    int i, j, n = strlen(padrao);
    tabela_prefixo[0] = -1;
    i = -1;
    for (j = 1; j < n; j++) {
        while (i >= 0 && padrao[i+1] != padrao[j]) {
            i = tabela_prefixo[i];
        }
        if (padrao[i+1] == padrao[j]) {
            i++;
        }
        tabela_prefixo[j] = i;
    }
}

void busca_kmp(char *texto, char *padrao) {  
    int n = strlen(texto);
    int m = strlen(padrao);
    int *tabela_prefixo = (int*) malloc(sizeof(int) * m);
    construir_tabela_prefixo(padrao, tabela_prefixo);
    int i = -1;
    int encontrado = 0;
    for (int j = 0; j < n; j++) {
        while (i >= 0 && padrao[i+1] != texto[j]) {
            i = tabela_prefixo[i];
        }
        if (padrao[i+1] == texto[j]) {
            i++;
        }
        if (i == m-1) {
            printf("%d\n", j - m + 1);
            i = tabela_prefixo[i];
            encontrado = 1;
        }
    }
    free(tabela_prefixo);
    if (!encontrado) {
        printf("-1\n");
    }
}

int main() {
    char string_target[7000001], padrao[1000001];
    scanf("%s", string_target);
    scanf("%s", padrao);
    busca_kmp(string_target, padrao);
    return 0;
} 