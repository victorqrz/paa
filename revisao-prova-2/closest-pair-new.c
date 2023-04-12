#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include <float.h>

typedef struct
{
    float x, y;
} Point;

float min(float x, float y)
{
    return (x < y)? x : y;
}

float dist(Point p1, Point p2)
{
    return sqrt( (p1.x - p2.x)*(p1.x - p2.x) +
                 (p1.y - p2.y)*(p1.y - p2.y)
               );
}

float bruteForce(Point P[], int n)
{
    float min = FLT_MAX;
    for (int i = 0; i < n; ++i)
        for (int j = i+1; j < n; ++j)
            if (dist(P[i], P[j]) < min)
                min = dist(P[i], P[j]);
    return min;
}
 

int compareX(Point p1, Point p2) {
  if (p1.x == p2.x)
    return p1.y < p2.y;

  return p1.x < p2.x;
}

int compareY(Point p1, Point p2) {
  if (p1.y == p2.y)
    return p1.x < p2.x;

  return p1.y <= p2.y;
}

void merge(Point arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
 
    /* create temp arrays */
    Point L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2) {
        if (compareX(L[i], R[j])) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(Point arr[], int l, int r)
{
    if (l < r) {
        
        int m = l + (r - l) / 2;
 
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
 
        merge(arr, l, m, r);
    }
}

//comparação no retângulo de altura d
float stripComparePoints(Point strip[], int size, float d)
{
    float min = d;  

    for (int i = 0; i < size; ++i)
        for (int j = i+1; j < size && (strip[j].y - strip[i].y) < min; ++j)
            if (dist(strip[i],strip[j]) < min)
                min = dist(strip[i], strip[j]);
 
    return min;
}

float comparaPares(Point Px[], Point Py[], int n)
{
    
    if (n <= 3)
        return bruteForce(Px, n);
 
    int mid = n/2;
    Point midPoint = Px[mid];
 
    Point Pyl[mid];
    Point Pyr[n-mid]; 
    int li = 0, ri = 0;

    for (int i = 0; i < n; i++)
    {
      if ((Py[i].x < midPoint.x || (Py[i].x == midPoint.x && Py[i].y < midPoint.y)) && li<mid)
         Pyl[li++] = Py[i];
      else
         Pyr[ri++] = Py[i];
    }

    float dl = comparaPares(Px, Pyl, mid);
    float dr = comparaPares(Px + mid, Pyr, n-mid);
 
    float d = min(dl, dr);
 
    Point strip[n];
    int j = 0;
    for (int i = 0; i < n; i++)
        if (abs(Py[i].x - midPoint.x) < d)
            strip[j] = Py[i], j++;
 
    return stripComparePoints(strip, j, d);
}

float parMaisProximo(Point P[], int n)
{
    Point Px[n];
    Point Py[n];
    for (int i = 0; i < n; i++)
    {
        Px[i] = P[i];
        Py[i] = P[i];
    }
 
    mergeSort(Px, 0, n-1);
    mergeSort(Py, 0, n-1);
 
    return comparaPares(Px, Py, n);
}

int main(void){
  int n, i, k;

  while(1){

    scanf("%d", &n);
    if(n == 0){
      break;
    }

    Point A[n];
    for(i=0; i<n; i++){
      scanf("%f %f", &A[i].x, &A[i].y);
    }    

    float menor = parMaisProximo(A, n);

    (menor > 10000) ? printf("INFINITY") : printf("%.4f", menor); 
  }

  return 0;
}