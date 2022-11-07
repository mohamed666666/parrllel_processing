#include <stdio.h>
#include <stdlib.h>
#include<omp.h>

int main()
{

    int id, var2=2, var3 =3;

    int k;


    printf(" Enter K:");
    scanf("%d",&k);
    /* sequential code */
    printf("I am a serial region. \n");

    #pragma omp parallel private(var2) shared(var3) num_threads(k)
    {
		id = omp_get_thread_num();
	    if(id == 0){
			var2 = 22;
		}
        printf ("hello from thread %d\n" , id);
		printf("var2 %d \n " , var2);
		printf("var3 %d \n " , var3);
    }

	/* sequential code */
    printf("I am a serial region. \n");
    return 0;
}
