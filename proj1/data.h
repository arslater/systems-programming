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
	char * data;
	struct node *leftChild;
	struct node *rightChild;

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

//////////////////////////////////////////////////
// Basic Tree
struct tree
{
	Node * root;
};
typedef struct tree Tree;

// Tree manipulation functions
Tree *makeTree();			// allocates memory for a new Tree
Tree *buildTree(Stack*);	/* builds an Exression Tree from a 
							    postfix stack.               */

/////////////////////////////////////////////////////////
// Utility and Evaluation Functions (found in process.c)
//
double  evaluate(Node *);	 /* Takes a root node of a valid expression
							     tree and returns the integer result of
							     the evaluated expression tree        */
void   printTree(Node*);	 // (for debugging) prints the tree
bool   isOperator(char*);	 /* Utility function to determine if the 
							     data string is an operator or not. If
							     it is, then it returns true.         */
Stack *infix2postfix(char *);/* Takes a VALID, parenthesized, string
                                 and converts it to a stack of the 
								 expression in postfix form with NO
								 parenthesis                         */
void rmData(Tree *);		 /* Does the final memory freeing. Only frees the 
								 tree, because the tree was made from popped Nodes
								 from the stack						 */
#endif
