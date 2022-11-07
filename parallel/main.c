#include <stdio.h>
#include <stdlib.h>
#include<mpi.h>

int main(int argc, char **argv)
   {
        int my_id, root_process, ierr, num_procs;
      MPI_Status status;
      int counter=0;

      int grades[16];

      /* Create child processes, each of which has its own variables.
       * From this point on, every process executes a separate copy
       * of this program.  Each process has a different process ID,
       * ranging from 0 to num_procs minus 1, and COPIES of all
       * variables defined in the program. No variables are shared.
       **/

      ierr = MPI_Init(&argc, &argv);

      /* find out MY process ID, and how many processes were started. */

      ierr = MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
      ierr = MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

      if( my_id == 0 ) {

 	    FILE *file = fopen("student.txt", "r");


    	    int i=0;

   	   int num;
           while(fscanf(file, "%d", &num) > 0) {

           grades[i] = num;

          i++;
          }
          fclose(file);


	MPI_Send(grades,16,MPI_INT,1,0,MPI_COMM_WORLD);


      }
    if( my_id == 1 ) {

           MPI_Recv(grades, 16, MPI_INT,
                     MPI_ANY_SOURCE, 0,
                     MPI_COMM_WORLD,
                     &status);

           for (int i=0;i<16;i++){
           if(grades[i]>=60){
              printf("the student %d is passed \n",i);
              counter++;
           }}
      }

      printf("%d students passed outof 16\n",counter);


      ierr = MPI_Finalize();
   }

