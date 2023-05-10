#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

int n, counter=0, aux=0, joias[1000001];

int max_3(int n1, int n2, int n3){
  if(n1 > n2){
    if(n1 > n3) return n1;
    else {
      if(n2 > n3) return n2;
      else return n3;
    }
  } else {
    if(n2 > n3) return n2;
    else return n3;
  } 
}

int dp(int i){
  if (i == 0){
    aux+=joias[i];
    return aux;
  } else {
      aux+=joias[i];
      if(i - 3 >= 0){
        dp(i-3);
      } else return aux;
  }
}

int main(void){

  scanf("%d", &n);

  for (int i = 0; i < n; i++)
  {
    scanf("%d", &joias[i]);
  }

  if(n <= 3){
    if(n == 1){
      printf("%d", joias[0]);
    } else if(n == 2){
      printf("%d", max_3(joias[0], joias[1], 0));
    } else {
      printf("%d", max_3(joias[0], joias[1], joias[2]));
    } 
  } else {
    printf("%d %d %d",dp(n-3), dp(n-2), dp(n-1));
  }

  return 0;
}