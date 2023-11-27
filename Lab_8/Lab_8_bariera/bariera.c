#include "bariera.h"

void bariera_init(int l_w, typ_bariery* tb)
{
    tb->liczba_watkow = l_w;
    tb->liczba_watkow_wywolujaca = 0;
    pthread_cond_init(&tb->cond_v, NULL);
    pthread_mutex_init(&tb->mutex, NULL);
}

void bariera(typ_bariery* tb)
{
    pthread_mutex_lock(&tb->mutex);
    tb->liczba_watkow_wywolujaca++;

    if(tb->liczba_watkow > tb->liczba_watkow_wywolujaca)
    {
        pthread_cond_wait(&tb->cond_v, &tb->mutex);
    }
    else
    {
        pthread_cond_broadcast(&tb->cond_v);
        tb->liczba_watkow_wywolujaca = 0;
    }

    pthread_mutex_unlock(&tb->mutex);
}