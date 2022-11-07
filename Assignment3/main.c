#include <stdio.h>
#include <stdlib.h>
#include<omp.h>




int main()
{

    int n;

    printf("enter number of data points: ");
    scanf("%d",&n);


    int points[n];


    FILE *myFile;
    myFile = fopen("dataset.txt", "r");

    if (myFile == NULL)
    {
        printf("Error Reading File\n");
        exit (0);
    }


    for (int i = 0; i < n; i++)
    {
        fscanf(myFile, "%d", &points[i]);
    }


    //sorting array points
    int temp = 0;

    //Calculate length of array arr
    int length = sizeof(points)/sizeof(points[0]);
    //Sort the array in ascending order
    for (int i = 0; i < length; i++)
    {
        for (int j = i+1; j < length; j++)
        {
            if(points[i] > points[j])
            {
                temp = points[i];
                points[i] = points[j];
                points[j] = temp;
            }
        }
    }



    for(int i=0;i<length;i++){
      printf(" %d ",points[i]);
    }

    int range=points[length-1]-points[0];
    //printf("the range : %d",range);

    int bar;
    printf("Enter Number Of Bars: ");
    scanf("%d",&bar);
    //printf("bars %d",bar);



    int slicer=range/bar +1;

    printf("s %d\n",slicer);



    #pragma omp parallel shared(points) num_threads(bar)
    {
        int counter=0;
        int id = omp_get_thread_num();
        int start=slicer*id;
        int end=start+slicer;

        for(int i=0;i<length;i++){
            if(points[i]<end && points[i]>=start)
                counter++;
        }

        printf("the range Start with %d and End with %d and has %d points\n",start,end,counter);




    }









    return 0;
}
