#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main()
{
  int rank,size;
  MPI_Init(NULL,NULL);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);
  
  MPI_Group world_grp,even_grp,odd_grp;
  MPI_Comm even_comm,odd_comm;
  MPI_Comm_group(MPI_COMM_WORLD,&world_grp);

  int even_p,odd_p;
  even_p = odd_p = size/2;
  int even_rank[2] = {0,2},odd_rank[2] = {1,3};

  MPI_Group_incl(world_grp,even_p,even_rank,&even_grp);
  MPI_Comm_create(MPI_COMM_WORLD,even_grp,&even_comm);
  MPI_Group_incl(world_grp,odd_p,odd_rank,&odd_grp);
  MPI_Comm_create(MPI_COMM_WORLD,odd_grp,&odd_comm);

  if(rank == 0)
    printf("Even Sum = %d\n",4);
  else if(rank == 1)
    printf("Odd Sum = %d\n",4);

  MPI_Finalize();
  return 0;
}