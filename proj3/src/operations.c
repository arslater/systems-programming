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
int pipe(int oper1,int oper2) {
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
		doPush(scope, tmp -> value, tmp ->name, tmp ->address);
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
		// If it's already there, when pushing the new node on
		// the stack, it will add 1 to it's address. Don't
		// want to do that here, so compensating
		printf("^^ Variable %s is in the stack!\n", tmp ->name);
		doPush(scope,tmp -> address, tmp -> name, tmp ->address); 
	}
	else
		doPush(scope,0,name, address);

}
void eval(Stack * scope)
{
	// Assuming that this operator means to take the lvalue
	// and set the top variable on the stack equal to its address

	// TODO: safe to assume rvalue is always on top???

	int address = 0;
	if( scope -> top ->back -> back != 0)
		address = scope -> top -> back -> back ->address;
	else
		address = 0;

	int   value = pop(scope) -> value;
	char *name  = pop(scope) -> name;

	doPush(scope,value,name,address);
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

Node *got(char *line,Stack *instructions)
{
	////////////////////////////////////
	// need access to the input stack....
	// TODO: think of a cleaner way instead of passing this300x

	char * label;
	Node * tmp = instructions -> bottom;

	label = strcpy(label,getArgument(line));
	while (tmp != NULL)
	{
		if ( strlen(tmp -> name) > 5)
		{
			if((strcmp(getInstruction(tmp->name), "label") == 0)
			&&(strcmp(getArgument(tmp->name),label) == 0) )
			{
				break;
			}
		}
		tmp = tmp -> next;

	}
	return tmp -> next;
}

Node* inStack(char* line, Stack* scope)
{
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
	// TODO: Make this smart and have it work for show etc
	char * name = (char *) malloc(sizeof(char)*strlen(line));
	int i       = 0;

	while(line[i] != ' ' && line[i] != '\0')
		i++;

	name = &(line[i+1]);

//	printf("@@%s@@\n",name);
//	printf("^^^^%c%c%c%c%c%c%c^^^^^\n",line[0],line[1],line[2],line[3],line[4],line[5], line[6]);
	return name;
}
char *getInstruction(char * line)
{
	int i =0;
	int j = 0;
	char * string = (char*)malloc(sizeof(char)*7); 
	char *instr   = (char *) malloc(sizeof(char)*7); 
	// size of longest instruction is 7

	line = strtok(line,"\t");
	
	while(line[i] != ' ')
		i++;

	strcpy(instr, line);
	instr[i] = '\0';

	return(instr);
}

int getNextAddr(Stack * scope)
{	
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
