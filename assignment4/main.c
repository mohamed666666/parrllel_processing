#include <stdio.h>
#include <stdlib.h>
#include"mpi.h"
int main(int argc,int *argv[])
{
    MPI_Init(NULL,NULL);
    int rank;
    MPI_Status Status;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if(rank==0){
    int x=5;
    MPI_Send(&x,1,MPI_INT,1,1,MPI_COMM_WORLD);

    }

    if(rank==1){
        int y;
        MPI_Recv(&y,1,MPI_INT,0,1,MPI_COMM_WORLD,&Status);

        printf("the ricevid Data : %d \n",y);
    }
    MPI_Finalize();
    return 0;

}
