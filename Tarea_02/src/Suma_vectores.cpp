#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>

#define Mast 0
#define Entrada 1
#define sumaV 2

void imprimeVector(int VECTOR[], int cantidad)
{
	int i;
	for(i = 0; i < cantidad; i++)
	{
		printf("%d\n", VECTOR[i]);
	}
}

void llenaVector(int VECTOR[], int cantidad)
{
	srand(time(NULL));
	int i;
	for(i = 0; i < cantidad; i++)
	{
		VECTOR[i] = (rand()%150) + 1;
	}
}

int main(int argc, char *argv[])
{
	int rank, size;
	int cantidad = atoi(argv[1]);
	int VECTOR_A[cantidad], VECTOR_B[cantidad];
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == Mast)
	{

		llenaVector(VECTOR__A, cantidad);
		llenaVector(VECTOR__B, cantidad);

		MPI_Send(VECTOR__A, cantidad, MPI_INT, Entrada, 2, MPI_COMM_WORLD);
		MPI_Send(VECTOR__B, cantidad, MPI_INT, Entrada, 3, MPI_COMM_WORLD);
	}
	else
	{
		if (rank == Entrada)
		{
			MPI_Recv(VECTOR__A, cantidad, MPI_INT, Mast, 2, MPI_COMM_WORLD, &status);
			MPI_Recv(VECTOR__B, cantidad, MPI_INT, Mast, 3, MPI_COMM_WORLD, &status);
			printf("Imprimimos el vector A: \n");
			imprimeVector(VECTOR__A, cantidad);
			printf("Imprimimos el vector B: \n");
			imprimeVector(VECTOR__B, cantidad);
			MPI_Send(VECTOR__A, cantidad, MPI_INT, sumaV, 2, MPI_COMM_WORLD);
			MPI_Send(VECTOR__B, cantidad, MPI_INT, sumaV, 3, MPI_COMM_WORLD);
		}
		else
		{
			if (rank == sumaV)
			{
				MPI_Recv(VECTOR__A, cantidad, MPI_INT, Entrada, 2, MPI_COMM_WORLD, &status);
				MPI_Recv(VECTOR__B, cantidad, MPI_INT, Entrada, 3, MPI_COMM_WORLD, &status);
				int VECTOR__RES[cantidad];
				int i;
				for(i = 0; i < cantidad; i++)
				{
					VECTOR_RES[i] = (VECTORA[i] + VECTOR_B[i]);
				}
				printf("El vector resultante es: \n",VECTOR__RES);
			}
		}
	}
	MPI_Finalize();
	return 0;
}
