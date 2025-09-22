#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv); // Initialize the MPI environment
    
     printf("Output by Ashutosh Shingan\n");

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); // Get the rank of the process

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size); // Get the number of processes

    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len); // Get processor name

    printf("Hello world from processor %s, ID %d out of %d processors\n",
           processor_name, world_rank, world_size);

    MPI_Finalize(); // Finalize the MPI environment
    return 0;
}

