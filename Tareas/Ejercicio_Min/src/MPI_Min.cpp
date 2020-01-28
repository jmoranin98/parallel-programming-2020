#include <iostream>
#include <math.h> 
#include "mpi.h" 

using namespace std;
 
int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    int size;

    printf("Ingrese el número de procesos: ");
    scanf("%d",size);

    if(size != 10) {
        printf("Ésta aplicación está hecha para usar 10 procesos.\n");
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
        MPI_MIN, 
        mainRank, 
        MPI_COMM_WORLD
    );

    if(currentRank == mainRank)
        printf("El mínimo rango es %d.\n", result);

    MPI_Finalize();

    return EXIT_SUCCESS;
}