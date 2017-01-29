#include<stdbool.h>
#include<stdio.h>
#include<string.h>

#define INT 1
#define BOOL 0
#define ASSG 10
#define VOID -1

union st
{
	bool* bool_store;
	int* int_store;
};

typedef struct ssymbol
{
	char name[30];	
	int datatype, size;
	union st store;

} symbol;

