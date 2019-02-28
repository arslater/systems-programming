//////////////////////////////////////////////////
// Anita Slater
// CSI 402: Systems Programming - proj 2
// 2/28/2019
//
// data.h: contains all the function prototypes for
//	       the Stack and Node data structures. Also
//		   contains the prototype for the one other
//         function that processes the input line(s)
//         and produces output.

#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

extern FILE*  FP;	// set to stdout or .out file

///////////////////////////////////////////////////
// Node structure used by input stack and working stack
//
struct node
{
	// Broke up the data field into 2 pieces
	int value;	// The integer (NOT a variable name, but hold the value of a variable)
	char *name;	// If a variable, it's name. NULL if just dealing with integers

	//Below are only used for the stack
	struct node *next;
	struct node *back;
};
typedef struct node Node;

// Node manipulation functions
Node *makeNode(char *,int); 		// create new node with a name and value
									// IF a variable is added, it's value is initialized to zero
									// If an integer is added, it's name is NULL

///////////////////////////////////////////////
// Basic stack structure 
struct stack	
{
	Node *bottom;
	Node *top;
};
typedef struct stack Stack;

// Stack manipulation functions
Stack *makeStack();				  // allocates memory for a new stack
Node  *pop(Stack*);				  // Returns the popped Node
void   push(Stack*,Node*);		  // Pushes a new node to the stack
char  *stack2string(Stack *,int); // (for debugging) stack -> string

void doInstruction(char *,Stack*);// I'd love to think of a way to
// make this function more efficient. Right now it's just a whole 
// bunch of ifs. Takes a line from the input stack, and based on the
// instruction type, performs that instruction.
#endif
