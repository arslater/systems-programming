////////////////////////////////////////////////////
// Anita Slater
// CSI 402: Systems Programming - proj2
// 2/28/2019
//
// data.c: Contains the implementations of the data
//		   structure manipulation functions.

#include"data.h"

/////////////////////////////////////////////
// Implementations of Node Manipulation Function(s)
//
Node *makeNode(char * name, int value)
{
	// initialize a node with a given nariable name (NULL
	// if it's just an integer) and value.
	Node* newNode = (Node*)malloc(sizeof(Node));

	newNode -> value = value;
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
