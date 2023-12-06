#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define WYMIAR 10

int main ()
{
  double a[WYMIAR][WYMIAR];

  for(int i=0;i<WYMIAR;i++) for(int j=0;j<WYMIAR;j++) a[i][j]=1.02*i+1.01*j;

  // podwĂłjna pÄtla - sekwencyjnie
  double suma=0.0;
  for(int i=0;i<WYMIAR;i++) {
    for(int j=0;j<WYMIAR;j++) {
      suma += a[i][j];
    }
  }
  
  printf("Suma wyrazów tablicy: %lf\n", suma);

  omp_set_nested(1);

  double suma_parallel=0.0; int i,j;
  double tab_lok_sum[3];
   for(int i=0;i<3;i++)
      tab_lok_sum[i] = 0;
  
   for(j=0;j<WYMIAR;j++) {
    int id_w = omp_get_thread_num();
    #pragma omp ordered
    #pragma omp parallel for schedule(static,1) default(none) shared(a, tab_lok_sum, j, id_w) ordered
    for(i=0;i<WYMIAR;i++) {
      tab_lok_sum[id_w] += a[i][j];
      #pragma omp ordered
      printf("(%1d,%1d)-W_%1d ",j,i,omp_get_thread_num()); 
    }
    printf("\n");
  }  

  for(i = 0; i < 3; i++)
    suma_parallel += tab_lok_sum[i];

  printf("Suma wyrazów tablicy równolegle: %lf\n", suma_parallel);

}