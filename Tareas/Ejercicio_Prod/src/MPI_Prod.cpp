#include <iostream>
#include <math.h> 
#include "mpi.h" 

using namespace std;
 
int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    int size;

    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(size != 7) {
        printf("Esta aplicación está hecha para 7 procesos.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    int currentRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentRank);

    int sum = currentRank + 1;
    int result = 0;

    MPI_Reduce(
        &sum, 
        &result, 
        1, 
        MPI_INT, 
        MPI_PROD, 
        0, 
        MPI_COMM_WORLD
    );

    if(currentRank == 0)
        printf("El producto de valores es %d.\n", result);

    MPI_Finalize();

    return EXIT_SUCCESS;
}