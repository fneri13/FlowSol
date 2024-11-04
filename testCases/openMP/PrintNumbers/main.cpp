#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("Usage: %s <integer>\n", argv[0]);
        return 1;
    }

    // Convert argv[1] to an integer
    int max = atoi(argv[1]);

    printf("The value of max is: %d\n", max);


    #pragma omp parallel for
        for (int i=0; i<max; i++){
            printf("Thread %d: %d\n", omp_get_thread_num(), i);
        }

    return 0;
}
