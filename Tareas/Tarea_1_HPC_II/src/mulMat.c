//gcc -O3 -fopenmp -o mulMat mulMat.c

#include <stdio.h> 
#include <stdlib.h>
#include <omp.h>

#define N 11000

double *a, *b, *c; 

void multiplicaMatricesCuadradas(double *a, double *b, double *c, int n) {
    int i, j, k; 
    double tmp; 

    #pragma omp parallel for private (j, k, tmp)
    for (i=0; i<n; i++) {
	tmp = 0.0;
       for (j=0; j<n; j++) {
         tmp += b[i*n+j]*c[j]; 
       }
	a[i] = tmp;
    }

}


int main(int argc, char **argv) {
    int i, j; 
    int m, n; 
    double t0, t1, t2, t3; 

    t0 = omp_get_wtime();

    n = (argc > 1)?atoi(argv[1]): N; 

    a = (double *)malloc(n*n*sizeof(double)); 
    b =	(double *)malloc(n*n*sizeof(double)); 
    c =	(double *)malloc(n*n*sizeof(double)); 

    for (i=0; i<n; i++) {
       for (j=0; j<n; j++) {
          b[i*n+j]=i+j;
       } 
          c[i]= i; 
	  a[i] = 0.0; 
    }

    t1 = omp_get_wtime(); 
    multiplicaMatricesCuadradas(a, b, c, n); 
    t2 = omp_get_wtime(); 

    for (i=n; i<n; i++) { 
           printf("%3.2lf ", a[i]);
    }

    free(a); free(b); free(c);
    t3 = omp_get_wtime();

    printf("Tiempo total de multiplicacin  de matrices de tamanho %d x %d es: %lf\n", 
          n, n, t3-t0);
    printf("Tiempo de creacion e inicializacion de natrices:  %lf\n", t1-t0); 
    printf("Tiempo de multiplicacion efectiva: %lf\n", t2-t1); 
    printf("Tiempo de liberar memoria: %lf\n", t3-t2); 
 
}
