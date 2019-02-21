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
	//Stack * operandStack = makeStack();
	Tree *tree = makeTree();
	Node *root = pop(pfStack);
	tree ->root = root;
	Node *tmp;

	//printf("%s##\n", tree->root->data);
//	printf("%s^^\n", pfStack ->top ->data);
	for(tmp = root; tmp != pfStack ->bottom; tmp=pop(pfStack))
	{
	//	printf(">%s\n", tmp ->data);
		addChild(tmp, pfStack->top,pfStack);
		if( pfStack ->top ->back != NULL)
			addChild(tmp,pfStack->top->back,pfStack);
	}
	return(tree);
}
void printTree(Tree *expTree)
{
	Node *tmp = expTree -> root;
	printf("%s ",tmp ->data);

	while(tmp ->leftChild != NULL)
	{
		//printf("%s ", tmp -> data);
		printf("%s ", tmp -> leftChild -> data);
		printf("%s ", tmp -> rightChild ->data);
		tmp = tmp ->rightChild;
	}
}
