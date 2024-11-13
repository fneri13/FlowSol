/*
Compute the communication bandwidth of the message passing between two cores of your laptop using mpi
*/

#include <mpi.h>
#include <iostream>
#include <stdlib.h>
#define NUMBER_OF_TESTS 10  // to perform an average of the results

int main(int argc, char* argv[]) {
    double *buf;
    int rank, numprocs;
    double t1, t2;
    int j, k, nloop;
    
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    
    if (numprocs != 2) {
        printf("The number of processes must be two!\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
        return 0;
    }
    
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    if (rank == 0) {
        printf("\tn\t\ttime [sec]\tRate [Gb/sec]\n");
    }
    
    for (int n = 1; n < 100000000; n *= 2) { // message length doubles
        nloop = 1000000 / n;
        if (nloop < 1) nloop = 1; // just a single loop for long messages
        
        buf = new double [n]; // allocate data in the buffer
        if (!buf) {
            printf("Could not allocate message buffer\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
            return 1;
        }
        
        for (int k = 0; k < NUMBER_OF_TESTS; k++) { // NUMBER_OF_TESTS is assumed to be 10 here
            if (rank == 0) {
                t1 = MPI_Wtime();
                for (int j = 0; j < nloop; j++) { // send message nloop times
                    MPI_Send(buf, n, MPI_DOUBLE, 1, k, MPI_COMM_WORLD);
                }
                t2 = (MPI_Wtime() - t1) / nloop;
            } else if (rank == 1) {
                for (int j = 0; j < nloop; j++) { // receive message nloop times
                    MPI_Recv(buf, n, MPI_DOUBLE, 0, k, MPI_COMM_WORLD, &status);
                }
            }
        }   

        if (rank == 0) { // calculate bandwidth
            double bandwidth = n * sizeof(double) * 1.0e-9 * 8 / t2; // in Gb/sec
            printf("\t%8d\t%10.2e\t%10.2f\n", n, t2, bandwidth);
        }
    
        delete [] buf;  // free data in the buffer
    }
    
    MPI_Finalize();
    return 0;
}
