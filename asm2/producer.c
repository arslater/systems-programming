//////////////////////////////////////////////////////
//
//   CSI 402 - Prgroaming Assignment 2
//   Anita Slater
//
//   producer.c : Accepts multiple consumer requests and processes each request by creating the following four threads.
//        1. The reader thread will read an input file, one line at a time. It will pass each line of input to the character thread through a queue of messages.
//        2. The character thread component will scan the line and replace each blank character by the character supplied by the client. It will then pass the line to the toUpper thread through another queue of messages.
//        3. The toUpper thread component will scan the line and convert all lower case letters to upper case. It will then pass the converted line to the writer thread through another queue of messages.
//        4. The writer thread will write the line to an output file.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>
#include <pthread.h>

void *doRead(void *);
void *doRepl(void *);
void *doUppr(void *);
void *doWrite(void*);

typedef struct threadData{
    char **messageQueue;
    char   replLetter;
    char  *filename;
    char  *outfile;

} ThreadData;

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

int main()

{

    fprintf(stdout,"clion pls\n");
    pthread_t reader, charachter,toUpper,writer;
    int i;
    char consumerData[100]; // TODO: make this better!!!
    char *filename = (char *)malloc(sizeof(char)*PATH_MAX);
    char *REPLACE  = (char* )malloc(sizeof(char)*2);
    int * threadNum = 0;
    void* status    = 0;
    ThreadData *MyThreadData = (ThreadData*) malloc(sizeof(ThreadData));

    MyThreadData->messageQueue = (char **)malloc(sizeof(char*)*100); // TODO: make this also beter

    read(0,consumerData,sizeof(consumerData));

    MyThreadData->filename   = strtok(consumerData," ");
    MyThreadData->replLetter = strtok(NULL," ")[0];
    MyThreadData->outfile = "outfile.txt";

    // Have reader thread read the filename
    pthread_create(&reader,NULL, doRead, (void*)MyThreadData);
    pthread_join(reader,&status);

    // Have the charachter Thread scan each line of the message thread and replace each space
    pthread_create(&charachter,NULL,doRepl,(void *)MyThreadData);
    pthread_join(charachter,&status);

    pthread_create(&toUpper,NULL,doUppr,(void *)MyThreadData);
    pthread_join(toUpper,&status);

    pthread_create(&writer,NULL,doWrite,(void *)MyThreadData);
    pthread_join(writer,&status);

    fprintf(stdout,"\n%s -> %c\n| %s\n\n",MyThreadData->filename,MyThreadData->replLetter,MyThreadData->messageQueue[5]);

    return 0;
}

void *doRead(void *arg)
{
    /////////////////////////////////////////////
    // Takes a filename "queue" of messages
    // where each string element corresponds to a line in the input file

   ThreadData *thread = (ThreadData *)arg;
   char buff[255];

   FILE *fp = fopen(thread->filename,"r");

   //printf("%s\n",thread->filename);


   if ( fp == NULL)
        fprintf(stderr,"Something went wrogn.. cannot open file\n");
   int i = 0;
   // maybe run this in a loop and this function just reads the file line by line..?

    fprintf(stdout,"reading...\n");
    thread->messageQueue[i] = (char *)malloc(sizeof(char)*100);
    while(fgets(thread->messageQueue[i],255,fp))
    {
      // printf("READ LINE]%s",thread->messageQueue[i]);
       i++;
       thread->messageQueue[i] = (char *)malloc(sizeof(char)*100);
    }

    //printf("\n");
    fclose(fp);
   pthread_exit(NULL);
}

void *doRepl(void *arg)
{
    ThreadData *thread = (ThreadData *)arg;
    int i = 0;
    int j = 0;

    printf("replacing....\n");
    while( thread->messageQueue[i] != 0)
    {
        while(thread->messageQueue[i][j] != 0)
        {
           // printf("[%d][%d]:%c\n",i,j,thread->messageQueue[i][j]);
            if(thread->messageQueue[i][j] == ' ')
                thread->messageQueue[i][j] = thread->replLetter;
            j++;
        }
       // printf("Observing: %s",thread->messageQueue[i]);
        j = 0;
        i++;
    }

    //printf("##%s\n",thread->messageQueue[4]);
    //printf("\n");
    pthread_exit(NULL);

}

void *doUppr(void *arg)
{
    ThreadData *thread = (ThreadData *)arg;
    int i = 0;
    int j = 0;

    printf("replacing....\n");
    while( thread->messageQueue[i] != 0)
    {
        while(thread->messageQueue[i][j] != 0)
        {
            if(thread->messageQueue[i][j] > 96 && thread->messageQueue[i][j] < 123)
                thread->messageQueue[i][j] -=32;
            j++;
        }
        j = 0;
        i++;
    }
    pthread_exit(NULL);
}

void *doWrite(void *arg)
{
    ThreadData *thread = (ThreadData *)arg;
    FILE* fp = fopen(thread->outfile,"w");
    int i = 0;
    int j = 0;

    printf("replacing....\n");
    while( thread->messageQueue[i] != 0)
    {
        fprintf(fp,"%s",thread->messageQueue[i]);
        i++;
    }
    pthread_exit(NULL);
}