#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include <float.h>
#include <string.h>

/* int backtrack(int i, int j, int N, int M, char A[N][M], char answer[N*M], int aux) {

    if(i == N-1 && j == M-1){
        A[i][j] = 'v';
        answer[aux] = 'D';
        aux++;
        return 1;
    }

    if(A[i][j] == '.'){
        if(backtrack(i, j+1, N, M, A, answer, aux) == '.'){
            A[i][j] = '>';
            answer[aux] = 'R';
            aux++;
            return 1;
        }
        if(backtrack(i+1, j, N, M, A, answer, aux) == '.'){
            A[i][j] = 'v';
            answer[aux] = 'D';
            aux++;
            return 1;
        }
        if(backtrack(i-1, j, N, M, A, answer, aux) == '.'){
            A[i][j] = '^';
            answer[aux] = 'U';
            aux++;
            return 1;
        }
        if(backtrack(i, j-1, N, M, A, answer, aux) == '.'){
            A[i][j] = '<';
            answer[aux] = 'L';
            aux++;
            return 1;
        }
    }
} */

int backtrack(int i, int j, int N, int M, char **A, char *answer, int *aux) {

    if (A[i][j] != '.') {
        return 0;
    }

    if (i == N-1 && j == M-1) {
        A[i][j] = 'O';
        return 1;
    }

    if (A[i][j] == '.') {
        if (j < M-1) {
            if(backtrack(i, j+1, N, M, A, answer, aux)){
                A[i][j] = '>';
                answer[(*aux)++] = 'R';
                return 1;
            }
        }
        if (i < N-1) {
            if(backtrack(i+1, j, N, M, A, answer, aux)){
                A[i][j] = 'v';
                answer[(*aux)++] = 'D';
                return 1;
            }
        }
        if (i > 0) {
            if(backtrack(i-1, j, N, M, A, answer, aux)){
                A[i][j] = '^';
                answer[(*aux)++] = 'U';
                return 1;
            }
        }
        if (j > 0) {
            if(backtrack(i, j-1, N, M, A, answer, aux)){
                A[i][j] = '<';
                answer[(*aux)++] = 'L';
                return 1;
            }
        }
    }

    return 0;
}

int main(int argc, char const *argv[])
{
    int N, M, i, j,counter=0;

    scanf("%d %d", &N, &M);
    getchar(); 

    char **tabuleiro = (char**) malloc(N * sizeof(char*));
    char answer[N*M];

    for(i=0; i<N; i++){
        tabuleiro[i] = (char*) malloc((M+1) * sizeof(char));
        for(j=0; j<M; j++){
            scanf(" %c", &tabuleiro[i][j]); 
        }
        tabuleiro[i][M] = '\0';
    }

    backtrack(0, 0, N, M, tabuleiro, answer, &counter);

    for(i=0; i<N; i++){
        for(j=0; j<M; j++){
            printf("%c", tabuleiro[i][j]);
        }
        printf("\n");
    }

    for(i=0; i<N; i++){
        free(tabuleiro[i]);
    }
    free(tabuleiro);


    for(i=counter-1; i>=0; i--){
        printf("%c ", answer[i]);
    }

    return 0;
}
