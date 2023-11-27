#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#include"czytelnia.h"


/*** Implementacja procedur interfejsu ***/

int my_read_lock_lock(czytelnia_t* czytelnia_p){
    pthread_rwlock_rdlock(&czytelnia_p->lock);
    pthread_mutex_lock(&czytelnia_p->mutex);
    czytelnia_p->liczba_czyt++;
    pthread_mutex_unlock(&czytelnia_p->mutex);
}

int my_read_lock_unlock(czytelnia_t* czytelnia_p){
    pthread_mutex_lock(&czytelnia_p->mutex);
    czytelnia_p->liczba_czyt--;
    pthread_mutex_unlock(&czytelnia_p->mutex);
    pthread_rwlock_unlock(&czytelnia_p->lock);
}


int my_write_lock_lock(czytelnia_t* czytelnia_p){
    pthread_rwlock_wrlock(&czytelnia_p->lock); 
    pthread_mutex_lock(&czytelnia_p->mutex);
    czytelnia_p->liczba_pis++;
    pthread_mutex_unlock(&czytelnia_p->mutex);
}


int my_write_lock_unlock(czytelnia_t* czytelnia_p){
    pthread_mutex_lock(&czytelnia_p->mutex);
    czytelnia_p->liczba_pis--;
    pthread_mutex_unlock(&czytelnia_p->mutex);
    pthread_rwlock_unlock(&czytelnia_p->lock); 

}


void inicjuj(czytelnia_t* czytelnia_p){
    czytelnia_p->liczba_czyt = 0;
    czytelnia_p->liczba_pis = 0;
    pthread_rwlock_init(&czytelnia_p->lock, NULL);
    pthread_mutex_init(&czytelnia_p->mutex, NULL);
}

void czytam(czytelnia_t* czytelnia_p){

// wypisanie wartości zmiennych kontrolujących działanie: liczby czytelników i pisarzy
    printf("Liczba czytających %d, piszących: %d\n", czytelnia_p->liczba_czyt, czytelnia_p->liczba_pis);

// sprawdzenie warunku poprawności i ewentualny exit
    if( czytelnia_p->liczba_pis>1 || (czytelnia_p->liczba_pis==1 && czytelnia_p->liczba_czyt>0) || czytelnia_p->liczba_pis<0 || czytelnia_p->liczba_czyt<0 ) 
    { 
        printf("Warunek czytania niespełniony\n"); exit(0); 
    }

    usleep(rand()%300000);
}

void pisze(czytelnia_t* czytelnia_p){

// wypisanie wartości zmiennych kontrolujących działanie: liczby czytelników i pisarzy
    printf("Liczba czytających %d, piszących: %d\n", czytelnia_p->liczba_czyt, czytelnia_p->liczba_pis);


// sprawdzenie warunku poprawności i ewentualny exit
    if( czytelnia_p->liczba_pis>1 || (czytelnia_p->liczba_pis==1 && czytelnia_p->liczba_czyt>0) || czytelnia_p->liczba_pis<0 || czytelnia_p->liczba_czyt<0 ) 
    { 
        printf("Warunek pisania niespełniony\n"); exit(0); 
    }

    usleep(rand()%300000);
}


