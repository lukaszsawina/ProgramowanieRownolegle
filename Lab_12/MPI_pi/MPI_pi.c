#include <stdlib.h>
#include<stdio.h>
#include<math.h>
#include <unistd.h>

#include "mpi.h"

int main( int argc, char** argv ){ 
  
  int rank, ranksent, size; 
  
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank ); 
  MPI_Comm_size( MPI_COMM_WORLD, &size );

  int max_liczba_wyrazow=0;
  int root = 0;

  if( rank == root )
  {
    printf("Podaj maksymalną liczbę wyrazów do obliczenia przybliżenia PI\n");
    scanf("%d", &max_liczba_wyrazow);
  } 

  MPI_Bcast( &max_liczba_wyrazow, 1, MPI_INT, root, MPI_COMM_WORLD );

  int n_loc = ceil(max_liczba_wyrazow/size);

  int my_start = rank*n_loc;
  int my_end = (rank + 1) * n_loc;
  if (rank == size - 1) my_end = max_liczba_wyrazow;

  double suma_plus=0.0;
  double suma_minus=0.0;
  int i=0;
  for(i = my_start; i<my_end; i++){  
    int j = 1 + 4*i; 
    suma_plus += 1.0/j;
    suma_minus += 1.0/(j+2.0);
  }

  double pi_approx_lok = 4*(suma_plus-suma_minus);
  double pi_approx = 0.0;

  MPI_Reduce( &pi_approx_lok, &pi_approx, 1, MPI_DOUBLE, MPI_SUM, root, MPI_COMM_WORLD);

  if( rank == root )
  {
    printf("PI obliczone: \t\t\t%20.15lf\n", pi_approx);
    printf("PI z biblioteki matematycznej: \t%20.15lf\n", M_PI);
  } 

  MPI_Finalize(); 
  
  return(0);

}

