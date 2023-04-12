#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include <float.h>

typedef struct
{
    double x, y;
} Point;

float min(float x, float y)
{
    return (x < y)? x : y;
}

void merge(Point arr[], int l, int m, int r, bool is_x)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
 
    Point L[n1], R[n2];
 
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    while (i < n1 && j < n2) {
        if(is_x){
            if (L[i].x <= R[j].x) {
                arr[k] = L[i];
                i++;
            }
            else {
                arr[k] = R[j];
                j++;
            }
            k++;
        } else {
            if (L[i].y <= R[j].y) {
                arr[k] = L[i];
                i++;
            }
            else {
                arr[k] = R[j];
                j++;
            }
            k++;

        }
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

void mergeSort_X(Point arr[], int l, int r)
{
    if (l < r) {
       
        int m = l + (r - l) / 2;
 
        mergeSort_X(arr, l, m);
        mergeSort_X(arr, m + 1, r);
 
        merge(arr, l, m, r, true);
    }
}

void mergeSort_Y(Point arr[], int l, int r)
{
    if (l < r) {
       
        int m = l + (r - l) / 2;
 
        mergeSort_Y(arr, l, m);
        mergeSort_Y(arr, m + 1, r);
 
        merge(arr, l, m, r, false);
    }
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

float stripPointsCheck(Point strip[], int size, float d)
{
    float min = d;

    mergeSort_Y(strip, 0, size - 1);

    for (int i = 0; i < size; ++i)
        for (int j = i+1; j < size && (strip[j].y - strip[i].y) < min; ++j)
            if (dist(strip[i],strip[j]) < min)
                min = dist(strip[i], strip[j]);
 
    return min;
}
 
float parMaisProximo(Point P[], int n)
{

    if (n <= 3)
        return bruteForce(P, n);
 
    int mid = n/2;
    Point midPoint = P[mid];
 
    float dl = parMaisProximo(P, mid);
    float dr = parMaisProximo(P + mid, n-mid);
 
    float d = min(dl, dr);

    Point strip[n];
    int j = 0;
    for (int i = 0; i < n; i++)
        if (abs(P[i].x - midPoint.x) < d)
            strip[j] = P[i], j++;
 
    return min(d, stripPointsCheck(strip, j, d) );
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
      scanf("%lf %lf", &A[i].x, &A[i].y);
    }

    mergeSort_X(A, 0, n-1);    

    float menor = parMaisProximo(A, n);

    (menor > 10000) ? printf("INFINITY\n") : printf("%.4lf\n", menor); 
  }

  return 0;
}