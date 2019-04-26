////////////////////////////////////////////////////////////
//
//  Anita Slater
//  CSI 402: Systems Programming - Programming Assignment 6
//  4/25/19
//
//  main.c - main c source code
//

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gSum[4];
int nums[8];
int piece = 0;
pthread_mutex_t mutex1;

#define NUM_THREADS 2
#define NUM_INTS    8

void *ArraySum(void* arg)
{
	int part = piece++;	// locking this 
						// locks the whole program????
	int  sum = 0;
	int    i = 0;
	
	for( i = part*(NUM_INTS/2); i<(part+1)*(NUM_INTS/2);i++)
		sum+= nums[i];

	pthread_mutex_lock(&mutex1);
	gSum[part] = sum;	// locking while updaing global
	pthread_mutex_unlock(&mutex1);
}

int main (int argc, char* argv[])
{
    int j    = 0;
	int sum  = 0;
	int i    = 0;
	
	char *input = (char *) malloc(sizeof(char)*NUM_INTS);
	char *buff  = (char *) malloc(sizeof(char)*4);
	pthread_mutex_init(&mutex1, NULL);
	printf("Enter in %d numbers separated by spaces, then press enter\ninput:", NUM_INTS);
	fgets(input, 256,stdin);

	nums[i] = atoi(strtok(input," "));
	i++; 
	while( (buff = strtok(NULL," ")) != NULL)
	{
		nums[i] = atoi(buff);
		i++;
		if ( i > NUM_INTS)
			break;
	}	
    pthread_t sumThreads[NUM_THREADS];
    for (j = 0; j < NUM_THREADS; j++)
    {
        int *threadNum;
        threadNum = &j;
        pthread_create( &sumThreads[j], NULL, ArraySum, (void *)threadNum);
	}
    for (j = 0; j < NUM_THREADS; j++)
    {
		pthread_join(sumThreads[j], NULL);
		sum += gSum[j];
	}
    printf("The sum of array elements is %d\n", sum);
    return( 0 ) ;
}
