#include<stdlib.h>
#include<mpi.h>
#include<stdio.h>
#include<math.h>
#define N 100000

int main()
{
  int rank,size;
  MPI_Init(NULL,NULL);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);

  double count = 0,val = 0;
  for(int i = 0;i<N;i++)
  {
    double x = (double)rand()/RAND_MAX;
    double y = (double)rand()/RAND_MAX;

    double z = (x*x) + (y*y);

    if(z<=1)
      count++; 
  }

  MPI_Reduce(&count,&val,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);

  if(rank == 0)
    printf("PI: %lf \t",val/N);

  MPI_Finalize();
}