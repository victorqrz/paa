#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include <float.h>
#include <string.h>

typedef struct {
    int inicio;
    int fim;
} Consulta;

int compararHorarios(const void* a, const void* b) {
    Consulta* consultaA = (Consulta*)a;
    Consulta* consultaB = (Consulta*)b;
    return consultaA->fim - consultaB->fim;
}

int agendarConsultas(Consulta consultas[], int numConsultas) {
    qsort(consultas, numConsultas, sizeof(Consulta), compararHorarios);

    int numMaxConsultas = 1;
    int ultimoFim = consultas[0].fim;

    for (int i = 1; i < numConsultas; i++) {
        if (consultas[i].inicio >= ultimoFim) {
            numMaxConsultas++;
            ultimoFim = consultas[i].fim;
        }
    }

    return numMaxConsultas;
}

int main() {
    int numConsultas;
    scanf("%d", &numConsultas);

    Consulta* consultas = (Consulta*)malloc(numConsultas * sizeof(Consulta));
    for (int i = 0; i < numConsultas; i++) {
        scanf("%d %d", &consultas[i].inicio, &consultas[i].fim);
    }

    int maxConsultas = agendarConsultas(consultas, numConsultas);

    printf("%d\n", maxConsultas);

    free(consultas);

    return 0;
}
