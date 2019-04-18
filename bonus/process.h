#ifndef PROCESS_H
#define PROCESS_H
#include "data.h"

void run(Node *,Stack *,Stack *);	
void switchInstruction(Node *, Stack*,Stack*); // switches instruction to approp place

// Cleaning up logic
bool isLogclOprn(char *);
bool isRelatOprn(char *);
bool isArthmOprn(char *);
bool isStackOprn(char *);
bool isCntrlOprn(char *);
bool isOutput(char *);

void doLogclOprn(char *,Stack*);
void doRelatOprn(char *,Stack*);
void doArthmOprn(char *,Stack*);
void doStackOprn(char *,Stack*);
void doCntrlOprn(char *,Stack*,Stack *,Node *);
void doOutput(char *,Stack*);

int sum(int,int);	// +
int sub(int,int);	// -
int mul(int,int);	// *
int divi(int,int);	// "\"
int mod(int,int);	// %

int bang(int);		// !
int pype(int,int);	// |
int ampr(int,int);	// &

void doPush(Stack*,int, char *,int); // includes the address now
void rvalue(char *, Stack*);
void lvalue(char *, Stack*);
void eval(Stack *);	// :=

int equ(int,int);
int leq(int,int);
int geq(int,int);// >=
int lt(int,int);
int gt(int,int); // >
int neq(int,int);

Node *got(char *, Stack*);		// goto is a keyword
void gofalse(char *, Stack*,Stack *);
void gotrue(char *,Stack*,Stack*);
void clean(Stack*, Stack*);

//utility functions
Node *inStack(char *, Stack*);
char *getArgument(char *);
char *getInstruction(char*);
int   getNextAddr(Stack*);
#endif
