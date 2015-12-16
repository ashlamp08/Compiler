%{
	#include<stdio.h>
	#include<stdlib.h>
	#include "y.tab.h"
	#include "symbol_table.h"
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
[_a-zA-Z]+   	{yylval = yytext; return ID;}

"\n"		{return *yytext;}
[ \t]		{}
.		{return *yytext;}


%%

yywrap()
{
	return 1;
}



