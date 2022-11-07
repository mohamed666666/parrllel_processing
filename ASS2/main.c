#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SIZE 20
#define K 2
#define N 7
int a2[1000];

int Start()
{
    FILE* filePointer;
    int bufferLength = 255;
    char buffer[bufferLength];
    filePointer = fopen("/shared/Data.txt", "r");
    int count = 0;

    while (fgets(buffer, bufferLength, filePointer)) {
        count++;
    }
    fclose(filePointer);
    return count;
}

struct DataItem {
   int x;
   int y;
   int clusterX;
   int clusterY;
   double dis;
   int centroidIdx;
};

struct DataItem* hashArray[SIZE];
struct DataItem* dummyItem;
struct DataItem* item;

double distance(struct DataItem* self, struct DataItem*  p) {
	int DiffX = (p->x) - (self->x);
	int DiffY = (p->y) - (self ->y);
	double xSquare = (double)DiffX*DiffX;
	double ySquare = (double)DiffY*DiffY;
	double result = sqrt(xSquare+ySquare);
	return result;
}

void insert(int y,int x) {

   struct DataItem item = (struct DataItem) malloc(sizeof(struct DataItem));
   item.x= x;
   item.y = y;

   // Compute the index
   int hashIndex = hashCode(y);

   //move in array until an empty or deleted cell
   while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->y != -1) {
      //go to next cell
      ++hashIndex;

      //wrap around the table
      hashIndex %= SIZE;
   }

   hashArray[hashIndex] = item;
}

int hashCode(int key) {
   return key % SIZE;
}

void display() {
   int i = 0;

   for(i = 0; i<SIZE; i++) {

      if(hashArray[i] != NULL)
         printf(" (%d,%d)",hashArray[i]->y,hashArray[i]->x);
      else
         printf("");
   }

   printf("\n");
}

struct DataItem computeMin(double dis[N][K],int index, int k, struct DataItem centroids[K])
{
    int i;
    double MIN = 1000000;
    struct DataItem result;
    for (i = 0; i < k; i++){
	if((MIN) > (dis[index][i])){
		MIN = dis[index][i];
		result.x =centroids[i].x;
    		result.y =centroids[i].y;
		result.dis =MIN;
		result.centroidIdx = i;
	}
    }
    return result;
}
void clustring( struct DataItem Points[N], double dis[N][K], struct DataItem centroids[K]){
	struct DataItem result;
 	int i;
	for(i = 0 ; i < N ; i++){
		result = computeMin(dis, i, K, centroids);
		Points[i].clusterX = result.x;
		Points[i].clusterY = result.y;
		Points[i].dis = result.dis;
		Points[i].centroidIdx = result.centroidIdx;
	}
}

void itrative (struct DataItem Points[N], struct DataItem centroids[K], double dis[N][K]){
    int i;
    int j;
    struct DataItem newCent[K];
    int newCount[K];
    for (i = 0; i < K; i++){
	newCount[i] = 0 ;
	newCent[i].x = 0;
	newCent[i].y = 0;
    }
    for (i = 0; i < N; i++){
		newCent[Points[i].centroidIdx].x = newCent[Points[i].centroidIdx].x + Points[i].x;
		newCent[Points[i].centroidIdx].y = newCent[Points[i].centroidIdx].y + Points[i].y;
		newCount[Points[i].centroidIdx] ++;
		printf ("%d\n",newCent[Points[i].centroidIdx].x);
 		}
    for (j=0 ; j<K ; j++){
		newCent[j].x =(int)newCent[j].x / newCount[j];
		printf ("%d\n",newCent[j].x);
	}
    for(i = 0; i < K; i ++){
		centroids[i].x=newCent[i].x ;
		centroids[i].y=newCent[i].y ;
	}
    for(i = 0; i < K; i ++){
		printf ("CENTROIDS : (%d, %d)\n", newCent[i].x, newCent[i].y);
	}
    for (i=0; i < N; i++)
        {
		for (j=0; j < K; j++)
        	{
			dis[i][j] = distance(&centroids[j], &Points[i]);
                        printf ("I:%d, J:%d [%d , %d] - [%d ,%d] = (%f)\n" , i, j, centroids[j].x, centroids[j].y, Points[i].x, Points[i].y, dis[i][j]);
		}
        }
     clustring(Points, dis, centroids);
	for(i = 0; i < N; i ++){
		printf ("%d(%d, %d) -> (%d, %d) its index = %d, dis = %f\n",i ,Points[i].x, Points[i].y, Points[i].clusterX, Points[i].clusterY, Points[i].centroidIdx, Points[i].dis);
	}

}



int main(int argc, char* argv[])
{
    int n = 2 * Start();
    int arrayofdata[n], a2[1000];
    FILE* filepointer;
    char line[100];
    filepointer = fopen("/shared/Data.txt", "r");
    if (filepointer == NULL)
        exit(EXIT_FAILURE);
    int i = 0;
    while (fgets(line, sizeof(line), filepointer)) {
        char words[10];
        int indx = 0;
        int indexctr = 0;
        for (indexctr = 0; indexctr <= strlen(line); indexctr++)
            if (line[indexctr] == ' ' || line[indexctr] == '\0')
            {
                if (line[indexctr] == ' ') {
                    arrayofdata[i] = atoi(words);
                    i++;
                    *words = 0;
                    indx = 0;
                }
                else
                {
                    arrayofdata[i] = atoi(words);
                    i++;
                    *words = 0;
                }
            }
            else
            {
                words[indx] = line[indexctr];
                indx++;
            }

    }

   dummyItem = (struct DataItem*) malloc(sizeof(struct DataItem));
   dummyItem->x= -1;
   dummyItem->y = -1;
   int j =0;
   struct DataItem Points[N];
   struct DataItem centroids[K];
   double dis[N][K];
   int clustered[N];
   double sum [K];
   double mean [K];
   int count[K];
   for (i = 0; i < n; i +=2)
        {
		if(n%2 == 0 ||n%2 == 2){
			insert(arrayofdata[i], arrayofdata[i+1]);
			Points[j].y = arrayofdata[i];
			Points[j].x = arrayofdata[i+1];
			j++;
		}
		else{
			;
		}
        }

   for (i = 0; i < N; i ++)
        {
		printf("     Points : %d \n", i+1);
         	printf(" X is: %d \n", Points[i].x);
         	printf(" Y is: %d \n", Points[i].y);
	}

    for(i = 0 ; i < K ; i++ ) {

      centroids[i]=Points[rand() % N];
      printf("%d (%d, %d)\n",centroids[i], centroids[i].x, centroids[i].y);
   }

   #pragma omp parallel shared(centroids, Points) private(i,j)num_threads(K)
    {

        #pragma omp for schedule(static)
        for (i=0; i < N; i++)
        {
		for (j=0; j < K; j++)
        	{
			dis[i][j] =distance(&centroids[j], &Points[i]);
                        printf ("I:%d, J:%d .. IN thread %d [%d , %d] - [%d ,%d] = (%f)\n" ,i,j, omp_get_thread_num() ,centroids[j].x,centroids[j].y, Points[i].x, Points[i].y, dis[i][j]);
		}
        }
    }   /* end of parallel region */

	clustring(Points, dis, centroids);
	for(i = 0; i < N; i ++){
		printf ("%d(%d, %d) -> (%d, %d) its index = %d, dis = %f\n",i ,Points[i].x, Points[i].y, Points[i].clusterX, Points[i].clusterY, Points[i].centroidIdx, Points[i].dis);
	}

    #pragma omp parallel shared(centroids, dis, sum, mean) private(i,j)num_threads(K)
    {
	#pragma omp for schedule(static)

        for (i=0; i < N; i++){
			sum[Points[i].centroidIdx] += Points[i].dis;
			count[Points[i].centroidIdx]++;
	}
	for (j=0 ; j<K ; j++){
		mean[j] = sum[j]/(double)count[j];
	}
	for(i = 0; i < K; i ++){
		printf ("IN thread %d %f\n",omp_get_thread_num(),mean[i]);
	}
    }   /* end of parallel region */
	for(i = 0; i < K; i ++){
		printf ("CENTROIDS : (%d, %d)\n", centroids[i].x, centroids[i].y);
	}

	itrative (Points,centroids, dis);
    return 0;
}













