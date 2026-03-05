#include <omp.h>
#include <stdio.h>

// Definición de macro para indexación 2D en arreglo 1D
#define INDEX(i, j, n) ((i) * (n) + (j))

void mat_mul(double *A, double *B, double *C, int n) {
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < n; j++) {
                C[INDEX(i,j,n)] += A[INDEX(i,k,n)] * B[INDEX(k,j,n)];
            }
        }
    }
}
