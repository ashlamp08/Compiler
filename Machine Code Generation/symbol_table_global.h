#include<stdbool.h>
#include<stdio.h>
#include<string.h>

#define INT 1
#define BOOL 0
#define ASSG 10
#define VOID -1

typedef struct ssymbol
{
	char name[30];	
	int datatype;
	int size;
	int store;

} symbol;

