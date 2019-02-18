#include<stdio.h>
#include"tree.h"
#include<stdlib.h>
#include<stdio.h>

Node *makeNode(char data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode -> data = data;

	return newNode;
}
