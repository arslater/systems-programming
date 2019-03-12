#include "data.h"
#include "process.h"

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
		int i = 0;
		while( line[i] != ' ')
			i++;
			
		doPush(scope,atoi(&(line[i+1])),line);
	}
	else if(strstr(line,"rvalue") != NULL)
		rvalue(line, scope);
	else if(strstr(line,"lvalue") != NULL)
		lvalue(line,scope);
	else if(line[0] == ':' && line[1] == '=')
		eval(scope);
}
void  doOutput(char *line,Stack* scope)
{
	char * argument = (char *) malloc(sizeof(char)*strlen(line));
	int i           = 0;

	while(line[i] != ' ')
		i++;

	argument = &(line[i+1]);


	if( strcmp(argument, "show")== 0)
		argument = "\n";
	
	if( (strstr(line,"show")) != NULL)
		fprintf(FP,"%s\n", argument);
	else
		fprintf(FP,"%d\n",scope ->top -> value);
}
void doPush(Stack* scope, int value, char *name)
{
	/////////////////////////////////////
	// Push to the stack
	
	push(scope,makeNode(name, value));	
	if ( scope -> top -> back != NULL)
		scope -> top -> address = scope -> top -> back -> address+1;
	else
		scope -> top -> address = 0;
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
	Node *tmp = NULL;
	int   value = 0;
	char *name = getArgument(line);

	if( (tmp = inStack(line,scope)) != NULL)
	{
		// A variable of the same name is in the stack
		// Push it's contents onto the stack
		doPush(scope, tmp -> value, tmp ->name);
	}
	else
	{
		// Not in the stack already, make a new node
		doPush(scope,0,name);
	}
}

void lvalue(char *line, Stack* scope)
{
	// Pushing to the stack the memory address
	// of the data given by the argument
	int    i = 0;
	char * name = getArgument(line);
	Node * tmp;

	// does the variable exist in the current stack?
	if( (tmp=inStack(line,scope)) != NULL)
		doPush(scope,tmp -> address, tmp -> name); 
	else
		doPush(scope,0,name);

}
void eval(Stack * scope)
{
	// in progress
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

Node* inStack(char* line, Stack* scope)
{
	Node * tmp   = scope -> bottom;
	Node * rNode = NULL;
	char *var    = getArgument(line);

	while( tmp != NULL)
	{
		if(strcmp(var,tmp ->name) == 0)
		{
			rNode = tmp;
			break;
		}
		tmp = tmp -> next;
	}
	return rNode;
}
char *getArgument(char* line)
{
	// TODO: Make this smart and have it work for show etc
	char * name = (char *) malloc(sizeof(char)*strlen(line));
	int i       = 0;

	while(line[i] != ' ')
		i++;

	name = &(line[i+1]);
	return name;
}
