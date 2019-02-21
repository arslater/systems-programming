#include<stdio.h>
#include"data.h"
#include<stdlib.h>
#include<stdio.h>

Node *makeNode(char * data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode -> data = data;

	newNode -> above     = NULL;
	newNode -> leftChild = NULL;
	newNode -> rightChild= NULL;
	
	// stack elements
	newNode -> next = NULL;
	newNode -> back = NULL;

	return newNode;
}

Tree *makeTree()
{
	Tree *tree = (Tree *) malloc(sizeof(Tree));
	tree -> root = NULL;

	return tree;
}

void addChild(Node *parent, Node* newNode,Stack* operandStack)
{
//	printf("ADDING %s\n", newNode ->data);
	if (parent -> leftChild == NULL)
	{
		// Left node hasn't been filled yet
		// TODO: Work out logic ot make this smoother
		parent ->leftChild = newNode;
		parent -> leftChild -> above = parent;
	}
	else
	{
		//Should always be the right child for this else..
		// TODO: Check it
		parent -> rightChild = newNode;
		parent -> rightChild ->above   = parent;
	}

}
Tree *buildTree(Stack *pfStack)
{
	Tree *tree = makeTree();
	Node *root;
	Stack * opStack = makeStack();
	tree ->root = root;
	Node *tmp;
	Node *tmp1;
	
	for(tmp = pop(pfStack); tmp != NULL; tmp=pop(pfStack))
	{
		printf("%s|", tmp -> data);	
		if( isOperator(tmp ->data))
		{
			// Operator, need to get two values
			printf("Oprator: %s\n",tmp ->data);

			tmp ->leftChild = pop(opStack);
			tmp ->rightChild= pop(opStack);

			push(opStack,tmp);
		}
		else
		{
			// Operand
			printf("Operand: %s\n",tmp ->data);

			push(opStack,tmp);
		}
	}
	tree -> root = opStack-> top;
	return(tree);
}
bool isOperator(char *string)
{
	bool comparison = false;

	if( (strcmp("+",string)==0) || (strcmp("-",string)==0)||
	    (strcmp("/",string)==0) || (strcmp("*",string)==0) )
		comparison = true;

	return(comparison);
}
void printTree(Node *root)
{
	Node *tmp = root;
	
	if(tmp != NULL)
	{
		printTree(tmp ->leftChild);
		printTree(tmp ->rightChild);

		printf("%s ",tmp -> data);
	}
}
