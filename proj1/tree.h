#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// TODO: Rename this to something more appropriate --
//		 BC right now it;s storing BOTH data structures

// TODO: Think of how to handle OPERAND vs OPERATOR data section
//       Maybe make a bitmask to show which one it is?

//extern FILE* INPUT;

struct node
{
	char data;
	struct node *parent;
	struct node *leftChild;
	struct node *rightChild;

	//Below are only used for the stack
	struct node *next;
	struct node *back;
};

typedef struct node Node;

struct stack	// cobbling together a stack
{
	Node *bottom;
	Node *top;
};
typedef struct stack Stack;

Node *pop(Stack*);
void push(Stack*,Node*);
Stack* makeStack();
char* infix2postfix(char *);	// converts an infix string to a postfix string

Node *makeNode(char); 		// create new node containing data
void addRightChild(Node*,Node*);	// create right child node
void addLeftChild(Node*,Node*);

#endif
