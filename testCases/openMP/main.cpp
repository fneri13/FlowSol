#include <omp.h>
#include <iostream>

int main() {
    const int size = 1000;
    int a[size], b[size], result[size];

    // Initialize arrays a and b
    for (int i = 0; i < size; i++) {
        a[i] = i;
        b[i] = i * 2;
    }

    // Parallelize the following loop using OpenMP
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        result[i] = a[i] + b[i];  // Each thread will handle part of the loop
    }

    // Print some of the results
    std::cout << "Result[500] = " << result[500] << std::endl;

    return 0;
}
