#include <iostream>
#include <math.h> 
#include "mpi.h" 

using namespace std;

int main(int argc, char* argv[])
{
    int size, rank, localSum, totalSum, max;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    for (int i = rank + 1; i <= 10; i += size) {
        x = x + 2;
        localSum += x * x;
    }
    totalSum = localSum + 1;

    MPI_Reduce(
        &totalSum, 
        &max, 
        1, 
        MPI_INT, 
        MPI_MAX, 
        0, 
        MPI_COMM_WORLD
    );

    if(rank == 0)
        printf("%d.\n", max);

    MPI_Finalize();

    return EXIT_SUCCESS;
}