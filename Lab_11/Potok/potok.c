#include <stdlib.h>
#include<stdio.h>
#include<math.h>
#include <unistd.h>
#include <ctype.h>

#include "mpi.h"


int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    struct {
        int next;
        double val;
        char name[30];
        int liczba_duzych;
        int liczba_malych;
        int liczba_spacji;

    } dane, odebrane_dane;

    dane.next = 1;
    dane.val = 10.10*rank;
    sprintf(dane.name, "Hello, World!");

    MPI_Aint packed_size;
    MPI_Pack_size(1, MPI_INT, MPI_COMM_WORLD, &packed_size);

    int buffer_size = 100;
    char buffer[buffer_size];
    int position = 0; 

    MPI_Pack(&dane.next, 1, MPI_INT, buffer, buffer_size, &position, MPI_COMM_WORLD);
    MPI_Pack(&dane.val, 1, MPI_DOUBLE, buffer, buffer_size, &position, MPI_COMM_WORLD);
    MPI_Pack(dane.name, 30, MPI_CHAR, buffer, buffer_size, &position, MPI_COMM_WORLD);
    MPI_Pack(&dane.liczba_duzych, 1, MPI_INT, buffer, buffer_size, &position, MPI_COMM_WORLD);
    MPI_Pack(&dane.liczba_malych, 1, MPI_INT, buffer, buffer_size, &position, MPI_COMM_WORLD);
    MPI_Pack(&dane.liczba_spacji, 1, MPI_INT, buffer, buffer_size, &position, MPI_COMM_WORLD);

    if( rank == 0 ){ 

        MPI_Aint packed_size;
        MPI_Pack_size(1, MPI_INT, MPI_COMM_WORLD, &packed_size);

        int buffer_size = 100;
        char buffer[buffer_size];
        int position = 0; 

        MPI_Send(buffer, position, MPI_PACKED, 1, 0, MPI_COMM_WORLD);
        printf("Proces %d wysłał liczbę %lf do procesu %d\n", rank, dane.val, dane.next);
        dane.val = 1.0;

        } else if(rank == size-1) {
        
            MPI_Recv(buffer, buffer_size, MPI_PACKED, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            position = 0;
            MPI_Unpack(buffer, buffer_size, &position, &odebrane_dane.next, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Unpack(buffer, buffer_size, &position, &odebrane_dane.val, 1, MPI_DOUBLE, MPI_COMM_WORLD);
            MPI_Unpack(buffer, buffer_size, &position, odebrane_dane.name, 20, MPI_CHAR, MPI_COMM_WORLD);
            MPI_Unpack(buffer, buffer_size, &position, &odebrane_dane.liczba_duzych, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Unpack(buffer, buffer_size, &position, &odebrane_dane.liczba_malych, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Unpack(buffer, buffer_size, &position, &odebrane_dane.liczba_spacji, 1, MPI_INT, MPI_COMM_WORLD);

            printf("Proces %d odebrał liczbę %lf do procesu %d\n", rank, odebrane_dane.val, rank-1);

            printf("Małych liter: %d, Dużych liter: %d, spacji: %d\n", odebrane_dane.liczba_malych, odebrane_dane.liczba_duzych, odebrane_dane.liczba_spacji);

        } else {
            MPI_Recv(buffer, buffer_size, MPI_PACKED, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            position = 0;
            MPI_Unpack(buffer, buffer_size, &position, &odebrane_dane.next, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Unpack(buffer, buffer_size, &position, &odebrane_dane.val, 1, MPI_DOUBLE, MPI_COMM_WORLD);
            MPI_Unpack(buffer, buffer_size, &position, odebrane_dane.name, 20, MPI_CHAR, MPI_COMM_WORLD);
            MPI_Unpack(buffer, buffer_size, &position, &odebrane_dane.liczba_duzych, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Unpack(buffer, buffer_size, &position, &odebrane_dane.liczba_malych, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Unpack(buffer, buffer_size, &position, &odebrane_dane.liczba_spacji, 1, MPI_INT, MPI_COMM_WORLD);


            printf("Proces %d odebrał liczbę %lf do procesu %d\n", rank, odebrane_dane.val, rank-1);
            printf("%s\n", odebrane_dane.name);

            switch (rank)
            {
            case 1:
                {
                    for (int i = 0; odebrane_dane.name[i] != '\0'; ++i) {
                        
                        if (isupper(odebrane_dane.name[i])) {
                            odebrane_dane.liczba_duzych++;
                        }
                    }
                }
                break;
            case 2:
                {
                    for (int i = 0; odebrane_dane.name[i] != '\0'; ++i) {
                        
                        if (!isupper(odebrane_dane.name[i])) {
                            odebrane_dane.liczba_malych++;
                        }
                    }
                }
                break;
            case 3:
                {
                    for (int i = 0; odebrane_dane.name[i] != '\0'; ++i) {
                        
                        if (odebrane_dane.name[i] == ' ') {
                            odebrane_dane.liczba_spacji++;
                        }
                    }
                }
                break;
            default:
                break;
            }


            dane.next = rank+1;
            dane.val = 10.10 * rank;
            dane.liczba_duzych = odebrane_dane.liczba_duzych;
            dane.liczba_malych = odebrane_dane.liczba_malych;
            dane.liczba_spacji = odebrane_dane.liczba_spacji;

            MPI_Aint packed_size;
            MPI_Pack_size(1, MPI_INT, MPI_COMM_WORLD, &packed_size);

            int buffer_size = 100;
            char buffer[buffer_size];
            int position = 0; 

            MPI_Pack(&dane.next, 1, MPI_INT, buffer, buffer_size, &position, MPI_COMM_WORLD);
            MPI_Pack(&dane.val, 1, MPI_DOUBLE, buffer, buffer_size, &position, MPI_COMM_WORLD);
            MPI_Pack(dane.name, 20, MPI_CHAR, buffer, buffer_size, &position, MPI_COMM_WORLD);
            MPI_Pack(&dane.liczba_duzych, 1, MPI_INT, buffer, buffer_size, &position, MPI_COMM_WORLD);
            MPI_Pack(&dane.liczba_malych, 1, MPI_INT, buffer, buffer_size, &position, MPI_COMM_WORLD);
            MPI_Pack(&dane.liczba_spacji, 1, MPI_INT, buffer, buffer_size, &position, MPI_COMM_WORLD);

            MPI_Send(buffer, position, MPI_PACKED, dane.next, 0, MPI_COMM_WORLD);
            printf("Proces %d wysłał liczbę %lf do procesu %d\n", rank, dane.val, dane.next);
        }

        sleep(1);

    MPI_Finalize();

    return 0;
}
