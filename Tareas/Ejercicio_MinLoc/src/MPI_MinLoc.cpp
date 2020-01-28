#include <iostream>
#include <math.h> 
#include "mpi.h" 

using namespace std;
 
#define  LEN   500

float localValues[LEN];        
int count;
int myrank, minrank, minindex;
float minval;


struct CustomStruct {
    float value;
    int   index;
};

CustomStruct in, out;

in.value = localValues[0];
in.index = 0;

for (i=1; i < count; i++) {
    if (in.value > localValues[i]) {
        in.value = localValues[i];
        in.index = i;
    }
}

MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
in.index = myrank*LEN + in.index;
MPI_Reduce( in, out, 1, MPI_FLOAT_INT, MPI_MINLOC, root, comm );

if (myrank == root) {
    minval = out.value;
    minrank = out.index / LEN;
    minindex = out.index % LEN;
}
