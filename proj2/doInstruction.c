#include "data.h"


// TODO: Call the functions from within these if statemetns
void doInstruction(char *line, Stack *runStack)
{
	int i          = 0;
	char *argument = (char *) malloc(sizeof(char)*strlen(line));

	if ( line[0] == '+')
		push(runStack, makeNode( NULL, runStack -> top ->value 
		+ runStack -> top ->back ->value));

	else if ( line[0] == '|')
		push(runStack, makeNode( NULL, runStack -> top ->value 
		| runStack -> top ->back ->value));
	
	else if ( line[0] == '-')
	{
		push(runStack, makeNode( NULL, runStack -> top ->back->value 
		- runStack -> top ->value));
	}
	else if ( line[0] == '*')
		push(runStack, makeNode( NULL, runStack -> top ->value 
		* runStack -> top ->back ->value));
	
	else if ( line[0] == '/')
		push(runStack, makeNode( NULL, runStack -> top -> back->value 
		/ runStack -> top ->value));
	
	else if ( line[0] == 'd')
		push(runStack, makeNode( NULL, runStack -> top ->back ->value 
		% runStack -> top ->value));

	else if ( line[0] == '!')
		push(runStack, makeNode( NULL, runStack -> top ->back ->value 
		^ runStack -> top ->value));
	
	else if ( line[0] == '&')
		push(runStack, makeNode( NULL, runStack -> top ->back ->value 
		& runStack -> top ->value));

	else if ( line[0] == '=')
	{
		if( (runStack -> top -> value)-1 == runStack -> top -> back -> value)
				push(runStack,makeNode(NULL,0));
		else
				push(runStack,makeNode(NULL,1));
	}	
	else if ( line[0] == '<')
	{	
		switch (line[1])
		{
			case '>':
				if( runStack -> top -> value == runStack -> top -> back -> value)
					push(runStack,makeNode(NULL,0));
				else
					push(runStack,makeNode(NULL,1));
				break;
			case '=':
				if( (runStack -> top -> value)-1 <= runStack -> top -> value)
					push(runStack,makeNode(NULL,1));
				else
					push(runStack,makeNode(NULL,0));
				break;
			default:
				if( (runStack -> top -> value)-1 > runStack -> top -> value)
					push(runStack,makeNode(NULL,0));
				else
					push(runStack,makeNode(NULL,1));
				break;
		}
	}
	else if ( line[0] == '>')
	{
		switch (line[1])
		{
			case '=':
				if( (runStack -> top -> value)-1 >= runStack -> top -> value)
					push(runStack,makeNode(NULL,1));
				else
					push(runStack,makeNode(NULL,0));
				break;
			
			default:
				if( (runStack -> top -> value)-1 < runStack -> top -> value)
					push(runStack,makeNode(NULL,0));
				else
					push(runStack,makeNode(NULL,1));
				break;
		}
	}
	else if ( line[0] == 'd')
		push(runStack, makeNode( NULL, runStack -> top ->back ->value 
		% runStack -> top ->value));

	else
	{
		/////////////////////////////////////////////
		// These instructions have arguments following them.
		// Separate the argument from the line and save it in
		// the 'argument' string
		//
		while(line[i] != ' ')
			i++;

		argument = &(line[i+1]);

		if( (strstr(line,"show")) != NULL)
			fprintf(FP,"%s\n",argument);

		else if ((strstr(line,"print")) != NULL)
			fprintf(FP,"%d\n",runStack->top->value);
	
		else if((strstr(line,"pop")) != NULL)
			pop(runStack);

		else if((strstr(line,"push")) != NULL)
			push(runStack,makeNode(NULL,atoi(argument)));
		
		else if((strstr(line,"rvalue")) != NULL)
			push(runStack,makeNode(argument,0));
	}
}
