/*
Compute the communication bandwidth of the message passing between two cores of your laptop using mpi
*/

#include <mpi.h>
#include <iostream>
#include <stdlib.h>


int main(int argc, char* argv[]) {
    int done = 0, n, myid, numprocs, i;
    const double PI25DT = 3.141592653589793238462643;
    double pi, h, sum, x, start, finish;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    for (int n=100; n<=1000000000; n*=10){
        if (myid == 0) {
        start = MPI_Wtime();
        }

        // Broadcast `n` to all processes
        MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
        if (n == 0) {
            done = 1;
            break;
        }

        h = 1.0 / static_cast<double>(n);
        sum = 0.0;

        // Each process calculates part of the sum
        for (i = myid + 1; i <= n; i += numprocs) {
            x = h * (static_cast<double>(i) - 0.5);
            sum += 4.0 * h * sqrt(1.0 - x * x);
        }

        // Sum up all partial sums from each process into `pi` at root
        MPI_Reduce(&sum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

        if (myid == 0) {
            finish = MPI_Wtime();
            printf("With %i bins Pi is approximately %.16f -> Rel. Error is %12.8e\n", n , pi, (fabs(pi - PI25DT)/PI25DT));
            printf("Elapsed time: %12.8e seconds\n\n", finish - start);
        }
    }

    MPI_Finalize();
    return 0;
}
