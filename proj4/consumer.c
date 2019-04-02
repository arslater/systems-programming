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
    long sum = 0;
    long num = 0;
    char * ptr;
    char * digit  = (char *) malloc(sizeof(char)*2) ;
    char * stream = (char *) malloc(sizeof(char)*60);

    read(0,stream,60); // read from pipe, 0 has been 'casted' to 0 from dup() call
    fprintf(stdout,"Even Numbers:");

    do
    {
        if(stream[i] == ' ' || stream[i] == 0)
        {
            num = strtol(digit,&ptr,10);
            if(num % 2 == 0)    // even number
                fprintf(stdout,"%ld ",num);
            else
                sum += num; // odd number add it to overall sum
            digit[0] = '\0';
            digit[1] = '\0';
            j=0;
        }
        else
        {
            digit[j] = stream[i]; // support for 2-digit numbers
            j++;
        }
        i++;
    }while(stream[i]!=0);

    fprintf(stdout,"\nSum of odd values:%ld\n",sum);

    exit(2);
}
