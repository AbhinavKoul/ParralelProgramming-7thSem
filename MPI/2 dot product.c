#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

int main()
{
    int rank,size;
    MPI_Init(NULL,NULL);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if(rank == 0)
        printf("\nStarting omp_dotprod with %d tasks",size);
        
    double a[100],b[100];
    
    for(int i = 0;i<100;i++)
        b[i] = a[i] = 1.0;

    double mysum = 0.0,allsum;

    for(int i = 0;i<100;i++)
        mysum += a[i]*b[i];
    
    printf("\n Task %d partial sum is %f\n",rank,mysum);
    MPI_Reduce(&mysum,&allsum,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);

    if(rank == 0)
        printf("\n Completed process : global sum is %f\n",allsum);

    MPI_Finalize();
}