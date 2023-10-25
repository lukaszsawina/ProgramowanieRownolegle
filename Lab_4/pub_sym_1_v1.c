#include<stdlib.h>
#include<stdio.h>
#include <time.h>
#include<pthread.h>
#include <unistd.h>

#define ILE_MUSZE_WYPIC 10

void * watek_klient (void * arg);

pthread_mutex_t muteks_kf;
pthread_mutex_t muteks_kr;

int glob_kufle;
int glob_krany;

int main( void ){

  pthread_t *tab_klient;
  int *tab_klient_id;

  int l_kl, l_kf, l_kr, i;

  printf("\nLiczba klientow: "); scanf("%d", &l_kl);

  printf("\nLiczba kufli: "); scanf("%d", &l_kf);

  //printf("\nLiczba kranow: "); scanf("%d", &l_kr);
  l_kr = 1000000000; // wystarczająco dużo, żeby nie było rywalizacji 
  
  pthread_mutex_init( &muteks_kf, NULL);
  pthread_mutex_init( &muteks_kr, NULL);
  
  glob_kufle = l_kf;
  glob_krany = l_kr;

  tab_klient = (pthread_t *) malloc(l_kl*sizeof(pthread_t));
  tab_klient_id = (int *) malloc(l_kl*sizeof(int));
  for(i=0;i<l_kl;i++) tab_klient_id[i]=i;


  printf("\nOtwieramy pub (simple)!\n");
  printf("\nLiczba wolnych kufli %d\n", l_kf); 

  for(i=0;i<l_kl;i++){
    pthread_create(&tab_klient[i], NULL, watek_klient, &tab_klient_id[i]); 
  }
  for(i=0;i<l_kl;i++){
    pthread_join( tab_klient[i], NULL);
  }
  printf("\nZamykamy pub!\n");
  
  if(glob_kufle != l_kf)
    printf("Ilość kufli nie zgadza się na końcu programu\n");

  if(glob_krany != l_kr)
    printf("Ilość kranów nie zgadza się na końcu programu\n");

  printf("\nPozostalo kufli %d\nPozostalo kranow: %d\n",glob_kufle,glob_krany); 
}


void * watek_klient (void * arg_wsk){

  int moj_id = * ((int *)arg_wsk);

  int i, j, kufel, result;
  int ile_musze_wypic = ILE_MUSZE_WYPIC;

  long int wykonana_praca = 0;

  printf("\nKlient %d, wchodzę do pubu\n", moj_id); 
    
  for(i=0; i<ile_musze_wypic; i++){
    pthread_mutex_lock( &muteks_kf );
    if(glob_kufle <= 0) 
    {
      printf("Nie ma już kufli, czekam!\n");
      i--;
      pthread_mutex_unlock( &muteks_kf );
      continue;
    }
    printf("\nKlient %d, wybieram kufel\n", moj_id); 
    if(glob_kufle <= 0) 
      printf("Nie ma już kufli a i tak został zabrany\n");
    glob_kufle--; 
    printf("\nPozostalo kufli %d\n", glob_kufle); 
    pthread_mutex_unlock( &muteks_kf );
            
    j=0;
    pthread_mutex_lock( &muteks_kr );
    printf("\nKlient %d, nalewam z kranu %d\n", moj_id, j); 
    if(glob_krany <= 0) 
      printf("Nie ma już kranów a i tak został zajęty\n");
    glob_krany--;
    printf("\nPozostalo kranow %d\n", glob_krany);

    usleep(30);

    glob_krany++;
    printf("\nPozostalo kranow %d\n", glob_krany); 
    pthread_mutex_unlock( &muteks_kr );
    printf("\nKlient %d, pije\n", moj_id); 
    nanosleep((struct timespec[]){{0, 50000000L}}, NULL);
    
    pthread_mutex_lock( &muteks_kf );
    printf("\nKlient %d, odkladam kufel\n", moj_id); 
    glob_kufle++;
    printf("\nPozostalo kufli %d\n", glob_kufle); 
    pthread_mutex_unlock( &muteks_kf );
  }

  printf("\nKlient %d, wychodzę z pubu; wykonana praca %ld\n",
	 moj_id, wykonana_praca); 
    
  return(NULL);
} 


