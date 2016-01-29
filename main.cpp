#include <iostream>

#include <mpi/mpi.h>

int main (int argc,char** argv) {
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // Print off a hello world message
    printf("Hello world from processor %s, rank %d"
           " out of %d processors\n",
           processor_name, world_rank, world_size);

    unsigned sum (0);

    for (unsigned j=0;j<500000000;++j) {
        ++sum;
    }

    if (world_rank==0) {
        for (unsigned i=1;i<(unsigned)world_size;++i) {
            unsigned value;
            MPI_Recv(&value, 1, MPI_INT, i, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            sum += value;
        }

        std::cout << "Sum: " << sum << std::endl;
    } else {
        MPI_Send(&sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    // Finalize the MPI environment.
    MPI_Finalize();
};
