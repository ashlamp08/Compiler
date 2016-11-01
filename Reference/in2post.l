%{

#include <iostream> 
#include "in2post.hpp"
#define verbose(x) ;//std::cout<<"LEX found "<<x<<"\n"

%}

%%

[0-9]+			{verbose(yytext);yylval = atoi (yytext);return DIGIT;}
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