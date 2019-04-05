//
// Created by anita on 4/5/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char** argv)
{

    int  fd[2];
    int  pid;
    int  status        = 0;
    char *dotslash     = (char *)malloc(sizeof(char)*12);
    //TODO: Make this smarter


    if(pipe(fd)==-1 ) // creating the pipe
    {
        fprintf(stderr, "Pipe failed\n");
        exit(-1);
    }
    if((pid = fork()) == -1)
    {
        ////////////////////
        // Error forking
        fprintf(stderr,"Fork Error. Exiting...\n");
        exit(-1);
    }


    if(pid == 0)
    {
        //////////////////
        // In the child, have it execute producer

        dotslash[0] = '.';
        dotslash[1] = '/';
        strcat(dotslash,argv[1]);
        //TODO: Think: is it bad to just assume that fd will be 4
        
        execvp(dotslash,NULL); // execute

       fprintf(stderr,"Something went terribly wrong. Error executing");
    }
    else
    {

        if( (pid = wait(&status)) < 0) {
            /////////////////////////
            // Waiting for the child to terminate
            perror("wait");
            _exit(1);
        }
        dup2(fd[0],0);    //make stdin the pipe
        dotslash[0] = '.';
        dotslash[1] = '/';
        strcat(dotslash,argv[2]);
        fprintf(stdout,"even numbers: ");
        execvp(dotslash,NULL);
    }
};