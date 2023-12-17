#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>

typedef struct {
    int next;
    double val;
    char name[30];
} Data;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    Data wyslane, odebrane;

    wyslane.next = (rank + 1) % size;
    wyslane.val = 10.10 * rank;
    snprintf(wyslane.name, sizeof(wyslane.name), "Hello from process %d", rank);

    MPI_Datatype Data_Type;
    int blocklengths[3] = {1, 1, 30};  // Liczba elementów w każdym bloku
    MPI_Aint displacements[3];
    MPI_Datatype types[3] = {MPI_INT, MPI_DOUBLE, MPI_CHAR};

    MPI_Get_address(&wyslane.next, &displacements[0]);
    MPI_Get_address(&wyslane.val, &displacements[1]);
    MPI_Get_address(wyslane.name, &displacements[2]);

    // Obliczenie przesunięć względem początku struktury
    displacements[2] -= displacements[0];
    displacements[1] -= displacements[0];
    displacements[0] = 0;

    MPI_Type_create_struct(3, blocklengths, displacements, types, &Data_Type);
    MPI_Type_commit(&Data_Type);

    while (1) {
        if (rank == 0) {
            // Proces 0 odbiera dane od ostatniego procesu
            if (wyslane.val != 0.0) {
                MPI_Recv(&odebrane, 1, Data_Type, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                printf("Proces %d odebrał liczbę %lf od procesu %d\n", rank, odebrane.val, size - 1);
                printf("%s\n", odebrane.name);
            }

            // Inicjalizacja nowych danych
            wyslane.next = (rank + 1) % size;
            wyslane.val = 10.10 * rank;
            snprintf(wyslane.name, sizeof(wyslane.name), "Hello from process %d", rank);

            // Wysłanie danych do następnego procesu
            MPI_Send(&wyslane, 1, Data_Type, wyslane.next, 0, MPI_COMM_WORLD);
            printf("Proces %d wysłał liczbę %lf do procesu %d\n", rank, wyslane.val, wyslane.next);
            wyslane.val = 1.0;

        } else if (rank == size - 1) {
            // Ostatni proces odbiera dane od poprzedniego procesu
            MPI_Recv(&odebrane, 1, Data_Type, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Proces %d odebrał liczbę %lf od procesu %d\n", rank, odebrane.val, rank - 1);
            printf("%s\n", odebrane.name);

            // Inicjalizacja nowych danych
            wyslane.next = 0;
            wyslane.val = 10.10 * rank;
            snprintf(wyslane.name, sizeof(wyslane.name), "Hello from process %d", rank);

            // Wysłanie danych do procesu 0
            MPI_Send(&wyslane, 1, Data_Type, 0, 0, MPI_COMM_WORLD);

        } else {
            // Procesy pośrednie odbierają dane od poprzedniego procesu
            MPI_Recv(&odebrane, 1, Data_Type, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Proces %d odebrał liczbę %lf od procesu %d\n", rank, odebrane.val, rank - 1);
            printf("%s\n", odebrane.name);

            // Inicjalizacja nowych danych
            wyslane.next = (rank + 1) % size;
            wyslane.val = 10.10 * rank;
            snprintf(wyslane.name, sizeof(wyslane.name), "Hello from process %d", rank);

            // Wysłanie danych do następnego procesu
            MPI_Send(&wyslane, 1, Data_Type, wyslane.next, 0, MPI_COMM_WORLD);
            printf("Proces %d wysłał liczbę %lf do procesu %d\n", rank, wyslane.val, wyslane.next);
        }

        sleep(1);
        MPI_Barrier(MPI_COMM_WORLD);
    }

    MPI_Type_free(&Data_Type);
    MPI_Finalize();

    return 0;
}
