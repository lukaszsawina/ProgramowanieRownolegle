#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define TAB_SIZE 10



void * funkcja_watku(void* atrybut)
{
    int Wlasne_ID = *(int*) atrybut;
    pthread_t System_ID = pthread_self();
    printf("Systemowy ID: %lu\tWłasny ID:%d\n",(unsigned long)System_ID, Wlasne_ID);

    return(NULL);
}

int main()
{
    pthread_t tid_tab[TAB_SIZE];
    int index[TAB_SIZE] = {0};
    int i;
    void *wynik;

    for(i = 0; i < TAB_SIZE; i++)
    {
        index[i] = i;
        printf("Utworzono wątek o wewnętrzynm ID: %d\n",index[i]);
        pthread_create(&tid_tab[i], NULL, funkcja_watku, &i);
    }

    for(i = 0; i < TAB_SIZE; i++)
    {
        pthread_join(tid_tab[i], &wynik);
    }

    return 0;
}