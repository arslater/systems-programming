//
// Created by anita on 4/18/19.
//
#include "data.h"
#include "process.h"

Node* inStack(char* line, Stack* scope)
{
    ////////////////////////////////////
    // Takes a string and sees if there is a node in the
    // scope stack with the same name
    Node * tmp   = scope -> top; // want to get most recent value
    Node * rNode = NULL;
    char *var    = getArgument(line);

    while( tmp != NULL && tmp -> name != NULL)
    {
        if(strcmp(var,tmp ->name) == 0)
        {
            rNode = tmp;
            break;
        }
        tmp = tmp -> back;
    }
    return rNode;
}
char *getArgument(char* line)
{
    //////////////////////////
    // Voodoo magic to get rid of leading spaces and grab the
    // argument ( the second word. )
    char * name;
    char * arg = NULL;

    if ( line != 0)
    {
        name = (char *)malloc(sizeof(char)*strlen(line));;
        int i = 0;
        arg = (char *) malloc(sizeof(char)*strlen(line));

        name = strtok (line," \t");
        // Get rid of tabs and spaces

        if(name != 0)
        {
            while (name[i] != '\0' && name[i] != 0)
                i++;

            arg = &(name[i+1]);
        }
    }
    if ( arg == 0)
        arg = " ";	// kept getting errors when trying to manipulate empty strings
    return arg;
}
char *getInstruction(char * line)
{
    int i = 0;
    int j = 0;
    char *instr   = (char *) malloc(sizeof(char)*7);
    char *cpy	  = (char *) malloc(sizeof(char)*strlen(line));

    strcpy(cpy, line);

    cpy = strtok(cpy," \t");
    // getting rid of tabs and paces

    if ( cpy != 0)
    {
        while( cpy[i] == ' ' && cpy[i] != 0)
            i++;

        while( cpy[i] != ' ' && cpy[i] != 0)
        {
            instr[j] = cpy[i];
            j++;
            i++;
        }
    }
    if( instr == 0 )
        instr = " ";
    return(instr);
}

int getNextAddr(Stack * scope)
{
    /////////////////////////
    // Algorithmically get the next address
    Node *tmp = scope -> bottom;
    int max   = -1;

    while(tmp != NULL)
    {
        if( tmp -> address > max)
            max = tmp -> address;
        tmp = tmp -> next;
    }

    return max;
}

void clean(Stack *workingStack,Stack*inputStack)
{
    /////////////////////////////////////
    // Free all of the nodes in oth stacks
    Node *tmp = workingStack -> bottom;

    if( tmp != NULL)
    {
        while (tmp->next != NULL) {
            tmp = tmp->next;
            free(tmp->back);
        }

        tmp = inputStack->bottom;
        while (tmp->next != NULL) {
            tmp = tmp->next;
            free(tmp->back);
        }
    }
}
