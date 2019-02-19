#include <stdio.h>
#include "tree.h"
#include <stdlib.h>

int main(int argc, char ** argv)
{
	FILE *fp;
	
	/*Node* pNode = makeNode('P');
	Node* rchld = makeNode('R');

	addRightChild(pNode,rchld);

	printf("MY NODE HAS A VALUE OF %c\n", rchld ->data);
	*/

	// Testing out my AWFUL stack

	Stack *myStack = makeStack();
	int i = 0;

	push(myStack,makeNode('1'));
	push(myStack,makeNode('2'));
	push(myStack,makeNode('3'));
	push(myStack,makeNode('4'));
	push(myStack,makeNode('5'));

	pop(myStack);
	pop(myStack);
	Node*tmp = myStack -> top;
	//printf("*****");
	//printf("%c:::", myStack ->top ->data);
	
	while(tmp != NULL)
	{
		printf("%c\n",tmp ->data);
		tmp = tmp -> back;
	}
/*
	fp = fopen(argv[1],"r");
	if (fp == NULL)
	{
		fprintf(stderr,"Error opening '%s' for reading. Exiting...\n",argv[1]);
		exit(1);
	}
*/	
	return 0;
}
