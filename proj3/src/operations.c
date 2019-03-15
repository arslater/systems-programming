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
		// If it's already there, when pushing the new node on
		// the stack, it will add 1 to it's address. Don't
		// want to do that here, so compensating
		//printf("^^ Variable %s is in the stack!\n", tmp ->name);
		doPush(scope,tmp->value, tmp -> name, tmp ->address+1); 
	}
	else
		doPush(scope,0,name, address);

}
void eval(Stack * scope)
{
	// Assuming that this operator means to take the lvalue
	// and set the top variable on the stack equal to its address

	// TODO: safe to assume rvalue is always on top???

	printf("****************\n");
	int address = 0;
	if( scope -> top ->back != 0)
		address = scope -> top -> back -> address;
	else
		address = 0;

	int   value = pop(scope) -> value;
	char *name  = pop(scope) -> name;

//	doPush(scope,value,name,address);
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
int gt(int oper1, int oper2){
	return(((oper2)>oper1));}
int neq(int oper1,int oper2){
	return((oper1-1) == oper2);}

Node * got(char *line,Stack *instructions)
{
	////////////////////////////////////
	// need access to the input stack....
	// TODO: think of a cleaner way instead of passing this300x

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
				&&(strcmp(getArgument(tmp->name),label) == 0) 
				)//&&(strstr(tmp -> name,"show") == NULL))
				{
					break;
				}
			}
		}
		tmp = tmp -> next;
	}
	return(tmp -> next);
}

void gofalse(char * line, Stack* scope,Stack* instructions)
{
	Node * tmp = pop(scope);

	printf("##??%d =?= 0\n",tmp ->value);

	if ( tmp -> value == 0 )
		run(got(line,instructions),scope,instructions);
}

void gotrue(char * line, Stack* scope,Stack* instructions)
{
	Node * tmp = pop(scope);
	
	if ( tmp -> value != 0 )
		run(got(line,instructions),scope,instructions);
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
/*	char * name = (char *) malloc(sizeof(char)*strlen(line));
	int i       = 0;
	int j       = 0;
	
	// want to get rid of leading tabs and whitespaces!!
	line = strtok(line,"\t");
	while(line[i] == ' ')
		i++;

	while(line[i] != ' ' && line[i] != '\0')
	{
		name[j] = line[i];
		i++;
		j++;
	}

	name[j] = '\0';
//	printf("@@%s@@\n",name);
//	printf("^^^^%c%c%c%c%c%c%c^^^^^\n",line[0],line[1],line[2],line[3],line[4],line[5], line[6]);
	*/

//	printf("#%s# ->",line);

	char * name;
	char * arg = NULL;

	if ( line != 0)
	{
		name = (char *)malloc(sizeof(char)*strlen(line));;
		int i = 0;
		arg = (char *) malloc(sizeof(char)*strlen(line));
	
		name = strtok (line," \t");
	
		if(name != 0)
		{
			while (name[i] != ' ' && name[i] != '\0' && name[i] != 0)
				i++;
	
			arg = &(name[i+1]);
		}
	
//		printf("%s<<<<<\n",arg);
	}
	if ( arg == 0)
		arg = " ";
	return arg;
}
char *getInstruction(char * line)
{
	int i = 0;
	int j = 0;
	//char * string = (char*)malloc(sizeof(char)*7); 
	char *instr   = (char *) malloc(sizeof(char)*7); 
	// size of longest instruction is 7

	line = strtok(line,"\t");
	// getting rid of tabs

	if ( line != 0)
	{
		while( line[i] == ' ' && line[i] != 0)
			i++;
	
		while( line[i] != ' ' && line[i] != 0)
		{
			instr[j] = line[i];
			j++;
			i++;
		}
		//printf("getting here%d\n", line[2]);
		instr[j] = '\0';
		//printf("I IS EQQUAL TOOOO%d\n",i);
	}
	if( instr == 0 )
		instr = " ";
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

