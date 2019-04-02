#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
    // Want to create file first
    FILE*   file = fopen("numbers","wr");
    int   fp = open("numbers",O_RDONLY);
    int status = 0;
    int   i;
    pid_t pid;
    int   maxNum      = 20; // random numbers b/w 0 and 20
    int   howManyNums = 20; // stores 20 numbers by default
    char *buff        = (char *) malloc(sizeof(char)*60);
    int   fd[2];

    srand(time(NULL));

    // Generating the file with random numbers
    for(i=0;i<howManyNums;i++)
        fprintf(file,"%d ", rand()%maxNum);
    //fclose(fp); // should it be closed?????????
    //fgets(buff,60,file);
    buff = "1 2 3 4 5";

    if(pipe(fd)==-1 )
    {
        fprintf(stderr, "Pipe failed\n");   // creating the pipe
        exit(1);
    }
    if((pid = fork()) == -1)
    {
        ////////////////////
        // Error forking
        fprintf(stderr,"Fork Error. Exiting...\n");
        exit(1);
    }
    if(pid == 0)
    {
        ///////////////////////
        // We are the child
        printf("I am the child!!!\n");
        //dup2(fd[1],0);
        write(fd[1], buff,sizeof(buff)+1);
        dup2(fd[0],0);
        close(fd[1]);//no more writing

        execvp("./consumer",NULL);//run consumer
        fprintf(stderr,"Exec failed\n");
        exit(2);
    }
    else
    {
        if( (pid = wait(&status)) < 0){
            perror("wait");
            _exit(1);

        }
        ////////////////////////
        // We are the parent
        if(status == 0)
            printf("The child process terminated normally\n");
        else
            printf("The child process terminated with an error");

        // close the writing pipe
        //close(fd[1]);
        //close(fd[0]);
        //pid = sleep(1);
    }
    return 0;
}