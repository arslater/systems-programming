/////////////////////////////
// csi402: proj4
// producer.c
//
// by anita slater
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

int main()
{

    int fp;
    FILE* file;
    int status = 0;
    int   i;
    pid_t pid;
    int   maxNum      = 20; // random numbers b/w 0 and 20
    int   howManyNums = 20; // stores 20 numbers by default
    char *buff        = (char *) malloc(sizeof(char)*60);
    char  nums[2];
    int   fd[2];
    int ran          = 0;

    ////////////////
    // Try creating file. Make sure that a file of the
    // same name does not exist
    remove("numbers");
    if ((fp =open("numbers", O_RDWR|O_CREAT,00666 )) == -1)
    {
        ///////////////////////
        // Error creating a file with those permissions
        fprintf(stderr,"Error creating file...\n");
    }
    srand(time(NULL));

    fprintf(stdout,"File \"numbers\" fp = %d\n",fp);    /* could have used write() or fprintf() for both of*/
    write(1,"File \"numbers\" contents is: ",28);       /* these. Just wanted practice going back and forth*/

    // Generating the file with random numbers
    for(i=0;i<howManyNums;i++)
    {
        //////////////////////////
        // Loading the file with random variables
        //   Have the same variable being saved in the file
        //   as well as being outputted to the screen.
        //   Can also write to the pipe here
        ran = (rand() % (maxNum-1))+1;

        sprintf(nums, "%d",ran);
        write(fp,nums,strlen(nums));
        write(1,nums,strlen(nums));
        write(fp," ",1);
        write(1," ",1);
    }
    write(1,"\n",1);
    close(fp);

    // Save the results of the file into a buffer string
    file = fopen("numbers","r");
    fgets(buff,howManyNums*3,file);
    fclose(file);

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
        ///////////////////////
        // We are the child

        fprintf(stdout,"Child: My pid = %d. My parent pid = %d\n",getpid(),getppid());
        write(fd[1], buff,strlen(buff)+1);
        dup2(fd[0],0);
        close(fd[1]);//no more writing to the pipe

        execvp("./consumer",NULL);//run consumer
        fprintf(stderr,"Exec failed\n"); // this should never show
        exit(-2);
    }
    else
    {
        ///////////////////////////
        // We are the parent
        if( (pid = wait(&status)) < 0)
        {
            /////////////////////////
            // Waiting for the child to terminate
            perror("wait");
            _exit(1);
        }
        fprintf(stdout,"Parent: My pid = %d. I created child pid = %d\n",getpid(),pid);
    }
    return 0;
}