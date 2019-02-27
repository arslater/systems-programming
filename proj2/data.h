#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

extern int OPERAND;

///////////////////////////////////////////////////
// Node structure Used by The stack and the tree
// Only the tree uses the '*child' elements
//
struct node
{
	// TODO: Consider making a new Node struct..?
	// Used only for the input Stack
	char * data;

	// Used for the parsing stuff...?
	int value;
	int address;

	//Below are only used for the stack
	struct node *next;
	struct node *back;
};
typedef struct node Node;

// Node manipulation functions
Node *makeNode(char *); 		// create new node containing a string

///////////////////////////////////////////////
// Basic stack structure 
struct stack	
{
	Node *bottom;
	Node *top;
};
typedef struct stack Stack;

// Stack manipulation functions
Stack *makeStack();				 // allocates memory for a new stack
Node  *pop(Stack*);				 // Returns the popped Node
void   push(Stack*,Node*);		 // Pushesa new node to the stack
char  *stack2string(Stack *,int);// (for debugging) stack -> string
Stack *reverseStack(Stack*);	 // reverses order for the stack


#endif
