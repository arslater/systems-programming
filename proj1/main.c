#include <stdio.h>
#include "tree.h"
#include <stdlib.h>

int main(int argc, char ** argv)
{
	FILE *fp;
	Stack *myStack = makeStack();
	printf("%s\n",infix2postfix("(((AYYYY+B)*C)-((D-E)*(F+G)))"));
	return 0;
}
