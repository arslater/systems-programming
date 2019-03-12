#include "data.h"
#include "process.h"

void switchInstruction(char* line,Stack *scope)
{
	if(isLogclOprn(line))
		doLogclOprn(line,scope);
	else if(isRelatOprn(line))
		doRelatOprn(line,scope);
	else if(isArthmOprn(line))
		doArthmOprn(line,scope);
	else if(isStackOprn(line))
		doStackOprn(line,scope);
	else
	{
		
		int  i = 0;
		char * command = (char *) malloc(sizeof(char)*5);
		char * argument= (char *) malloc(sizeof(char)*strlen(line)-5);

		command[0] = line[0];

		while( line[i] != 0)
			i++;

		argument   = &(line[i]);
		command[i] = '\0';
		line[i+1] = ' ';
		doOutput(line,scope);

	}
}
bool isRelatOprn(char * line)
{
	//////////////////////////////
	// "<>,<=,>=,<,>,="
	//
	return( (line[0] == '<') || (line[0] == '>') || (line[0] =='=') );
}
bool isArthmOprn(char * line)
{
	//////////////////////////////
	// "*,+,-,/,div"
	//	
	return( (line[0] == '*') || (line[0] == '+') || (line[0] == '-') 
	    ||	(line[0] == '/') || (line[0] == 'd'));
}
bool isLogclOprn(char * line)
{
	//////////////////////////////
	// "!,&,|"
	//	
	return( (line[0] == '!') || (line[0] == '&') || (line[0] == '|') );
}
bool isStackOprn(char * line)
{
	//////////////////////////////
	// "pop,push,rval"
	//	
	
	// A little different here. Want to make sure that the FIRST 
	// word is one of the stack calls.

	return( (strstr(line,"pop") != NULL) || (strstr(line,"push") != NULL) 
	     || (strstr(line,"rval") !=NULL) || (strstr(line,"lvalue") != NULL)
		 || (line[0] == ':'));
}
bool isOutput(char * line)
{
	//////////////////////////////
	// "show,print"
	//	
	
	return( (strstr(line,"show") != NULL) || (strstr(line,"print") != NULL));
}

