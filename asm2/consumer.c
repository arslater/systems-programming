/////////////////////////////////////////
//
//  CSI 402 - Prgroaming Assignment 2
//  Anita Slater
//
//  consumer.c : Submits processing requests to the producer by supplying a file name,
//               its location and a character. It also outputs the contents of the
//               file provided by the producer to the standard output.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>

char * FILENAME = "changeMe.txt";
char REPLACE[2]  = "a";
// Where are we getting the name of the file from?!?!?!

int main()
{
    //printf("%s\n",FILENAME);

    FILE *fp = fopen(FILENAME, "w");
    if   (fp == NULL)
    {
        ///////////////////////////
        // can't read file
        fprintf(stderr,"Error opening '%s' for reading!\n",FILENAME);
    }

    pid_t pid = 0;
    int   fd1[2];
    int   fd2[2];
    char  path[PATH_MAX]; // getting the max length of the path

    if(pipe(fd1) == -1 || pipe(fd2) == -1)
    {
        fprintf(stderr,"Error creating pipe!\n");
        exit(-1);
    }
    if((pid=fork()) == -1)
    {
        fprintf(stderr,"Error forking. Exiting...\n");
        exit(-2);
    }
    if(pid == 0)
    {
        /////////////////////////////
        // we are the child
        printf("I am the child\n");

        getcwd(path,sizeof(path));
        strcat(path,"/");
        strcat(path,FILENAME);

        write(fd1[1],path,sizeof(path)+1);
        write(fd2[1],REPLACE,sizeof(REPLACE));
        //write(fd[1],"hi",sizeof("hi"));
        close(fd1[1]);
        close(fd2[1]);
    }
    else
    {
        /////////////////////////////
        // we are the parent
        printf("I am the parent\n");
        char buff[300];
        char car[2];

        close(fd1[1]);
        close(fd2[1]);
        read(fd1[0],buff,sizeof(buff));
        read(fd2[0],car,sizeof(car));
        printf("%s\n",buff);
        printf("%s\n",car);

    }






    return 0;
}