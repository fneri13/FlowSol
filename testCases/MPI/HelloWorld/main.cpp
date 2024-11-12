#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Get the rank of the process
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Print a hello world message from each process
    std::cout << "Hello world from process " << rank << ", out of " << size << " processes!" << std::endl;

    // Finalize the MPI environment
    MPI_Finalize();
    return 0;
}
