#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <errno.h>


typedef struct Osoba {
    int Wiek;
    float Wzrost;
    float Waga;
} Osoba;


void * funkcja_watku(void* atrybut)
{
    float x = 1.5f;
    while (1)
    {
        x *= sin(x) / atan(x) * tanh(x) * sqrt(x);
    }

    return(NULL);
}


int main()
{
    pthread_t tid_1;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    cpu_set_t cpuset_1;

    CPU_ZERO(&cpuset_1);
    CPU_SET(4, &cpuset_1);
    pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpuset_1);
    pthread_create(&tid_1, &attr, funkcja_watku, NULL);

    pthread_join(tid_1, NULL);

    pthread_attr_destroy(&attr);
    return 0;
}