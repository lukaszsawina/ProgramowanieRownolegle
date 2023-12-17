#include <stdlib.h>
#include<stdio.h>
#include<math.h>
#include <unistd.h>

#include "mpi.h"

int main( int argc, char** argv ){ 
  
  int rank, ranksent, size, source, dest, tag, value; 
  int pierwszyraz = 0;
  value = 0;
  MPI_Status status;
  
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank ); 
  MPI_Comm_size( MPI_COMM_WORLD, &size );



    while(1){
        
        if( rank == 0 ){ 
            if(value != 0)
            {
                MPI_Recv( &value, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                printf("Proces %d odebrał liczbę %d do procesu %d\n", rank, value, size-1);
            } 

            value++;
            dest=1; tag=0; 
            MPI_Send( &value, 1, MPI_INT, dest, tag, MPI_COMM_WORLD );
            printf("Proces %d wysłał liczbę %d do procesu %d\n", rank, value, dest);

        } else if(rank == size-1) {
        
            MPI_Recv( &value, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status );
            printf("Proces %d odebrał liczbę %d do procesu %d\n", rank, value, rank-1);

            printf("Jestem ostani więc zamykam pierścien i idziemy od nowa \n");
            value++;
            dest=0; tag=0; 
            MPI_Send( &value, 1, MPI_INT, dest, tag, MPI_COMM_WORLD );
            printf("Proces %d wysłał liczbę %d do procesu %d\n", rank, value, dest);
        } else {
            dest=rank+1; tag=0; 

            MPI_Recv( &value, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            printf("Proces %d odebrał liczbę %d do procesu %d\n", rank, value, rank-1);

            value++;
            MPI_Send( &value, 1, MPI_INT, dest, tag, MPI_COMM_WORLD );

            printf("Proces %d wysłał liczbę %d do procesu %d\n", rank, value, dest);
        }
        sleep(1);
      }
  
  MPI_Finalize(); 
  
  return(0);

}

