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
	return(oper1 != oper2);}
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

	char * label = (char*) malloc(sizeof(char)*strlen(line));
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

void call(Node *position, char *line, Stack*scope, Stack *inputStack)
{
    scope -> ra = position;
    // save position. Will need this for later

    run(got(line,inputStack),scope,inputStack);
    // basically a goto, so let's use that function

}

void end(Stack *inputStack,Node *pos)
{
	////////////////////////
	// pops the top node from the scope stack
	//
    printf("ending!\n");
	//popStack(STACKOFSCOPES); //I don't pop I guess...???????

	//Node *ra = STACKOFSCOPES->top->ra;
	// so the current stack is now the top of stack of scopes
	run(pos->next,STACKOFSCOPES->top,inputStack);

}

void retn(Stack *inputStack,Stack *scope)
{
    printf("returning\n");

    // return does not pop any stacks

	//Node * ra = STACKOFSCOPES -> top -> back ->ra;
    run(scope ->ra->next,scope,inputStack);
}

void begin(Stack* inputStack, Stack*scope, Node *pos)
{
	/////////////////////////////////////
	// Creates a new Node with a "heap stack"
	// and then pushes it
	//
    printf("beginning\n");
   // Stack * heap    = makeStack();

    // push the saved address as the top node
    // of the previous stack


	//Making a newNode onto the stack, which contains
	// a "heap" a stack of all subroutine instructions

	// we also want to add this new instruction set
	// scope to the stack of scopes
	//scope -> top ->position = pos;
	//pushStack(STACKOFSCOPES,heap);

	//run(pos ->next,heap,inputStack);
	run(pos->next,scope,inputStack);
}