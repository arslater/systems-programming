#include <stdio.h>
#include "data.h"
#include <stdlib.h>

int OPERAND = 16;

int main(int argc, char ** argv)
{
	FILE *fp;
//	char * string = (char *) malloc(sizeof(char)*256);

	if((fp=fopen(argv[1],"r"))== NULL)
	{
		fprintf(stderr,"ERROR: cannot open '%s' for reading! Exiting...\n",argv[1]);
		exit(1);
	}
	char * string = (char *) malloc(sizeof(char)*64);
	int i =0;
	Tree *expTree = makeTree();
	Stack *myStack = makeStack();
	char * outfile = strcat(strtok(argv[1],"."),".out");
	while( !feof(fp))
	{
		string[i] = fgetc(fp);
		i++;
	}
	string[i-2] = '\0';

	fclose(fp);

	if(( fp=fopen(outfile,"w")) == NULL)
	{
		fprintf(stderr,"Error opening '%s' for writing. Exiting!\n",outfile);
		exit(2);
	}

	myStack = infix2postfix(string);
	myStack = reverseStack(myStack);
	
	expTree = buildTree(myStack);
	fprintf(fp,"%s=%lf\n",string,evaluate(expTree->root));
	return 0;
}
