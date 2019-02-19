#include <stdio.h>
#include "tree.h"

int main()
{
	Node* pNode = makeNode('P');
	Node* rchld = makeNode('R');

	addRightChild(pNode,rchld);

	printf("MY NODE HAS A VALUE OF %c\n", rchld ->data);

	return 0;
}
