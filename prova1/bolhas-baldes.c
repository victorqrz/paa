#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

int main(void){
  int n=0;

  while(scanf("%d", &n) != 0){
    int num, i, j, k, z, jogadas=0;
    int *arr;
    
    scanf("%d", &num);
    
    arr = (int*) malloc(num * sizeof(int));

    for(i=0; i<num; i++){
      scanf(stdin, "%d", &arr[i]);
    }
    
    /* for(j=0; j<num; j++){
      for(k=1; k<num-1; k++){
        if(arr[k]<arr[j] && arr[k] != arr[j] + 1){
          int temp = arr[j];
          arr[j]=arr[k];
          arr[k]=temp;
          jogadas++;
        }
      }
    } */
    for(z=0; z<num; z++){
      printf("%d\n", arr[z]);
    }
    /* if(jogadas % 2 == 0){
      printf("Carlos\n");
    } else {
      printf("Marcelo\n");
    } */
  }

  return 0;
}