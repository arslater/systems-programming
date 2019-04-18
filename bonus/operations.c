#include "data.h"
#include "process.h"

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
int pype(int oper1,int oper2) {
	return(oper1|oper2);}
int ampr(int oper1,int oper2){
	return(oper1&oper2);}
void rvalue(char* line, Stack* scope)
{
	Node *tmp = NULL;
	int   value = 0;
	char *name = getArgument(line);

	int address = 0;

	if( scope -> top != NULL)
		address = scope -> top -> address;

	if( (tmp = inStack(line,scope)) != NULL)
	{
		// A variable of the same name is in the stack
		// Push it's contents onto the stack
		doPush(scope, tmp -> value, tmp ->name, tmp ->address+1);
	}
	else
	{
		// Not in the stack already, make a new node
		doPush(scope,0,name, address);
	}
}

void lvalue(char *line, Stack* scope)
{
	// Pushing to the stack the memory address
	// of the data given by the argument
	int    i = 0;
	char * name = getArgument(line);
	Node * tmp;

	int address = 0;

	if( scope -> top != NULL)
		address = scope -> top -> address;
	
	// does the variable exist in the current stack?
	if( (tmp=inStack(line,scope)) != NULL)
	{
		// If it's already there, the next address
		// will be the current address+1
		doPush(scope,tmp->value, tmp -> name, tmp ->address+1); 
	}
	else
		doPush(scope,0,name, address);

}
void eval(Stack * scope)
{
	// :=
	// This operator means to take the lvalue
	// and set the top variable on the stack equal to its address

	int address = 0;
	if( scope -> top ->back != 0)
		address = scope -> top -> back -> address;	// address of the rvalue node
	else
		address = 0;

	int   value = pop(scope) -> value;
	char *name  = pop(scope) -> name;

	doPush(scope,value,name,getNextAddr(scope)-1);
}
int equ(int oper1, int oper2){
	return(!(oper1 == oper2));}
int leq(int oper1,int oper2){
	return((oper1-1) <= oper2);}
int geq( int oper1, int oper2){
	return(!((oper1-1)>=oper2));}
int lt(int oper1, int oper2){
	return(!((oper1-1)<oper2));}
int gt(int oper1, int oper2){	// Wondering why this makes sense? Me too
	return(((oper2)>oper1));}	// For whatever reason swapping them fixes everything	
int neq(int oper1,int oper2){
	return((oper1-1) == oper2);}

Node * got(char *line,Stack *instructions)
{
	////////////////////////////////////
	// need access to the input stack to get the
	// the node where the label is

	char * label;
	Node * tmp = instructions -> bottom;
	label = strcpy(label,getArgument(line));
	
	while (tmp != NULL)
	{
		if( tmp -> name != 0 )
		{
			////////////////////////////
			// empty lines make seg faults
			if ( strlen(tmp -> name) >= 5)
			{
				if((strstr(tmp->name, "label") != NULL)
				&&(strcmp(getArgument(tmp->name),label) == 0) )
					break;
			}
		}
		tmp = tmp -> next;
	}
	return(tmp -> next);
}

void gofalse(char * line, Stack* scope,Stack* instructions)
{
	////////////////////////////////////////
	// If the current node on the stack is 0, jump to
	//	the label specified
	Node * tmp = pop(scope);

	if ( tmp -> value == 0 )
		run(got(line,instructions),scope,instructions);
}

void gotrue(char * line, Stack* scope,Stack* instructions)
{
	///////////////////////////////////////
	// If the current node on the stack is NOT
	// 0, go to the label specified
	Node * tmp = pop(scope);
	
	if ( tmp -> value != 0 )
		run(got(line,instructions),scope,instructions);
}
Node* inStack(char* line, Stack* scope)
{
	////////////////////////////////////
	// Takes a string and sees if there is a node in the
	// scope stack with the same name
	Node * tmp   = scope -> top; // want to get most recent value
	Node * rNode = NULL;
	char *var    = getArgument(line);

	while( tmp != NULL)
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
	Node *tmp = workingStack -> bottom -> next;

	while(tmp -> next!= NULL)
	{
		tmp = tmp -> next;
		free(tmp -> back);
	}
	
	tmp = inputStack -> bottom;
	while(tmp -> next!= NULL)
	{
		tmp = tmp -> next;
		free(tmp -> back);
	}
}	
