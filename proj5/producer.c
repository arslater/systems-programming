#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    srand(time(NULL));
    int     random;
    char    nums[4];
    int     i;

    write(1,"Random Numbers: ",16);
    for(i=0;i<20;i++)
    {
        random = (rand()%20)+1;
        sprintf(nums,"%d ",random);
        write(4,nums,strlen(nums));
        write(1,nums,strlen(nums));
        //fprintf(stdout,"%s",nums);
    }
    write(1,"\n",1);
    return 1;
}