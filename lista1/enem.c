#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

/* int binary_search_recursive(int a[], int e, int l, int r) {
  int mid = l + (r-l) / 2;

  if (l > r) return -1;

  if(a[mid] == e)
    return mid;
  else if(a[mid] > e)
    return binary_search(a, e, l, mid - 1);
  else
    return binary_search(a, e, mid + 1, r);
} */

int binary_search_iterative_returning_index(int a[], int e, int l, int r) {
  int flag = -1;

  while (l <= r) {
    int mid = (l + r) / 2;

    if (e == a[mid]){
      return mid;
    } else if (e < a[mid]){
      r = mid-1;
    } else {
      l = mid+1;
    }
  }

  return flag;
}

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
    int index = 0;
    index = binary_search_iterative_returning_index(
      cpfs, 
      testes[y], 
      0, 
      n-1
    );
    if(index == -1){
      printf("NAO SE APRESENTOU\n");
    } else {
      printf("%d\n", notas[index]);
    }
  }

  return 0;
}