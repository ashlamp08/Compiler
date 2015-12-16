%{
	#include <stdio.h> 
	#include "y.tab.h"
	#include <string.h>

	#define YYSTYPE char*

%}

%%

[0-9A-Za-z]+ 	{char *ptr = (char*)malloc(10);strcpy(ptr,yytext); 				yylval=ptr; return ALPHA;}
"\n"    {char *ptr = (char*)malloc(3);strcpy(ptr,yytext); 				yylval=ptr; return *yytext;}
["+"|"-"|"*"|"/"|"("|")"]       {char *ptr = (char*)malloc(3);strcpy(ptr,yytext); 				yylval=ptr; return *yytext;}
%%

yywrap()
{
	return 1;
}
      
