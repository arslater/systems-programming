#include"data.h"
#include "process.h"

FILE *FP = NULL;

int main(int argc, char **argv)
{
	FILE *fp;
	
	if( (fp = fopen(argv[1], "r")) == NULL)
	{
		fprintf(stderr, "Error opening '%s' for reading. Exiting.\n",argv[1]);
		exit(1);
	}

	Stack *inputStack = makeStack();
	Stack *workingStack = makeStack();
	char  **readLine  = (char **) malloc(sizeof(char*)*500);;
	int     i         = 0;
	char  *outfile    = strcat(strtok(argv[1],"."),".out");

	while( !feof(fp))
	{
		readLine[i] = (char *)malloc(sizeof(char)*200); 	

		fgets(readLine[i], 200,fp);
		readLine[i] = strtok(readLine[i], "\n"); // no newline chars
		push(inputStack,makeNode(readLine[i],0));
		i++;
	}
	pop(inputStack);// getting rid of empty string

	Node * tmp = inputStack -> bottom;
	
	if ( (FP = fopen(outfile,"w")) == NULL)
	{
		fprintf(stderr,"Error opening '%s' for writing. Exiting\n",outfile);
		exit(2);
	}

	FP = stdout; //uncomment to print to the console

	run(inputStack -> bottom, workingStack, inputStack);

	free(inputStack);
	free(*readLine);
	fclose(fp);	
	fclose(FP);
return 0;
}
