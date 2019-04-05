//
// Created by anita on 4/4/19.
//
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    char *buff    = (char *) malloc(sizeof(char)*60);
    char *digs    = (char *) malloc(sizeof(char)*3);
    int   i       = 0;
    int   j       = 0;

    read(0,buff,60);

    fprintf(stdout,"Even numbers: ");
    do
    {
        if(buff[i] == '\n' || buff[i] == ' ')
        {
            if( atoi(digs) % 2 == 0)
                fprintf(stdout,"%s ",digs);
            digs[0] = '\0';
            digs[1] = '\0';
            j = 0;
        }
        else
        {
            digs[j] = buff[i];
            j++;
        }
        i++;
    }while(buff[i] != 0);
    fprintf(stdout,"\n");

    return 1;
}