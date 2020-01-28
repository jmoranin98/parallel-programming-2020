#include <iostream>
#include <math.h> 
#include "mpi.h" 

using namespace std;
 
int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    int size, currentRank;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &currentRank);

    int mainRank = 0;
    char myValues[4] = {0, 1, 3,7};
    char myValue = myValues[currentRank];
    char result = 0;

    MPI_Reduce(
        &myValue, 
        &result, 
        1, 
        MPI_UNSIGNED_CHAR, 
        MPI_BXOR, 
        mainRank, 
        MPI_COMM_WORLD
    );

    if(currentRank == mainRank)
        printf("Los bits de los valores son %d.\n", result);

    MPI_Finalize();

    return EXIT_SUCCESS;
}