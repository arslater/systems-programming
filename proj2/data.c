#include<stdio.h>
#include"data.h"
#include<stdlib.h>
#include<stdio.h>

/////////////////////////////////////////////
// Implementations of Node Manipulation Function(s)
//
Node *makeNode(char * data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode -> data = data;

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
char * stack2string(Stack* expression, int length)// [debugging]
{
	Node *tmp;
	int  i    = 0;
	char *returnString = (char *)malloc(sizeof(char)*length);

	for(tmp = expression -> top; tmp != NULL; tmp = tmp -> back)
	{	
		strcat(returnString,tmp -> data);
		strcat(returnString," ");
		i+=2;
	}
		
	printf("\n");
	return(returnString);
}
Stack * reverseStack(Stack* stack)
{
	Node * tmp;
	Node * tmp1;
	Stack *newStack = makeStack();
	
	for(tmp = stack -> top; tmp != NULL; tmp = stack->top)
		push(newStack,pop(stack));

	return(newStack);
}

////////////////////////////////////////////////
// Implementations of Tree Manipulation Functions(s)
//
Tree *buildTree(Stack *pfStack) 
{	
	Tree *tree = makeTree();	
	Stack * opStack = makeStack();	
	Node *tmp;
	
	for(tmp = pop(pfStack); tmp != NULL; tmp=pop(pfStack))
	{	
		if( isOperator(tmp ->data))
		{
			// Operator, need to get its children
			tmp ->leftChild = pop(opStack);
			tmp ->rightChild= pop(opStack);

			push(opStack,tmp); // push this subtree on the stack
		}
		else
		{
			// Operand, just push onto the stack
			push(opStack,tmp);
		}
	}
	tree -> root = opStack-> top;
	/* the only remaining node in the stack will represent the root 
	   node of the tree, because it is the result of merging all of
	   the other operations                                    
	*/
	return(tree);
}

void printTree(Node *root) // [Debugging] Prints tree from root
{
	Node *tmp = root;
	
	if(tmp != NULL)
	{
		printTree(tmp ->leftChild);
		printTree(tmp ->rightChild);

		printf("%s ",tmp -> data);
	}
}
