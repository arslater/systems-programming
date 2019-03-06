#include "data.h"
#include "process.h"

void switchInstruction(char* line,Stack *scope)
{
	if(isLogclOprn(line))
		doLogclOprn(line,scope);
	// TODO: Be CRAZY and make this a ternary operation #1-liners
	// TODO: Function pointer HERE????
	// TODO: make a bitmask for what each of the operators are and use a function pointer!!!

	else if(isRelatOprn(line))
		doRelatOprn(line,scope);
	else if(isArthmOprn(line))
		doArthmOprn(line,scope);
	else if(isStackOprn(line))
		doStackOprn(line,scope);
	else
	{
		//printf("Gettign here\n");

		
		int  i = 0;
		char * command = (char *) malloc(sizeof(char)*5);
		char * argument= (char *) malloc(sizeof(char)*strlen(line)-5);

		command[0] = line[0];

		while( line[i] != 0)
			i++;
		command[i] = '\0';
		argument   = &(line[i]);

	    //if(isOutput(command))
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
	     || (strstr(line,"rval") !=NULL));
}
bool isOutput(char * line)
{
	//////////////////////////////
	// "show,print"
	//	
	
	// A little different here. Want to make sure that the FIRST 
	// word is one of the stack calls.
	
	//printf("isoutput\n");
	return( (strstr(line,"show") != NULL) || (strstr(line,"print") != NULL));
}
void  doLogclOprn(char *line,Stack *scope)
{
	int oper1 = (pop(scope))->value;
	int oper2 = 0;
	if( scope -> top != NULL)
		oper2 = (pop(scope))->value;

	if( line[0] == '!' )
		push(scope,makeNode(NULL,bang(oper1)));
	else if(line[0] == '&')
		push(scope,makeNode(NULL,ampr(oper1,oper2)));
 	else if(line[0] == '|')
		push(scope,makeNode(NULL,pipe(oper1,oper2)));

}
void  doRelatOprn(char *line,Stack* scope)
{
	int oper1 = pop(scope) -> value;
	int oper2 = pop(scope) -> value;

	if(line[0] == '=')
		neq(oper1,oper2);
	else if(line[0] == '<')
	{
		switch(line[1])
		{
			case '>':
				push(scope,makeNode(NULL,equ(oper1,oper2)));
				break;
			case '=':
				push(scope,makeNode(NULL,leq(oper1,oper2)));
				break;
			default:
				push(scope,makeNode(NULL,lt(oper1,oper2)));
				break;
		}
	}
	else if(line[0] == '>')
	{
		switch(line[1])
		{
			case '=':
				push(scope,makeNode(NULL,geq(oper1,oper2)));
			default:
				push(scope,makeNode(NULL,gt(oper1,oper2)));
		}
	}
}
void  doArthmOprn(char *line,Stack* scope)
{
	int oper1 = pop(scope)->value;
	int oper2 = pop(scope)->value;

	if( line[0] == '+' )
		push(scope,makeNode(NULL,sum(oper1,oper2)));
	else if(line[0] == '-')
		push(scope,makeNode(NULL,sub(oper1,oper2)));
	else if(line[0] == '*')
		push(scope,makeNode(NULL,mul(oper1,oper2)));
	else if( line[0] == '/')
		push(scope,makeNode(NULL,divi(oper1,oper2)));
	else if(line[0] == 'd')
		push(scope,makeNode(NULL,mod(oper1,oper2)));
}
void  doStackOprn(char *line,Stack *scope)
{

	if (strstr(line,"pop") != NULL)
		pop(scope);
	else if(strstr(line,"push") != NULL)
	{
		////////////////////////////////
		// See if we are pushing a variable or a value
		int  i = 0;
		int  j = 0;
		char *argument = (char *) malloc(sizeof(char)*strlen(line)-5);
		char *name     = NULL;
		int value      = 0;
		int flag       = 1;

		while(line[i] != ' ')
			i++;
		argument = &(line[i]);
		value = atoi(argument);

		for(j=0;argument[j] != 0; j++)
		{
			if( (argument[i]>65 && argument[i] < 90) 
			 || (argument[i]>97 && argument[i] <122))
			{
				/////////////////////////////////////
				// If a charachter is found, break
				name = &(line[i]);
				break;
			}
		}
		push(scope,makeNode(name, value));	
	}
	else if(strstr(line,"rvalue") != NULL)
	{
		rvalue(line, scope);
	}
}
void  doOutput(char *line,Stack* scope)
{
	char * argument = (char *) malloc(sizeof(char)*strlen(line));
	int i           = 0;

	while(line[i] != ' ')
		i++;

	argument = &(line[i+1]);

	if( (strstr(line,"show")) != NULL)
		fprintf(FP,"%s\n", argument);
	else
		fprintf(FP,"%d\n",scope ->top -> value);
}

int sum(int oper1,int oper2) {
	return(oper1+oper2);}
int sub(int oper1,int oper2) {
	return(oper2-oper1);}
int mod(int oper1,int oper2){
	return(oper2%oper1);}
int mul(int oper1,int oper2){
	return(oper1*oper2);}
int divi(int oper1,int oper2){
	return(oper2/oper1);}
int bang(int oper1) {
	return(!oper1);}
int pipe(int oper1,int oper2) {
	return(oper1|oper2);}
int ampr(int oper1,int oper2){
	return(oper1&oper2);}
void rvalue(char* line, Stack* scope)
{
	Node *tmp = scope -> bottom;
	int value = 0;
	while (tmp != NULL)
	{
		tmp = tmp -> next;
		if( strcmp(line,tmp ->name) == 0)
		{
			/////////////////////////////
			// Update variable
			value = tmp -> value;
		}
	}
	push(scope,makeNode(line,value));
}
int equ(int oper1, int oper2){
	return(!(oper1 == oper2));}
int leq(int oper1,int oper2){
	return((oper1-1) <= oper2);}
int geq( int oper1, int oper2){
	return(!((oper1-1)>=oper2));}
int lt(int oper1, int oper2){
	return(!((oper1-1)<oper2));}
int gt(int oper1, int oper2){
	return(((oper1-1)>oper2));}
int neq(int oper1,int oper2){
	return((oper1-1) == oper2);}
