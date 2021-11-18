#include<stdio.h>
#include<mpi.h>
#include<string.h>

#define BUFFER 32

int main()
{
	char msg[BUFFER];

	int rank,numprocs;

	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs);

	MPI_Status status;

	int tag =0,root=3;
	if(rank == 3)
	{
		strcpy(msg,"hello");

		for(int temp = 0;temp<numprocs;temp++)
		{
			if(temp!=3)
				MPI_Send(msg,BUFFER,MPI_CHAR,temp,tag,MPI_COMM_WORLD);
		}
	}
	else
	{
		MPI_Recv(msg,BUFFER,MPI_CHAR,root,tag,MPI_COMM_WORLD,&status);
		printf("\n %s in process with rank %d from the process %d \n",msg,rank,root);
	}

	MPI_Finalize();
}