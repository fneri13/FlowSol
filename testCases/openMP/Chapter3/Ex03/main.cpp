#include <omp.h>
#include <stdio.h>
 
long fib ( int n ) { return ( n < 2 ? 1 : fib ( n - 1) + fib ( n - 2) ) ; }

int main(int argc, char* argv[])
{
 
    int n = 10; // starting point of the series
    #pragma omp parallel
    {
        int t = omp_get_thread_num();
        printf("%d, %ld\n", t, fib(n+t));
    }
}