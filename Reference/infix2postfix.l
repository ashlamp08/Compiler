%{

#include <iostream> 
#include "infix2postfix.hpp"
#define verbose(x) ;//std::cout<<"LEX found "<<x<<"\n"

%}

%%

[A-Za-z]		{verbose(yytext);yylval = *yytext;return ALPHABET;}
"+"				{verbose(yytext);return *yytext;}
"-"				{verbose(yytext);return *yytext;}
"*"				{verbose(yytext);return *yytext;}
"/"				{verbose(yytext);return *yytext;}
"^"				{verbose(yytext);return *yytext;}
"("				{verbose(yytext);return *yytext;}
")"				{verbose(yytext);return *yytext;}
"\n"			{verbose(yytext);return *yytext;}

%%

yywrap(){
	return 1;
}