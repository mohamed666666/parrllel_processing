#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<omp.h>

// to run the code bellow
// use comand $$ gcc -fopenmp main.c -o final.out -lm
//./final.out
struct node
{
    int X;
    int Y;
    struct node* next;
};

void addLast(struct node **head, int x,int y)
{
    //create a new node
    struct node *newNode = malloc(sizeof(struct node));
    newNode->X= x;
    newNode->Y = y;
    newNode->next     = NULL;

    //if head is NULL, it is an empty list
    if(*head == NULL)
        *head = newNode;
    //Otherwise, find the last node and add the newNode
    else
    {
        struct node *lastNode = *head;


        //last node's next address will be NULL.
        while(lastNode->next != NULL)
        {
            lastNode = lastNode->next;
        }

        //add the newNode at the end of the linked list
        lastNode->next = newNode;


    }

}


void printList(struct node *head)
{
    struct node *temp = head;

    //iterate the entire linked list and print the data
    while(temp != NULL)
    {
        printf("(X:%d,Y:%d)->", temp->X,temp->Y);
        temp = temp->next;
    }
    printf("NULL\n");
}



int *avarge(struct node *head)
{
    int sum1=0;
    int sum2=0;
    int count=0;
    struct node *temp = head;
    while(temp != NULL)
    {
        sum1+= temp->X;
        sum2+= temp->Y;
        count++;
        temp = temp->next;
    }

    int *r=malloc(2);
    r[0]=sum1/count;
    r[1]=sum2/count;

    return r;


}

int main()
{







    int pnts[8][2]= {{3,5},{4,1},{7,5},{8,12},{20,19},{18,9},{13,17},{15,16}};


    int k ;

    printf(" Enter K:");
    scanf("%d",&k);

    int iterations;

    printf(" Enter iterations: ");
    scanf("%d",&iterations);


    // intailize centroids randomly
    int centroids[k][2];

    for (int x=0; x<k; x++)
    {
        for(int y=0; y<2; y++)
        {

            centroids[x][y]=(rand())%20;
        }
    }


    //calculate distances

    int id;
    int counter =0;


    while(counter<iterations)
    {

        int n=sizeof(pnts) / sizeof(pnts[0]);

        int distnaces2[k][n];


        #pragma omp parallel shared(pnts,distnaces2) num_threads(k)
        {

            id = omp_get_thread_num();

            for (int i=0; i<n; i++)
            {
                int x=(pnts[i][0]-centroids[id][0])*(pnts[i][0]-centroids[id][0]);
                int y=(pnts[i][1]-centroids[id][1])*(pnts[i][1]-centroids[id][1]);
                int z=x+y;

                distnaces2[id][i]=sqrt(z);

            }

        }


        for(int i=0; i<k; i++)
        {
            for(int j=0; j<n; j++)
            {
                printf("%d ",distnaces2[i][j]);

            }
            printf("\n");
        }








        // divide many clusters


        struct node* clusters[k];


        for(int i=0; i<k; i++)
        {

            clusters[i]= malloc(sizeof(struct node));
            for (int j =0 ; j<n; j++)
            {
                for(int c=0; c<k; c++)
                {
                    if(c==i)
                    {
                        continue;
                    }
                    if(distnaces2[i][j]<distnaces2[c][j])
                    {
                        int x=pnts[j][0];
                        int y=pnts[j][1];
                        addLast(&clusters[i],x,y);
                    }

                }

            }

        }



        for(int i=0; i<k; i++)
        {
            printf(" cluster %d\n",i);
            printList(clusters[i]);
        }





        // update centroids

        for (int i =0; i<k; i++)
        {
            int *arr;
            arr=avarge(clusters[i]);

            centroids[i][0]=arr[0];
            centroids[i][1]=arr[1];

            printf("new centroide %d are(%d,%d) \n",i,arr[0],arr[1]);
        }


        counter++;


    }




    return 0;
}
