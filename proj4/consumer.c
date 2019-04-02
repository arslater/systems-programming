/////////////////////////////
// csi402: proj4
// consumer.c
//
// by anita slater
//
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
void main()
{

    int i=0;
    int j=0;
    char *digit = (char *) malloc(sizeof(char)*2) ;
    char * ptr;
    long sum = 0;
    long num = 0;
    /////////////////////
    // want to read from a file
    // should have the same file pointers & descripters
    char * stream = (char *) malloc(sizeof(char)*60);
    //char stream[] = "1 207 3 4 5";
    fprintf(stdout,"I am a child doing things!!!\n");
    read(0,stream,60);
    fprintf(stdout,"%s\n",stream);
    fprintf(stdout,"Even Numbers:");

    do
    {
        //fprintf(stdout,"##%c|",stream[i]);
        if(stream[i] == ' ' || stream[i] == 0)
        {
            num = strtol(digit,&ptr,10);
            if(num % 2 == 0)    // even number
                fprintf(stdout,"%ld ",num);
            else
            {
                sum += num;
            }
            digit[0] = '\0';
            digit[1] = '\0';
            j=0;
        }
        else
        {
            digit[j] = stream[i];
            j++;
        }
        i++;
    }while(stream[i-1]!=0);
    
    fprintf(stdout,"\nSum of odd values:%ld\n",sum);

    exit(2);
}
