#ifndef _czytelnia_
#define _czytelnia_

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
/*** Definicje typow zmiennych ***/
typedef struct {
  // <- zasoby czytelni
  int liczba_czyt;
  int liczba_pis;
  pthread_rwlock_t lock;
  pthread_mutex_t mutex;
} czytelnia_t;

/*** Deklaracje procedur interfejsu ***/
void inicjuj(czytelnia_t* czytelnia_p);
void czytam(czytelnia_t* czytelnia_p);
void pisze(czytelnia_t* czytelnia_p);

int my_read_lock_lock(czytelnia_t* czytelnia_p);
int my_read_lock_unlock(czytelnia_t* czytelnia_p);
int my_write_lock_lock(czytelnia_t* czytelnia_p);
int my_write_lock_unlock(czytelnia_t* czytelnia_p);

#endif
