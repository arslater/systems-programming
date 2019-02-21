#ifndef DATA_H
#define DATA_H

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
	char * data;
	struct node *above;
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

struct tree
{
	Node * root;
};
typedef struct tree Tree;

Tree * makeTree();
void addChild(Node*,Node*,Stack*);
void printTree(Tree*);
Tree *buildTree(Stack*);

Node *pop(Stack*);
void push(Stack*,Node*);
Stack* makeStack();
Stack* infix2postfix(char *);	// converts an infix string to a postfix string
char*   stack2string(Stack *,int);

Node *makeNode(char *); 		// create new node containing data

#endif
