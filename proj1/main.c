#include <stdio.h>
#include "data.h"
#include <stdlib.h>

int main(int argc, char ** argv)
{
	FILE *fp;
	char * string ="(((AYYYY+B)*C)-((D-E)*(F+G)))";
	Tree *expTree = makeTree();

	string = "((5+4)+(7*9))"; 
//	string = "((5+4)*3)";
	Stack *myStack = makeStack();
	myStack = infix2postfix(string);
	myStack = reverseStack(myStack);
	//printf("Finsihed with no errors!%s\n",myStack->bottom ->data);
	printf("%s\n", stack2string(myStack, strlen(string)));
	
	expTree = buildTree(myStack);
	printTree(expTree->root);
	printf("%d\n",evaluate(expTree->root));
	return 0;
}
