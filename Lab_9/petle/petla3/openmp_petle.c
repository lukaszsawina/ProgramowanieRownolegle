#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define WYMIAR 10

int main ()
{
  double a[WYMIAR][WYMIAR];

  for(int i=0;i<WYMIAR;i++) for(int j=0;j<WYMIAR;j++) a[i][j]=1.02*i+1.01*j;


  double suma=0.0;
  for(int i=0;i<WYMIAR;i++) {
    for(int j=0;j<WYMIAR;j++) {
      suma += a[i][j];
    }
  }
  
  printf("Suma wyrazów tablicy: %lf\n", suma);

  omp_set_nested(1);

  // podwĂłjna pÄtla - docelowo rĂłwnolegle
  double suma_parallel=0.0; int i,j;

  
  #pragma omp parallel for schedule(static) default(none) shared(suma_parallel, a) private(i) ordered
  for(j=0;j<WYMIAR;j++) {
    int id_w = omp_get_thread_num();
    double suma_temp=0.0;
    for(i=0;i<WYMIAR;i++) {
      suma_temp += a[i][j];
      #pragma omp ordered
      printf("(%1d,%1d)-W_%1d ",j,i,omp_get_thread_num()); 
    }

    #pragma omp critival
    suma_parallel += suma_temp;

    #pragma omp ordered
    printf("\n");
  }

  
  printf("Suma wyrazów tablicy równolegle: %lf\n", suma_parallel);

}