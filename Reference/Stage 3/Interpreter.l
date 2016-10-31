%{

#include <iostream> 
#include "syntaxTree.h"
#include "Interpreter.hpp"
#define verbose(x) ;//std::cout<<"LEX found "<<x<<"\t";printHex(std::cin.peek())
//std::cout<<"LEX found "<<x<<"\n"

%}

%%

"read"			{verbose(yytext);	yylval = new SNode(READ);				return READ;}
"write"			{verbose(yytext);	yylval = new SNode(WRITE);				return WRITE;}
"start"			{verbose(yytext);	yylval = new SNode(START);				return START;}
"end"			{verbose(yytext);	yylval = new SNode(END);				return END;}
[a-z]			{verbose(yytext);	yylval = new SNode(ID, *yytext-'a');	return ID;}
[0-9]+			{verbose(yytext);	yylval = new SNode(NUM, atoi(yytext));	return NUM;}
"+"				{verbose(yytext);	yylval = new SNode('+');				return *yytext;}
"-"				{verbose(yytext);	yylval = new SNode('-');				return *yytext;}
"*"				{verbose(yytext);	yylval = new SNode('*');				return *yytext;}
"/"				{verbose(yytext);	yylval = new SNode('/');				return *yytext;}
"^"				{verbose(yytext);	yylval = new SNode('^');				return *yytext;}
"="				{verbose(yytext);	yylval = new SNode('=');				return *yytext;}
"("				{verbose(yytext);	return *yytext;}
")"				{verbose(yytext);	return *yytext;}
";"				{verbose(yytext);	return *yytext;}
"\n"			{}
" "				{}
%%

int yywrap(){
	return 1;
}