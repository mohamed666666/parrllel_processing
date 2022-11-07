#include <stdio.h>
#include <stdlib.h>



int *getarray()
{
    int arr[5];
    printf("Enter the elements in an array : ");
    for(int i=0;i<5;i++)
    {
        scanf("%d", &arr[i]);
    }
    return arr;
}


int main()
{

    int pnts[8][2]= {{3,5},{4,1},{7,5},{8,12},{20,19},{18,9},{13,17},{15,16}};
    int n=sizeof(pnts) / sizeof(pnts[0]);
    printf("%d\n",n);


    int *n2;
    n2=getarray();
    printf("\nElements of array are :");
    for(int i=0;i<2;i++)
    {
        printf("%d", n2[i]);
    }

    return 0;
}
