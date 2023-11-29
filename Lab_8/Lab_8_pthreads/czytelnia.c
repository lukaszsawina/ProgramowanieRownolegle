#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#include"czytelnia.h"


/*** Implementacja procedur interfejsu ***/

int my_read_lock_lock(czytelnia_t* czytelnia_p){
    pthread_mutex_lock(&czytelnia_p->mutex);

    if(czytelnia_p->liczba_pis > 0 || (czytelnia_p->o_p >0))
    {
    	czytelnia_p->o_c++;
        pthread_cond_wait(&czytelnia_p->cond_c, &czytelnia_p->mutex);
        czytelnia_p->o_c--;
    }
       
    czytelnia_p->liczba_czyt++;
    pthread_cond_signal(&czytelnia_p->cond_c);
    pthread_mutex_unlock(&czytelnia_p->mutex);
}


int my_read_lock_unlock(czytelnia_t* czytelnia_p){
    pthread_mutex_lock(&czytelnia_p->mutex);
    czytelnia_p->liczba_czyt--;

    if(czytelnia_p->liczba_czyt == 0)
        pthread_cond_signal(&czytelnia_p->cond_p);

    pthread_mutex_unlock(&czytelnia_p->mutex);
}


int my_write_lock_lock(czytelnia_t* czytelnia_p){
    pthread_mutex_lock(&czytelnia_p->mutex);

    if((czytelnia_p->liczba_czyt+czytelnia_p->liczba_pis) > 0)
    {
    	czytelnia_p->o_p++;
        pthread_cond_wait(&czytelnia_p->cond_p, &czytelnia_p->mutex);
        czytelnia_p->o_p--;
    }
    czytelnia_p->liczba_pis++;
    pthread_mutex_unlock(&czytelnia_p->mutex);
}


int my_write_lock_unlock(czytelnia_t* czytelnia_p){
    pthread_mutex_lock(&czytelnia_p->mutex);
    czytelnia_p->liczba_pis--;

    if(czytelnia_p->o_c > 0)
        pthread_cond_signal(&czytelnia_p->cond_c);
    else
        pthread_cond_signal(&czytelnia_p->cond_p);

    pthread_mutex_unlock(&czytelnia_p->mutex);
}

void inicjuj(czytelnia_t* czytelnia_p){
    czytelnia_p->liczba_czyt = 0;
    czytelnia_p->liczba_pis = 0;

    pthread_cond_init(&czytelnia_p->cond_c, NULL);
    pthread_cond_init(&czytelnia_p->cond_p, NULL);

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


