#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

long F(long a)
{
  return a*a;
}
void search(long limit,long num,int id)
{
  long t = (long)(limit*id)/4;
  long m = (limit*(id+1))/4;

  for(long i = t;i<=m;i++)
  {
    if(F(i) == num)
    {
      printf("Process %d found !\n",id);
      break;
    }
  }
}
int main()
{
  int rank;
  MPI_Init(NULL,NULL);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);

  search(100,49,rank);
  MPI_Finalize();
  return 0;
}