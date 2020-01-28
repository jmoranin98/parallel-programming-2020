#include <iostream>
#include <math.h> 
#include "mpi.h" 

using namespace std;
 
int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int size, currentRank;

    MPI_Comm_rank(MPI_COMM_WORLD, &currentRank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    float quad = currentRank * 10;
    float sum = quad + 1.5;

    MPI_Reduce(
        &currentRank,
        &sum,
        1,
        MPI_FLOAT,
        MPI_SUM,
        0,
        MPI_COMM_WORLD
    );

    if (currentRank == 0)
    	printf("La suma es %d.\n", sum);

    MPI_Finalize();

    return 0;
}