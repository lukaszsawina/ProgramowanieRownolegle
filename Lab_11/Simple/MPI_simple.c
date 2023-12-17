#include <stdlib.h>
#include<stdio.h>
#include<math.h>
#include <unistd.h>

#include "mpi.h"

int main( int argc, char** argv ){ 
  
  int rank, ranksent, size, source, dest, tag, i; 
  MPI_Status status;
  
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank ); 
  MPI_Comm_size( MPI_COMM_WORLD, &size );

  char hostname[256];

  if(size>1){
    
    if( rank != 0 ){ dest=0; tag=0; 
      gethostname(hostname, sizeof(hostname));
      MPI_Send( &hostname, 256, MPI_CHAR, dest, tag, MPI_COMM_WORLD );
      
    } else {
      
      for( i=1; i<size; i++ ) { 
	
	MPI_Recv( &hostname, 256, MPI_CHAR, MPI_ANY_SOURCE, 
		  MPI_ANY_TAG, MPI_COMM_WORLD, &status );
	printf("Dane od procesu o randze (status.MPI_SOURCE ->) %d: Nazwa hosta: %s (i=%d)\n", 
	       status.MPI_SOURCE, hostname, i );
      }
      
    }

  }
  else{
	printf("Pojedynczy proces o randze: %d (brak komunikatów)\n", rank);
  }

  
  MPI_Finalize(); 
  
  return(0);

}

