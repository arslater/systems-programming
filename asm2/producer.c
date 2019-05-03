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

#include<stdio.h>

int main()
{
    printf("producer.c");

    return 0;
}