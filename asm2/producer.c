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

char **doRead(char **);
char **doRepl(char **);
char **doUppr(char **);
char **messages;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

int main()

{
    pthread_t reader, charachter,toUpper,writer;
    int i;
    //char *filename = (char *) malloc(sizeof(char)*45); // TODO: make this better
    char filename[100];
    messages = (char **)malloc(sizeof(char*)*100); // TODO: make this also beter


    read(0,filename,sizeof(filename));

    fprintf(stdout,"\n%s\n",filename);


    return 0;
}

char ** doRead(char **messages)
{
    /////////////////////////////////////////////
    // Takes a "queue" of strings, and creates another "queue" of messages
    // where each string element corresponds to a line in the input file

    //while(!feof())

}