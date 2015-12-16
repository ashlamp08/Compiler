%{
	#include<stdio.h>
	#include<stdlib.h>
	#include<stdbool.h>
	#include<string.h>
	#include<malloc.h>
	#include "symbol_table_check.h"
	#include "y.tab.h"
%}

%%
	
"decl" 		{return DECL;}
"enddecl"	{return ENDDECL;}
"begin"		{return BEG;}
"end"		{return END;}
"if"		{return IF;}
"then"		{return THEN;}
"else"		{return ELSE;}
"endif"		{return ENDIF;}
"while"		{return WHILE;}
"do"		{return DO;}
"endwhile"	{return ENDWHILE;}
"read"		{return READ;}
"write"		{return WRITE;}
"=="		{return EQEQ;}
"!="		{return NEQ;}
"<"		{return LTHAN;}
">"		{return GTHAN;}
"<="		{return LEQ;}
">="		{return GEQ;}
"AND"		{return AND;}
"OR"		{return OR;}
"NOT"		{return NOT;}

"integer"	{return INTEGER;}
"boolean"	{return BOOLEAN;}
"true"		{symbol* ptr = (symbol *)malloc(sizeof(symbol));
		ptr->datatype = 0;
		ptr->store.bool_store = (bool *)malloc(sizeof(bool));
		*(ptr->store.bool_store) = true;
		strcpy(ptr->name,yytext); yylval = ptr; return BOOLE;}

"false"		{symbol* ptr = (symbol *)malloc(sizeof(symbol));
		ptr->datatype = 0;
		ptr->store.bool_store = (bool *)malloc(sizeof(bool));
		*(ptr->store.bool_store) = false; 
		strcpy(ptr->name,yytext); yylval = ptr; return BOOLE;}

[_a-zA-Z]+   	{symbol* ptr = (symbol *)malloc(sizeof(symbol));
		strcpy(ptr->name,yytext); yylval = ptr; return ID;}

[0-9]+		{symbol* ptr = (symbol *)malloc(sizeof(symbol));
		ptr->datatype = 1;
		ptr->store.int_store = (int *)malloc(sizeof(int));
		*(ptr->store.int_store) = atoi(yytext); 
		strcpy(ptr->name,yytext); yylval = ptr; return NUM;}

"\n"		{}
[ \t]		{}
.		{return *yytext;}


%%

yywrap()
{
	return 1;
}



