%{

#include <iostream> 
#include "syntaxTree.h"
# define YY_NO_UNPUT
#include "Interpreter.hpp"
#define verbose(x) //std::cout<<"LEX found "<<x<<"\n"

%}

%%

"read"			{yylval = new SNode(READ);				return READ;}
"write"			{yylval = new SNode(WRITE);				return WRITE;}
"start"			{yylval = new SNode(START);				return START;}
"end"			{yylval = new SNode(END);				return END;}
"if"			{yylval = new SNode(IF);				return IF;}
"then"			{yylval = new SNode(THEN);				return THEN;}
"endif"			{yylval = new SNode(ENDIF);				return ENDIF;}
"while"			{yylval = new SNode(WHILE);				return WHILE;}
"do"			{yylval = new SNode(DO);				return DO;}
"endwhile"		{yylval = new SNode(ENDWHILE);			return ENDWHILE;}
"=="			{yylval = new SNode(ISEQ);				return ISEQ;}
"!="			{yylval = new SNode(NOTEQ);				return NOTEQ;}
[a-z]			{yylval = new SNode(ID, *yytext-'a');	return ID;}
[0-9]+			{yylval = new SNode(NUM, atoi(yytext));	return NUM;}
"+"				{yylval = new SNode('+');				return *yytext;}
"-"				{yylval = new SNode('-');				return *yytext;}
"*"				{yylval = new SNode('*');				return *yytext;}
"/"				{yylval = new SNode('/');				return *yytext;}
"^"				{yylval = new SNode('^');				return *yytext;}
"="				{yylval = new SNode('=');				return *yytext;}
"<"				{yylval = new SNode('<');				return *yytext;}
">"				{yylval = new SNode('>');				return *yytext;}
"("				{return *yytext;}
")"				{return *yytext;}
";"				{return *yytext;}
"\n"			{}
.				{}

%%

int yywrap(){
	return 1;
}