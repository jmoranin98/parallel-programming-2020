#include <math.h> 
#include <iostream>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include "time.h"

using namespace std;


#define N 4
double detMatriz(double mat[N][N], int n);
double cofactor(double mat[N][N], int b,int j);
double start, finish;

int main (int argc, char *argv[]) {
  double totalDet=0;
  srand(time(NULL));
  int tid;
  double mat[N][N];

  GET_TIME(start);

  for(int i=0;i<N;i++){
  		for(int j=0;j<N;j++){
  			mat[i][j]=rand()%3;
  		}
  	}
  for(int i=0;i<N;i++){
  		for(int j=0;j<N;j++){
  			printf("%lf ",mat[i][j]);
  		}
  		printf("\n");
  }
  	omp_set_num_threads(N);
  	#pragma omp parallel
 {
	 tid = omp_get_thread_num();
	 double cof=cofactor(mat,N,tid);
	 #pragma omp critical
	 totalDet+=cof;

 }

 GET_TIME(finish);

 printf("%lf ",totalDet);
 printf("Elapsed time = %e seconds\n", finish - start);
 return 0;
}

double detMatriz(double mat[N][N], int n)
{
	int index;
	double num1,num2,det = 1.0;
	double temp[n + 1];
	for(int i = 0; i < n; i++)
	{
		index = i;

		while(mat[index][i] == 0 && index < n) {
			index++;

		}
		if(index == n)
		{
			continue;

		}
		if(index != i)
		{
			for(int j = 0; j < n; j++)
			{
				int aux=mat[index][j];
				mat[index][j]=mat[i][j];
				mat[i][j]=aux;
			}
				if((index-i)%2!=0){
					det*=-1;
				}
	}

	for(int j = 0; j < n; j++)
	{
		temp[j] = mat[i][j];

	}
	for(int j = i+1; j < n; j++)
	{
		num1 = temp[i];
		num2 = mat[j][i];

		for(int k = 0; k < n; k++)
		{
			mat[j][k] = ((num1 * mat[j][k]) - (num2 * temp[k]))/num1;

		}
		}

	}

	for(int i = 0; i < n; i++)
	{
		det = det * mat[i][i];
	}

	return (det);
}

double cofactor(double mat[N][N], int b,int j){
	double menor[b][b];
	int c;
	for(int i=0;i<b;i++){
			for(int j=0;j<b;j++){
				menor[i][j]=0;
			}
		}

	for(int k=1; k<b; k++){

			c = 0;

			for(int l=0; l<b; l++){

					if(l!=j){

							menor[k-1][c] = mat[k][l];

							c++;

					}

			}

	}
	double determinante = mat[0][j]*detMatriz(menor,b-1);
	printf("El determinante es: %lf \n",determinante);
	if(j%2!=0)
		determinante*=-1;
	return determinante;
