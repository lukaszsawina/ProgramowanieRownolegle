#define _GNU_SOURCE
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <linux/sched.h>

int zmienna_globalna=0;

#define ROZMIAR_STOSU 1024*64

int funkcja_watku( void* argument )
{
  int i = 0;
  int zmienna_porzekazana = *(int*)argument;

  for(i; i < 1000; i++)
  {
    zmienna_globalna++;
    zmienna_porzekazana++;
  }

  printf("Wartość zmiennej przekazanej do wątku %d na koniec pętli: %d\n", (zmienna_porzekazana-1000)/10, zmienna_porzekazana);
  printf("Wartość zmiennej globalnej na koniec pętli: %d\n\n",zmienna_globalna);

  return 0;
}

int main()
{
  void *stos1;
  void *stos2;
  pid_t pid1;
  pid_t pid2;
  int parametr1 = 10;
  int parametr2 = 20;
  
  stos1 = malloc( ROZMIAR_STOSU );
  if (stos1 == 0) {
    printf("Proces nadrzędny - blad alokacji stosu1\n");
    exit( 1 );
  }

  stos2 = malloc( ROZMIAR_STOSU );
  if (stos2 == 0) {
    printf("Proces nadrzędny - blad alokacji stosu2\n");
    exit( 1 );
  }

  pid1 = clone( &funkcja_watku, (void *) stos1+ROZMIAR_STOSU, 
		 CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, &parametr1 );

  pid2 = clone( &funkcja_watku, (void *) stos2+ROZMIAR_STOSU, 
		 CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, &parametr2 );

  waitpid(pid1, NULL, __WCLONE);
  waitpid(pid2, NULL, __WCLONE);

  printf("Wartość zmiennej przekazanej do wątku 1 na koniec pętli: %d\n", parametr1);
  printf("Wartość zmiennej przekazanej do wątku 2 na koniec pętli: %d\n", parametr2);
  printf("Wartość zmiennej globalnej na koniec pętli: %d\n",zmienna_globalna);

  free( stos1 );
  free( stos2 );
}
