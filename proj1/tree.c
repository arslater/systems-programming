#include<stdio.h>
#include"tree.h"
#include<stdlib.h>
#include<stdio.h>

Node *makeNode(char data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode -> data = data;

	newNode -> parent    = NULL;
	newNode -> leftChild = NULL;
	newNode -> rightChild= NULL;
	
	// stack elements
	newNode -> next = NULL;
	newNode -> back = NULL;

	return newNode;
}
void addRightChild(Node *root, Node *rightNode)
{
	rightNode -> parent     = root;
	root      -> rightChild = rightNode;
}
void addLeftChild(Node *root, Node *leftNode)
{
	leftNode -> parent     = root;
	root      -> leftChild = leftNode;
}
