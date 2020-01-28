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
    bool myValue = (currentRank == 10);
    bool result = false;

    MPI_Reduce(
        &myValue, 
        &result, 
        1, 
        MPI_C_BOOL, 
        MPI_LOR, 
        mainRank, 
        MPI_COMM_WORLD
    );

    if(currentRank == mainRank)
    {
        printf("La lógica de los valores es %s.\n", result ? "verdadero" : "falso");
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}