#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<math.h>

typedef struct CalkowaniePodobszar {
  int ID;
  double a;
  double b;
  double dx;
} CalkowaniePodobszar;

double funkcja ( double x );

double calka_sekw(double a, double b, double dx);

double calka_dekompozycja_obszaru(double a, double b, double dx, int l_w);

void* calka_podobszar_w(void* arg_wsk);

double calka_dekompozycja_obszaru(double a, double b, double dx, int l_w){
  int i;

  //printf("a %lf, b %lf, dx %lf\n", a, b, dx);

  double calka_suma_local = 0.0;

  // tworzenie struktur danych do obsługi wielowątkowości
  pthread_t watki[l_w];
  CalkowaniePodobszar* podobszary = (CalkowaniePodobszar*)malloc(l_w * sizeof(CalkowaniePodobszar));

  int N = ceil((b-a)/l_w);
  // tworzenie wątków
  for(i=0; i<l_w; i++ ) 
  {
      double my_start = a+N*(i);
      double my_end = a+N*(i+1);
      if(my_end > b) my_end = b;

      printf("%lf\n", my_start);

      podobszary[i].a = my_start;
      podobszary[i].b = my_end;
      podobszary[i].dx = dx;
      podobszary[i].ID = i;

    pthread_create( &watki[i], NULL, calka_podobszar_w, &podobszary[i]);
  }


  // oczekiwanie na zakończenie pracy wątków
  void* calka_podobszaru;
  for(i=0; i<l_w; i++ ) {
    pthread_join( watki[i], &calka_podobszaru );
    calka_suma_local += *(double*)calka_podobszaru;
    free(calka_podobszaru);
  }

  free(podobszary);
  
  return(calka_suma_local);
}



void* calka_podobszar_w(void* arg_wsk){
  
  // rozpakowanie danych przesłanych do wątku
  CalkowaniePodobszar* podobszar = (CalkowaniePodobszar *) arg_wsk;
  double a_local = podobszar->a, b_local = podobszar->b, dx=podobszar->dx;

  int my_id = podobszar->ID; // skąd pobierany?
  printf("\nWątek %d: a_local %lf, b_local %lf, dx %lf\n", 
	 my_id, a_local, b_local, dx);

  int N = ceil((b_local-a_local)/dx);
  double dx_adjust = (b_local-a_local)/N;

  printf("Obliczona liczba trapezów: N = %d, dx_adjust = %lf\n", N, dx_adjust);
  //printf("a %lf, b %lf, n %d, dx %.12lf (dx_adjust %.12lf)\n", a, b, N, dx, dx_adjust);
  int i;
  double* calka = malloc(sizeof(double));
  *calka = 0.0;
  for(i=0; i<N; i++){

    double x1 = a_local + i*dx_adjust;
    *calka += (funkcja(x1)+funkcja(x1+dx_adjust));
  }

  *calka *= 0.5*dx_adjust;
  pthread_exit((void*)calka);
}
