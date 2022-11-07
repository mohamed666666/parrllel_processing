#include <stdio.h>
#include <stdlib.h>
#include"mpi/mpi.h"


// Sample Execution code : mpirun -np 4 ./a.out 100 ; Here 100 represents n


long double Pow(int base, int exp){
    long double result = 1.0;
    while (exp != 0) {
        result *= base;
        --exp;
    }
    return result;


}

int main(int argc, char **argv)
{

    int id, nproc;
    int  startval, endval;
    int num = atoi(argv[1]);
    int eterations=10;
    double sum,partial_sum;

    MPI_Init(&argc, &argv);

    // Total number of process
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);

    // get id of mynode:
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Status status;

    sum = 0; // zero sum for accumulation


    startval = eterations * id / nproc + 1;
    endval = eterations * (id + 1) / nproc;

    for (int i = startval; i <= endval; ++i)
        sum = sum + (1/(Pow(i,num)));

    printf("I am the Process %d and my partial sum is %f  \n", id, sum);

    if (id != 0) //the slaves sending back the partial sums
        MPI_Send(&sum, 1, MPI_DOUBLE	, 0, 1, MPI_COMM_WORLD);

    else //id==0! the master recieves the partial sums
    {
        printf("\n\nI am master and my sum currently is : %f \n", sum);
        for (int j = 1; j < nproc; j++)
        {
            MPI_Recv(&partial_sum, 1, MPI_DOUBLE	, j, 1, MPI_COMM_WORLD, &status);
            sum = sum + partial_sum;
            printf("The sum yet is %f after adding sum %f from process %d\n", sum, partial_sum, j);
        }
    }
    if (id == 0)
        printf("The Sum of Convergent Seriesis  %f  \n\n",  sum);

    MPI_Finalize();
    return 0;
}
