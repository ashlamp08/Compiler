%{
	#include <stdio.h> 
	#include "y.tab.h"
%}

%%

[0-9]+ 	{yylval=atoi(yytext); return DIGIT;}
"\n"    return *yytext;
"+" 	return *yytext;
"*" 	return *yytext;
"-" 	return *yytext;
"/" 	return *yytext;
"(" 	return *yytext;
")" 	return *yytext;

%%

yywrap()
{
	return 1;
}
      
