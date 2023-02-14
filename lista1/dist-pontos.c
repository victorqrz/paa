#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
  double x;
  double y;
} Ponto;

int main(void){
  int n, i=0;
  double d = INFINITY;

  scanf("%d", &n);

  Ponto pontos[n];

  for(i; i<n; i++){
    scanf("%lf %lf", &pontos[i].x, &pontos[i].y);
  }

  for(int k=0; k<n; k++){
    for(int j=k+1; j<n; j++){
      double expression = sqrt(pow(pontos[k].x - pontos[j].x ,2) + pow(pontos[k].y - pontos[j].y ,2));
      if(expression < d)
        d = expression;
    }
  }

  printf("%.4lf", d);

  return 0;
}