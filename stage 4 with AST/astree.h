#include<stdbool.h>
#include<stdio.h>
#include<string.h>
#include "symbol_table_global.h"

#define INT 1
#define BOOL 0
#define ASSG 10
#define VOID -1

typedef struct astnode
{
	int datatype;
	int nodetype;
	
	char name[20];
	int int_value;		//for constants
	bool bool_value;

	struct astnode *ptr1, *ptr2, *ptr3;

	symbol *Gentry;
 
} ast;

#define YYSTYPE ast *

	
