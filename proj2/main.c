#include"data.h"

FILE *FP = NULL;

int main(int argc, char **argv)
{
	FILE *fp;
	FP = stdout;
	// For debugging/ smarter code. Change to not STDOUT when going to a file


	if( (fp = fopen(argv[1], "r")) == NULL)
	{
		fprintf(stderr, "Error opening '%s' for reading. Exiting.\n",argv[1]);
		exit(1);
	}

	Stack *inputStack = makeStack();
	Stack *workingStack = makeStack();
	char  **readLine  = (char **) malloc(sizeof(char*)*500);;
	int     i         = 0;
	
	while( !feof(fp))
	{
		readLine[i] = (char *)malloc(sizeof(char)*200); 
		// TODO: MAKE THIS A SMARTER ALLOCATION

		fgets(readLine[i], 200,fp);
		readLine[i] = strtok(readLine[i], "\n"); // no newline chars
		push(inputStack,makeNode(readLine[i],0));
		i++;
	}
	pop(inputStack);// getting rid of empty string
	//printf("%s\n", stack2string(reverseStack(inputStack), 200));
	Node * tmp = inputStack -> bottom;
	while(strstr(tmp ->name,"halt") == NULL  )
	{	
		doInstruction(tmp ->name,workingStack);
		tmp = tmp -> next;
	}

	free(inputStack);
	free(*readLine);
	fclose(fp);	// TODO: think of a way to close file sooner
return 0;
}
