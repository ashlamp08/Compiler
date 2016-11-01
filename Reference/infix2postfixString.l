%{

#include <iostream> 
#define YYSTYPE std::string 
#include "infix2postfixString.hpp"
#define verbose(x) ;//std::cout<<"LEX found "<<x<<"\n"

%}

%%

[A-Za-z]+		{verbose(yytext);yylval.assign(yytext);return ALPHABET;}
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