#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include <float.h>


int total = 0;

int merge (int v[],int p,int q,int r)
{
    int i,j,k = 0,count = 0;
    int w[r-p];
    i = p;
    j = q;
    while(i < q && j < r)
    {
        if(v[i] <= v[j])
            w[k++] = v[i++];
        else
        {
            w[k++] = v[j++];
            count += q-i;
        }
    }
    while(i < q) w[k++] = v[i++];
    while(j < r) w[k++] = v[j++];
    for (i = p; i < r; i++)
        v[i] = w[i-p];


    return count;
}

int mergesort_n (int v[],int p,int r)
{
    int q,i_esq = 0,i_dir = 0,inter = 0;
    if(p < r-1)
    {
        q = (p+r)/2;
        i_esq = mergesort_n(v,p,q);
        i_dir = mergesort_n(v,q,r);
        inter = merge(v,p,q,r);

    }
    return i_esq + i_dir + inter;
}

int main(void){
  int n, i;

  int A[100000];

  while(1){
    scanf("%d", &n);
    if(n == 0) break;

    for(i=0; i<n; i++){
      scanf("%d", &A[i]);
    }

    int total = mergesort_n(A, 0, n);

    total % 2 == 0 ? printf("Carlos\n") : printf("Marcelo\n");
  }

  return 0;
}