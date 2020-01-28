#include <math.h> 
#include <iostream>
#include "mpi.h" 

using namespace std;
 
int main(int argc, char* argv[])
{
    // Inicializamos MPI
    MPI_Init(&argc, &argv);

    int size, currentRank;

    // Asignamos los valores de MPI a las variables size y currentRank respectivamente
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &currentRank);

    // Número de proceso principal
    int mainRank = 0;

    char mockValues[4] = {0, 2, 6, 8};
    char currentValue = mockValues[currentRank];

    char result = 0;

    MPI_Reduce(
        &my_value, 
        &result, 
        1, 
        MPI_UNSIGNED_CHAR, 
        MPI_BAND, 
        mainRank, 
        MPI_COMM_WORLD
    );

    if(currentRank == mainRank)
        printf("Valores: %d.\n", result);

    MPI_Finalize();

    return EXIT_SUCCESS;
}

