#include<stdbool.h>

union st
{
	bool bool_store;
	int int_store;
};

struct symbol
{
	char name[30];	
	int datatype;
	int size;
	union st store;
};	
			

