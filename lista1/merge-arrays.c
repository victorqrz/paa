#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
  int n=0, m=0, i=0, j=0, k=0, x=0, y=0, z=0, aux1, aux2;

  scanf("%d", &n);
  scanf("%d", &m);

  int arr1 [n];
  int arr2 [m];
  int arr3 [n+m];

  for(x=0; x<n; x++){
    scanf("%d", &arr1[x]);
  }
  
  for(y=0; y<m; y++){
    scanf("%d", &arr2[y]);
  }

  while(i<=n && j<=m){
    if(arr1[i] < arr2[j]){
      arr3[k++] = arr1[i++];
    } else {
      arr3[k++] = arr2[j++];
    }
  }

  printf("----------------------------\n");

  for(z; z<n+m; z++){
    printf("%d\n", arr3[z]);
  }
  
  return 0;
}