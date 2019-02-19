//#include "convert.h"
#include "stdio.h"
#include "tree.h"
#include "stdlib.h"

Stack* makeStack()
{
	Stack *newStack = (Stack*) malloc(sizeof(Stack *));

	newStack -> bottom = NULL;
	newStack -> top    = NULL;

	return(newStack);
}

Node* pop(Stack* stack)
{
	if( stack -> top != NULL)
	{
		// unempty stack
		Node *tmp = stack -> top;

		stack -> top = stack -> top -> back;

		tmp -> back = NULL;
		tmp -> next = NULL;
		return(tmp);
	}
}
void push(Stack *stack, Node* newNode)
{
	if (stack ->top != NULL)
	{
		// Unempty stack
		stack   -> top -> next = newNode;
		newNode -> back        = stack -> top;

		stack -> top = newNode;
	}
	else
	{
		// empty stack
		stack -> top    = newNode;
		stack -> bottom = newNode;
	}
}

char* infix2postfix(char * infix)
{
	char *postfix    = (char *) malloc(sizeof(char)*strlen(infix));
	int  i;
	int  j    = 0;
	char oper = 0;

	Stack* opstack    = makeStack();	
	
	for( i=0;i<strlen(infix);i++)
	{
		if(infix[i] == '+' || infix[i] == '-' || 
		   infix[i] == '/' || infix[i] == '*' )
		{	
			//printf(" ");
			postfix[j] = ' ';
			push(opstack,makeNode(infix[i]));
			j++;
		}
		else if( infix[i] == ')')
		{
			oper = pop(opstack)->data;
			//printf("%c",oper);
			postfix[j] = ' ';
			postfix[j+1] = oper;
			j+=2;
		}
		else if( infix[i] != '(')
		{
			//printf("%c",infix[i]);
			postfix[j] = infix[i];
			j++;
		}
	}
	return(postfix);
}




