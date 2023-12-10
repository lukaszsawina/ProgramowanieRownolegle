#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void mat_vec_row(double* a, double* x, double* y, int n)
{
  int i,j;

  for(i=0;i<n;i++){
    y[i]=0.0;
    for(j=0;j<n;j++){
      y[i]+=a[n*i+j]*x[j];
    }
  } 
}

void mat_vec_row_row_decomp(double* a, double* x, double* y, int n)
{
  int i,j;

#pragma omp parallel for default(none) private(j) shared(a, n) firstprivate(y,x)
  for(i=0;i<n;i++){
    y[i]=0.0;
    for(j=0;j<n;j++){
      y[i]+=a[n*i+j]*x[j];
    }
  }  
}

void mat_vec_row_col_decomp(double* a, double* x, double* y, int n)
{
  int i,j;

  for(i=0;i<n;i++){
    double temp_y = 0.0;

    #pragma omp parallel for default(none) reduction(+:temp_y) shared(a, x, n, i) private(j)
    for(j = 0; j < n; j++) {
      temp_y += a[n * i + j] * x[j];
    }
    #pragma omp critical
    y[i] = temp_y;
  }  
}

void mat_vec_col(double* a, double* x, double* y, int n)
{
  
  int i,j;

  for(i=0;i<n;i++) y[i]=0.0;
  for(j=0;j<n;j++){
    for(i=0;i<n;i++){
      y[i]+=a[i+j*n]*x[j];
    }
  } 
}

void mat_vec_col_col_decomp(double* a, double* x, double* y, int n)
{
  
  int i,j;
#pragma omp parallel default(none) private(i, j) shared(a, x, y, n)
{
  double *y_local = malloc(n * sizeof(double));

   #pragma omp for
    for(i = 0; i < n; i++) {
        y_local[i] = 0.0;
    }

  #pragma omp for
  for(j=0;j<n;j++){
    for(i=0;i<n;i++){
      y_local[i]+=a[i+j*n]*x[j];
    }
  }

  #pragma omp critical
  {
      for(i = 0; i < n; i++) {
          y[i] += y_local[i];
      }
  }
}

}

void mat_vec_col_row_decomp(double* a, double* x, double* y, int n)
{
  int i,j;

  for(i=0;i<n;i++) y[i]=0.0;
  for(j=0;j<n;j++){
    for(i=0;i<n;i++){
      y[i]+=a[i+j*n]*x[j];
    }
  } 
}

