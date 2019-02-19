#ifndef TREE_H
#define TREE_H

// TODO: Think of how to handle OPERAND vs OPERATOR data section
//       Maybe make a bitmask to show which one it is?

struct node
{
	char data;
	struct node *parent;
	struct node *leftChild;
	struct node *rightChild;
};

typedef struct node Node;

Node *makeNode(char); 		// create new node containing data
void addRightChild(Node*,Node*);	// create right child node
#endif
