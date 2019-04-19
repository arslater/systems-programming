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
    newNode -> address = -1;

    newNode -> position = newNode; // idt i need this...

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
	Node * tmp = NULL;
	if( stack -> top != NULL)
	{
		// unempty stack
		tmp = stack -> top;

		stack -> top = stack -> top -> back;

		tmp -> back = NULL;
		tmp -> next = NULL;
	}
	return(tmp); // return the detached node
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
		/*
		strcat(returnString,tmp -> name);
		strcat(returnString,":");
		sprintf(returnString,"%d",tmp -> value);
		strcat(returnString,"|");
		sprintf(returnString,"%d", tmp -> address);
		strcat(returnString," ");
		i+=2;
		*/
		printf("|%s=%d(0x%d) |", tmp -> name,tmp->value,tmp->address);
	}
	return(returnString);
}

GroupStack *makeGroupStack()
{
	GroupStack *newGroup = (GroupStack*) malloc(sizeof(GroupStack));

	newGroup -> top    = NULL;
	newGroup -> bottom = NULL;

	return(newGroup);
}

void pushStack(GroupStack* dest, Stack*src)
{
	/////////////////////////////////
	//Pushing a stack onto a stack
	if (dest -> top != NULL)
	{
		Stack * tmp = dest -> top;

		dest -> top = src;
		src -> back =  tmp;
		tmp -> next = src;
	}
	else
	{
		dest -> top    = src;
		dest -> bottom = src;
	}
}
Stack *popStack(GroupStack* group)
{
	Stack *tmp = NULL;

	if(group-> top != NULL)
	{
		tmp = group->top;
		group->top = tmp->back;

		tmp->next = NULL;
		tmp->back = NULL;
	}
	return(tmp);
}