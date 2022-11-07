#include <stdio.h>
#include <stdlib.h>

int main()
{

    FILE *file = fopen("student.txt", "r");
    int grades[16];

    int i=0;

    int num;
    while(fscanf(file, "%d", &num) > 0) {

        grades[i] = num;

        i++;
    }
    fclose(file);


    for(int x=0;x<16;x++){

            printf("%d\n",integers[x]);
        }


    return 0;
}
