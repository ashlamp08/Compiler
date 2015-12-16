#include<stdbool.h>

union sto
{
	bool* bool_store;
	int* int_store;
};

typedef struct ssymbol
{
	char name[30];	
	int datatype;
	int size;
	union sto store;
}symbol;

#define YYSTYPE symbol *


