#include <omp.h>
#include <stdio.h>
 
int main(int argc, char* argv[])
{
 
    // Beginning of parallel region
    #pragma omp parallel
    {
 
        printf("Hello, world %d\n", omp_get_thread_num());
    }
    // Ending of parallel region
}