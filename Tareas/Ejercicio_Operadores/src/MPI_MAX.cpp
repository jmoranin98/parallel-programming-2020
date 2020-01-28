#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

using namespace std;
 
int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    int size;

    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(size != 4) {
        printf("Esta aplicación está hecha para correr 4 procesos.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    int mainRank = 0;

    int currentRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &currentRank);

    int result = 0;
    MPI_Reduce(
        &currentRank, 
        &result, 
        1, 
        MPI_INT, 
        MPI_MAX, 
        mainRank, 
        MPI_COMM_WORLD
    );

    if(currentRank == mainRank)
        printf("%d.\n", result);

    MPI_Finalize();

    return EXIT_SUCCESS;
}