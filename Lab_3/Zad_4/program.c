#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h> 

typedef struct Osoba {
    int Wiek;
    float Wzrost;
    float Waga;
} Osoba;


void * funkcja_watku(void* atrybut)
{
    Osoba* przekazana_osoba_wsk = (Osoba*) atrybut;


    printf("Wiek: %d\tWzrost: %f\t Waga: %f\n", przekazana_osoba_wsk->Wiek, przekazana_osoba_wsk->Wzrost, przekazana_osoba_wsk->Waga);

    sleep(10);

    return(NULL);
}



int main()
{
    pthread_t tid_1, tid_2;
    pthread_attr_t attr_1, attr_2;
    struct sched_param param_1, param_2;

    Osoba osoba_wsk_1 = {20, 183.4, 67.3};
    Osoba osoba_wsk_2 = {30, 183.4, 67.3};

    pthread_attr_init(&attr_1);
    pthread_attr_init(&attr_2);

    param_1.sched_priority = 40;  // Wyższy priorytet
    param_2.sched_priority = 60;  // Niższy priorytet

    pthread_attr_setschedparam(&attr_1, &param_1);
    pthread_attr_setschedparam(&attr_2, &param_2);


    pthread_create(&tid_1, &attr_1, funkcja_watku, &osoba_wsk_1);
    pthread_create(&tid_2, &attr_2, funkcja_watku, &osoba_wsk_2);

    pthread_join(tid_1, NULL);
    pthread_join(tid_2, NULL);

    pthread_attr_destroy(&attr_1);
    pthread_attr_destroy(&attr_2);

    return 0;
}