%{
	#include<stdio.h>
	#include<stdlib.h>
	#include<stdbool.h>
	#include<string.h>
	#include<malloc.h>
	#include "astree.h"
	#include "y.tab.h"

	#define INT 1
	#define BOOL 0
	#define ASSG 10
	#define VOID -1
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
"+"		{return PLUS;}
"-"		{return MINUS;}
"*"		{return MUL;}
"/"		{return DIV;}

"integer"	{return INTEGER;}
"boolean"	{return BOOLEAN;}
"true"		{ast* ptr = (ast *)malloc(sizeof(ast));
		make_node(ptr, BOOL, BOOLE, NULL, 0, true, NULL, NULL, NULL, NULL);		
		yylval = ptr; return BOOLE;}

"false"		{ast* ptr = (ast *)malloc(sizeof(ast));
		make_node(ptr, BOOL, BOOLE, NULL, 0, false, NULL, NULL, NULL, NULL);		
		yylval = ptr; return BOOLE;}

[_a-zA-Z]+   	{ast* ptr = (ast *)malloc(sizeof(ast));
		make_node(ptr, VOID, ID, yytext, 0, false, NULL, NULL, NULL, NULL);		
		yylval = ptr; return ID;}

[0-9]+		{ast* ptr = (ast *)malloc(sizeof(ast));
		make_node(ptr, INT, NUM, NULL, atoi(yytext), false, NULL, NULL, NULL, NULL);		
		yylval = ptr; return NUM;}

"\n"		{}
[ \t]		{}
.		{return *yytext;}


%%

yywrap()
{
	return 1;
}



