#include "stdio.h"
#include "data.h"
#include "stdlib.h"

Stack *infix2postfix(char * infix) // ASSUMES VALID EXPRESSION!!!
{
	int j = 0;	/* Index counters used in array allocation */
	int i;		//
	int k = 0;	//		
	int l = 0;	//

	Stack *opstack = makeStack();	// "working stack"
	Stack *restack = makeStack();	// Result stack

	char **operands = (char **) malloc(sizeof(char *)*strlen(infix));
	// slightly overkill memory allocation, but guarentees
	// the there is enough memory to store each operand
	operands[0] = (char *) malloc(sizeof(char)*OPERAND);

	char **operator = (char **) malloc(sizeof(char*)*strlen(infix));
	// overkill for memory allocation.
    operator[l] = (char *) malloc(sizeof(char)*1); 

	for( i=0;i<strlen(infix);i++)
	{
		if(infix[i] == '+' || infix[i] == '-' || 
		   infix[i] == '/' || infix[i] == '*' )
		{
			// encountered an operator
			operator[l][0] = infix[i];
			// Double pointer to not overwrite strings

			push(opstack,makeNode(operator[l]));
			l++;
			operator[l] = (char *) malloc(sizeof(char)*OPERAND); 

			if (operands[j][0] != -1)
			{
				// not a parenthesis, push an operand
				push(restack,makeNode((operands[j])));	
				j++;
				k=0;
			
				operands[j] = (char *) malloc(sizeof(char)*OPERAND);	
				operands[j][0] = -1; // "reset" operator 
			}			
		}
		else if( infix[i] == ')')
		{
			if ( operands[j][0] != -1)
			{
				// push an operand (rvalue)
				push(restack,makeNode(operands[j]));

				j++;		
				operands[j] = (char *) malloc(sizeof(char)*OPERAND);
				k=0;
				operands[j][0] = -1;
			}
			// pop one of the operators from the stack and
			// push it onto the result stack
			push(restack,pop(opstack));
		}
		else if( infix[i] != '(')
		{
			// Encountering the operands, used for multi-charachter
			// long operands. Each time the loop iterates, this 
			// will append the operand onto the existing operand
			// string.
			operands[j][k] = infix[i];
			k++;
		}		
	}

	// I'm not freeing anything here, because these char*s are still
	// "living" and being used, so freeing them would mean erasing
	// all the data in each of the data nodes.

	return(restack);
}
double evaluate(Node *root) // recursively evaluate each tree
{
	double left  = 0;
	double right = 0;

	if(root != NULL)
	{
		if( !isOperator(root->data))
			return(atof(root ->data)); // Division needs prescision
		else
		{
			left  = evaluate(root->leftChild);
			right = evaluate(root->rightChild);
		
			if      (strcmp("+",root->data) == 0)
				return(left+right);
			else if (strcmp("-",root->data)==0)
				return(right-left); // ORDER MATTERS!!
			else if (strcmp("/",root->data)==0)
				return(right/left); // ORDER MATTERS!!
			else if(strcmp("*",root->data)==0)
				return(left*right);
		}
	}
}
void rmData(Tree *tree) // Final freeing of memory
{
	Node * root = tree -> root;
	Node * tmp  = tree -> root;
	while(root != NULL)
	{
		free(root);
		root = tmp ->next;
	}
	free(tree);
}
bool isOperator(char *string)
{
	bool comparison = false;

	if( (strcmp("+",string)==0) || (strcmp("-",string)==0)||
	    (strcmp("/",string)==0) || (strcmp("*",string)==0) )
		comparison = true;

	return(comparison);
}
