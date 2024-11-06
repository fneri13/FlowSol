#include <omp.h>
#include <stdio.h>

double **mtxMul ( double ** c , double ** a , double ** b, int n){
    #pragma omp parallel for collapse (2)
        for ( int i = 0; i < n ; i ++){
            for ( int j = 0; j < n ; j ++){
                c[i][j] = 0.0 ;
                for ( int k = 0; k < n ; k ++){
                    c[i][j] = c [i][j] + a[i][k] * b[k][j];
                }
            }
        } 

    return c;
}

int main(int argc, char* argv[])
{
    int n = 5;
    double **a = new double *[n]; 
    double **b = new double *[n]; 
    double **c = new double *[n];

    for (int i=0; i<n; i++){
        a[i] = new double [n];
        b[i] = new double [n];
        c[i] = new double [n];
    }

    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            a[i][j] = i+j;
            b[i][j] = i-j;
            c[i][j] = 0.0;
        }
    }
    mtxMul(c, a, b, n);
    for (int i=0; i<n; i++){
        printf("[");
        for (int j=0; j<n; j++){
            printf(" %.1f ", c[i][j]);
        }
        printf("]\n");
    }

    return 0;
}
