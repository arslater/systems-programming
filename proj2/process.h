#ifndef PROCESS_H
#define PROCESS_H
#include "data.h"

void switchInstruction(char *, Stack*); // switches instruction to approp place

// Cleaning up logic
bool isLogclOprn(char *);
bool isRelatOprn(char *);
bool isArthmOprn(char *);
bool isStackOprn(char *);
bool isOutput(char *);

void doLogclOprn(char *,Stack*);
void doRelatOprn(char *,Stack*);
void doArthmOprn(char *,Stack*);
void doStackOprn(char *,Stack*);
void doOutput(char *,Stack*);

int sum(int,int);
int sub(int,int);
int mul(int,int);
int divi(int,int);
int mod(int,int);

int bang(int);
int pipe(int,int);
int ampr(int,int);

void rvalue(char *, Stack*);

int equ(int,int);
int leq(int,int);
int geq(int,int);
int lt(int,int);
int gt(int,int);
int neq(int,int);

#endif
