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
    bool value = currentRank * 2;
    bool result = false;

    MPI_Reduce(
        &value, 
        &result, 
        1, 
        MPI_C_BOOL, 
        MPI_LOR, 
        mainRank, 
        MPI_COMM_WORLD
    );

    if(currentRank == mainRank)
        printf("%s.\n", result ? "True" : "False");

    MPI_Finalize();

    return EXIT_SUCCESS;
}