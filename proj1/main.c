#include <stdio.h>
#include "tree.h"

int main()
{
	Node* myNode = makeNode('7');

	printf("MY NODE HAS A VALUE OF %c\n", myNode -> data);

	return 0;
}
