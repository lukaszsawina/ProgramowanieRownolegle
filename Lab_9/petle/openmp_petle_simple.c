#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define WYMIAR 18

//Przed uruchomieniem programu w terminalu wpisać
//export OMP_NUM_THREADS=3

int main ()
{
  double a[WYMIAR];

#pragma omp  parallel for default(none) shared(a)
  for(int i=0;i<WYMIAR;i++) a[i]=1.02*i;

  // pÄtla sekwencyjna
  double suma=0.0;
  for(int i=0;i<WYMIAR;i++) {
      suma += a[i];
  }
  
  printf("Suma wyrazów tablicy: %lf\n", suma);

  // pÄtla do modyfikacji - docelowo rĂłwnolegĹa w OpenMP
  double suma_parallel=0.0;
  
  #pragma omp parallel for default(none) shared(a) reduction(+:suma_parallel) ordered
  for(int i=0;i<WYMIAR;i++) {
    int id_w = omp_get_thread_num();
    suma_parallel += a[i];
    #pragma omp ordered
    printf("a[%2d]->W_%1d  \n",i,id_w); 
  }

  printf("\nSuma równolegle: %lf\n",
	 suma_parallel);

}