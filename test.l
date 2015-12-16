%{
	#include <stdio.h> 
	#include "y.tab.h"
%}

%%

[a-z|A-Z|0-9|_]+   {char *ptr = (char*)malloc(10);strcpy(ptr,yytext); 				yylval=ptr; return ALPHA;}
"\n"    return *yytext;
.	return *yytext;

%%

yywrap()
{
	return 1;
}
      
