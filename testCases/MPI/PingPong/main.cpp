#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // This example requires exactly two processes
    if (world_size != 2) {
        std::cerr << "This program requires exactly two processes." << std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    const int PING_PONG_LIMIT = 10;
    int count = 0;
    int partner_rank = (world_rank + 1) % 2;

    while (count < PING_PONG_LIMIT) {
        if (world_rank == count % 2) {
            // If it's this process's turn, increment and send the count
            count++;
            MPI_Send(&count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
            std::cout << "Process " << world_rank << " sent count " << count << " to process " << partner_rank << std::endl;
        } else {
            // If it's the partner's turn, receive the count
            MPI_Recv(&count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            std::cout << "Process " << world_rank << " received count " << count << " from process " << partner_rank << std::endl;
        }
        
        // Use MPI_Barrier to synchronize processes after each send-receive, otherwise the std::cout flushes out stuff in unordered way
        MPI_Barrier(MPI_COMM_WORLD);
    }   


    MPI_Finalize();
    return 0;
}
