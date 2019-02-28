#include<stdio.h>
#include"data.h"
#include<stdlib.h>
#include<stdio.h>


/////////////////////////////////////////////
// Implementations of Node Manipulation Function(s)
//
Node *makeNode(char * name, int value)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode -> data = NULL;

	newNode -> value = value;
	newNode -> address = 0;
	newNode -> name  = name;

	// stack elements
	newNode -> next = NULL;
	newNode -> back = NULL;

	return newNode;
}

////////////////////////////////////////////////
// Implementations of Stack Manipulation Functions(s)
//
Stack* makeStack()
{
	Stack *newStack = (Stack*) malloc(sizeof(Stack));

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
		
		return(tmp); // return the detached node
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
		// Empty stack
		stack -> top    = newNode; /* top and bottom become */
		stack -> bottom = newNode; /* the new/only node     */
	}
}
char * stack2string(Stack* expression, int length)// [debugging]
{
	Node *tmp;
	int  i    = 0;
	char *returnString = (char *)malloc(sizeof(char)*length);

	for(tmp = expression -> top; tmp != NULL; tmp = tmp -> back)
	{	
		strcat(returnString,tmp -> data);
		strcat(returnString," ");
		i+=2;
	}
		
	printf("\n");
	return(returnString);
}
