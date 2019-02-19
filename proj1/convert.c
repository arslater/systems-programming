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

void pop(Stack* stack)
{
	if( stack -> top != NULL)
	{
		// unempty stack
		Node *tmp = stack -> top;

		stack -> top = stack -> top -> back;

		tmp -> back = NULL;
		tmp -> next = NULL;
		free(tmp);
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

