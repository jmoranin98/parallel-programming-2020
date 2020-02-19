#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include "timer.h"

const int MAX_THREADS = 1024;

long thread_count;
double sum;
double sumg=0;
long long n;
int flag[10];
float next,first=0, second=1;;
double my_factorial=1;
pthread_mutex_t mutex;

double local_int, total_int;

void* FibonacciOp(void* rank);
void Get_args(int argc, char* argv[]);
void Usage(char* prog_name);

int main(int argc, char* argv[]) {
   long       thread;
   pthread_t* thread_handles;
   double start, finish, elapsed;

   Get_args(argc, argv);

   thread_handles = (pthread_t*) malloc (thread_count*sizeof(pthread_t));
   pthread_mutex_init(&mutex, NULL);

   GET_TIME(start);
   for (thread = 0; thread < thread_count; thread++)
      pthread_create(&thread_handles[thread], NULL,
         FibonacciOp, (void*)thread);

   for (thread = 0; thread < thread_count; thread++)
      pthread_join(thread_handles[thread], NULL);
   GET_TIME(finish);
   elapsed = finish - start;

   printf("With n = %lld particiones,\n", n);
   printf("La suma es = %.15f\n", sumg);
   printf("The elapsed time is %e seconds\n", elapsed);

   pthread_mutex_destroy(&mutex);
   free(thread_handles);
   return 0;
}

void FibonacciOp(void* rank) {
   long my_rank = (long) rank;
   long long my_n = n/thread_count;
   while ((flag[my_rank-1]==0 && flag[my_rank]==1) || flag[0]==1 ){
      printf("\nHilo %ld",my_rank);
      for(int i=0 ; i<my_n;i++){
         if(i<=1 && my_rank==0){
            next=i;
         }else{
            next=first+second;
            first=second;
            second=next;
         }
         sumg=sumg+next;
         printf("\ndebug -> %.15f",next);
      }
      flag[my_rank]=0;
      flag[my_rank+1]=1;
   }

   return NULL;
}

void Get_args(int argc, char* argv[]) {
   if (argc != 3) Usage(argv[0]);
   thread_count = strtol(argv[1], NULL, 10);
   if (thread_count <= 0 || thread_count > MAX_THREADS) Usage(argv[0]);
   n = strtoll(argv[2], NULL, 10);
   if (n <= 0) Usage(argv[0]);
}

void Usage(char* prog_name) {
   fprintf(stderr, "usage: %s <number of threads> <n>\n", prog_name);
   fprintf(stderr, "   n is the number of terms and should be >= 1\n");
   fprintf(stderr, "   n should be evenly divisible by the number of threads\n");
   exit(0);
}