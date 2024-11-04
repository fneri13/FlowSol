#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("Usage: %s <integer>\n", argv[0]);
        return 1;
    }

    // Convert argv[1] to an integer
    int max = atoi(argv[1]);

    printf("Max is: %d\n", max);

    std::vector<int> v1 (max, 0);
    std::vector<int> v2 (max, 0);
    std::vector<int> v3 (max, 0);


    #pragma omp parallel for
        for (int i=0; i<max; i++){
            v1.at(i) = i;
            v2.at(i) = i;
            v3.at(i) = v1.at(i) + v2.at(i);
            printf("%d\n", v3.at(i));
        }
    

    return 0;
}
