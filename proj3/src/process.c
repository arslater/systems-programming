#include "data.h"
#include "process.h"
#include<unistd.h>
void run(Node *instruction,Stack *scope,Stack *inputStack)
{
	usleep(50000);
	printf("Processing %s [%s] [%s] (%c)\n", instruction->name, getInstruction(instruction->name),getArgument(instruction -> name), getInstruction(instruction->name)[0]);

	switchInstruction(instruction,scope, inputStack);
	
	stack2string(scope,10);
	printf("\n------------------------------------------\n");

	if(instruction -> next != NULL)
		run(instruction -> next,scope,inputStack); // voluntary recursion?!?!?!
}

void switchInstruction(Node* thisNode,Stack *scope,Stack *inputStack)
{
	if( thisNode != 0 && thisNode -> name != 0)
	{
		char * line = thisNode -> name;
		char * instruction = getInstruction(line);

//		printf("~~%d~~~\n", isStackOprn(instruction));

		if(isLogclOprn(instruction))
			doLogclOprn(instruction,scope);
		else if(isRelatOprn(instruction))
			doRelatOprn(instruction,scope);
		else if(isArthmOprn(instruction))
			doArthmOprn(instruction,scope);
		else if(isStackOprn(instruction))
			doStackOprn(line,scope);
		else if(isCntrlOprn(instruction))
			doCntrlOprn(line,scope, inputStack, thisNode);
		else
		{
			doOutput(line,scope);
		}
	}
	else
		////////////////////////////////
		// White spaces messing everything up!!
		run(thisNode -> next,scope,inputStack);
	//free(instruction);
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

	return( (strcmp(line,"pop") == 0)  || (strcmp(line,"push") == 0) 
		 || (strcmp(line,"rvalue") == 0) || (strcmp(line,"lvalue") == 0)
		 || (strcmp(line,":=") == 0));
}
bool isCntrlOprn(char * line)
{
	/////////////////////////////////
	// label, goto, gotrue, gofalse, halt
	//

	return( (strcmp(line,"label") == 0) || (strcmp(line,"goto") ==0) 
			|| (strcmp(line,"gofalse")==0) || (strcmp(line,"gotrue")==0)
			||(strcmp(line,"halt")==0));
}
bool isOutput(char * line)
{
	//////////////////////////////
	// "show,print"
	//	
	
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
                push(scope,makeNode(NULL,pype(oper1,oper2)));

}
void  doRelatOprn(char *line,Stack* scope)
{
    int oper1 = scope->top -> value;
    int oper2 = scope->top->back -> value;

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
				break;
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

		doPush(scope,atoi(getArgument(line)),getArgument(line),getNextAddr(scope)+1);
	}
	else if(strstr(line,"rvalue") != NULL)
		rvalue(line, scope);
	else if(strstr(line,"lvalue") != NULL)
		lvalue(line,scope);
	else if(strstr(getInstruction(line),":=")!= NULL)
		eval(scope);
}
void  doCntrlOprn(char * line, Stack *scope, Stack *inputStack,Node * curNode)
{
	////////////////////////////////////
	// goto

	if(strcmp(getInstruction(line),"goto") == 0)
		run(got(line,inputStack), scope,inputStack);
	else if(strcmp(getInstruction(line),"halt") == 0 )
		exit(1); // make me better!!!! call cleanup function
	else if(strcmp(getInstruction(line),"gofalse") == 0)
		gofalse(line,scope,inputStack);
	else if(strcmp(getInstruction(line),"gotrue") == 0)
		gotrue(line,scope,inputStack);
	else if(strcmp(getInstruction(line),"label") == 0)
		run(curNode -> next, scope,inputStack); 
		// TODO: better way of doing this bc, goes back to itself
}

void  doOutput(char *line,Stack* scope)
{
	char *argument  = "\n";
	int i           = 0;


//	printf("*********%s**************\n", getInstruction(line));
//	printf("=========%s==============\n", getArgument(line));

	if( strcmp(line, "show")!= 0)
		argument = getArgument(line);
	
	if( (strstr(line,"show")) != NULL)
		fprintf(FP,"%s\n", argument);
	else
	{
		//printf("$$$$$Printing!!\n");
		fprintf(FP,"%d\n",scope ->top -> value);
	}
	// show the current stack rn
//	stack2string(scope,10);
//	printf("\n");
}
void doPush(Stack* scope, int value, char *name, int address)
{
	/////////////////////////////////////
	// Push to the stack

	push(scope,makeNode(name, value));
	if( scope -> top -> back != NULL)
		scope -> top -> address = address+1;
	else
		scope -> top -> address = 0;
}
