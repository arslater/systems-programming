//#include "convert.h"
#include "stdio.h"
#include "data.h"
#include "stdlib.h"

Stack* makeStack()
{
	Stack *newStack = (Stack*) malloc(sizeof(Stack *));

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
		return(tmp);
	}
}
void push(Stack *stack, Node* newNode)
{
	if (stack ->top != NULL)
	{
		// Unempty stack

		// Comaptibility with tree
		newNode -> above = stack -> top;

		stack   -> top -> next = newNode;
		newNode -> back        = stack -> top;

		stack -> top = newNode;
	}
	else
	{
		// empty stack
		stack -> top    = newNode;
		stack -> bottom = newNode;
	}
}

Stack *infix2postfix(char * infix)
{
	int j = 0;
	int i;
	int k = 0;
	int l = 0;
	char **operands = (char **) malloc(sizeof(char *)*100);
	// TODO: MAKE THIS A SMART/DYNAMIC MEMORY ALLOCATION
	operands[0] = (char *) malloc(sizeof(char)*16);

	char **operator = (char **) malloc(sizeof(char*)*64);
    operator[l] = (char *) malloc(sizeof(char)*16); 

	Stack *opstack = makeStack();
	Stack *restack = makeStack();

	for( i=0;i<strlen(infix);i++)
	{
		if(infix[i] == '+' || infix[i] == '-' || 
		   infix[i] == '/' || infix[i] == '*' )
		{
			// encountered an operator
			operator[l][0] = infix[i];

			push(opstack,makeNode(operator[l]));
			l++;
			operator[l] = (char *) malloc(sizeof(char)*16); 

			if (operands[j][0] != -1)
			{
				push(restack,makeNode((operands[j])));	
				j++;
				k=0;
			
				operands[j] = (char *) malloc(sizeof(char)*16);
				// TODO: Change this to operand limit

				operands[j][0] = -1;
			}			
		}
		else if( infix[i] == ')')
		{
			if ( operands[j][0] != -1)
			{
				push(restack,makeNode(operands[j]));

				j++;		
				operands[j] = (char *) malloc(sizeof(char)*16);
				// TODO: Change this to operand limit
				k=0;
				operands[j][0] = -1;
			}
			push(restack,pop(opstack));
		}
		else if( infix[i] != '(')
		{
			// Encountering the operands	
			operands[j][k] = infix[i];
			k++;
		}		
	}
	return(restack);
}

char * stack2string(Stack* expression, int length)
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
int evaluate(Node *root)
{
	int left  = 0;
	int right = 0;

	if(root != NULL)
	{
		if( !isOperator(root->data))
			return(atoi(root ->data));
		else
		{
			left  = evaluate(root->leftChild);
			right = evaluate(root->rightChild);
		
			if      (strcmp("+",root->data) == 0)
				return(left+right);
			else if (strcmp("-",root->data)==0)
				return(left-right);
			else if (strcmp("/",root->data)==0)
				return(left/right);
			else if(strcmp("*",root->data)==0)
				return(left*right);
		}
	}
}
