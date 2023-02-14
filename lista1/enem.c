#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

int main(void){
  int n=0, i=0, j=0, m=0, k=0, y=0, v=0;

  scanf("%d", &n);

  int cpfs [n];
  int notas [n];

  for(i; i<n; i++){
    scanf("%d", &cpfs[i]);
  }

  for(j; j<n; j++){
    scanf("%d", &notas[j]);
  }

  scanf("%d", &m);
  int testes [m];

  for(v; v<m; v++){ 
    scanf("%d", &testes[v]);
  }

  for(y; y<m; y++){
    int achou = 0;
    for(int z=0; z<n; z++){
      if(cpfs[z] == testes[y]){
          printf("%d\n", notas[z]);
          achou = 1;
      }
    }
    if(!achou){
      printf("NAO SE APRESENTOU\n");
    }
  }

  return 0;
}