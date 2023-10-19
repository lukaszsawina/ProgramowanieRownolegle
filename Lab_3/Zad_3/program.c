#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define TAB_SIZE 10

typedef struct Osoba {
    int Wiek;
    float Wzrost;
    float Waga;
} Osoba;


void * funkcja_watku_z_wsk(void* atrybut)
{
    Osoba* przekazana_osoba_wsk = (Osoba*) atrybut;

    przekazana_osoba_wsk->Wiek++;
    przekazana_osoba_wsk->Wzrost++;
    przekazana_osoba_wsk->Waga++;

    printf("WSK\tWiek: %d\tWzrost: %f\t Waga: %f\n", przekazana_osoba_wsk->Wiek, przekazana_osoba_wsk->Wzrost, przekazana_osoba_wsk->Waga);

    return(NULL);
}

void * funkcja_watku_z_lok(void* atrybut)
{
    Osoba przekazana_osoba_lok = *(Osoba*) atrybut;

    przekazana_osoba_lok.Wiek++;
    przekazana_osoba_lok.Wzrost++;
    przekazana_osoba_lok.Waga++;

    printf("LOK\tWiek: %d\tWzrost: %f\t Waga: %f\n", przekazana_osoba_lok.Wiek, przekazana_osoba_lok.Wzrost, przekazana_osoba_lok.Waga);

    return(NULL);
}


int main()
{
    pthread_t tid_1, tid_2;
    Osoba osoba_wsk = {20, 183.4, 67.3};
    Osoba osoba_lok = {30, 172.6, 86.4};

    pthread_create(&tid_1, NULL, funkcja_watku_z_wsk, &osoba_wsk);
    pthread_create(&tid_2, NULL, funkcja_watku_z_wsk, &osoba_wsk);

    pthread_join(tid_1, NULL);
    pthread_join(tid_2, NULL);

    pthread_create(&tid_1, NULL, funkcja_watku_z_lok, &osoba_lok);
    pthread_create(&tid_2, NULL, funkcja_watku_z_lok, &osoba_lok);

    pthread_join(tid_1, NULL);
    pthread_join(tid_2, NULL);

    return 0;
}
