#ifndef _bariera_
#define _bariera_

#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

typedef struct 
{
    int liczba_watkow;
    int liczba_watkow_wywolujaca;
    pthread_cond_t cond_v;
    pthread_mutex_t mutex;
} typ_bariery;

#endif