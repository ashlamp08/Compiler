%{

#include <iostream>
#include "syntaxTree.h"
#define YY_NO_UNPUT
#include "compiler.hpp"
#define verbose(x) //std::cout<<"LEX found "<<x<<"\n"
unsigned lineNumber;
unsigned colNumber;

%}

%%

"read"			{colNumber+=yyleng;	yylval = new SNode(READ);			return READ;}
"write"			{colNumber+=yyleng;	yylval = new SNode(WRITE);			return WRITE;}
"begin"			{colNumber+=yyleng;	yylval = new SNode(START);			return START;}
"end"			{colNumber+=yyleng;	yylval = new SNode(END);			return END;}
"if"			{colNumber+=yyleng;	yylval = new SNode(IF);				return IF;}
"then"			{colNumber+=yyleng;	yylval = new SNode(THEN);			return THEN;}
"else"			{colNumber+=yyleng;	yylval = new SNode(ELSE);			return ELSE;}
"endif"			{colNumber+=yyleng;	yylval = new SNode(ENDIF);			return ENDIF;}
"while"			{colNumber+=yyleng;	yylval = new SNode(WHILE);			return WHILE;}
"do"			{colNumber+=yyleng;	yylval = new SNode(DO);				return DO;}
"endwhile"		{colNumber+=yyleng;	yylval = new SNode(ENDWHILE);		return ENDWHILE;}
"decl"			{colNumber+=yyleng;	yylval = new SNode(STARTDECL);		return STARTDECL;}
"enddecl"		{colNumber+=yyleng;	yylval = new SNode(ENDDECL);		return ENDDECL;}
"integer"		{colNumber+=yyleng;	yylval = new SNode(INTEGER);		return INTEGER;}
"boolean"		{colNumber+=yyleng;	yylval = new SNode(BOOLEAN);		return BOOLEAN;}
"<="			{colNumber+=yyleng;	yylval = new SNode(LEQ);			return LEQ;}
">="			{colNumber+=yyleng;	yylval = new SNode(GEQ);			return GEQ;}
"=="			{colNumber+=yyleng;	yylval = new SNode(ISEQ);			return ISEQ;}
"!="			{colNumber+=yyleng;	yylval = new SNode(NOTEQ);			return NOTEQ;}
"AND"			{colNumber+=yyleng;	yylval = new SNode(AND);			return AND;}
"OR"			{colNumber+=yyleng;	yylval = new SNode(OR);				return OR;}
"NOT"			{colNumber+=yyleng;	yylval = new SNode(NOT);			return NOT;}
"TRUE"			{colNumber+=yyleng;	yylval = new SNode(TRUE,"TRUE");	return TRUE;}
"FALSE"			{colNumber+=yyleng;	yylval = new SNode(FALSE,"FALSE");	return FALSE;}
[a-z][a-z0-9]*	{colNumber+=yyleng;	yylval = new SNode(ID,yytext);		return ID;}
[0-9]+			{colNumber+=yyleng;	yylval = new SNode(NUM, atoi(yytext));	return NUM;}
"+"				{colNumber+=yyleng;	yylval = new SNode('+');			return *yytext;}
"-"				{colNumber+=yyleng;	yylval = new SNode('-');			return *yytext;}
"*"				{colNumber+=yyleng;	yylval = new SNode('*');			return *yytext;}
"/"				{colNumber+=yyleng;	yylval = new SNode('/');			return *yytext;}
"^"				{colNumber+=yyleng;	yylval = new SNode('^');			return *yytext;}
"="				{colNumber+=yyleng;	yylval = new SNode('=');			return *yytext;}
"<"				{colNumber+=yyleng;	yylval = new SNode('<');			return *yytext;}
">"				{colNumber+=yyleng;	yylval = new SNode('>');			return *yytext;}
"("				{colNumber+=yyleng;	yylval=nullptr;						return *yytext;}
")"				{colNumber+=yyleng;	yylval=nullptr;						return *yytext;}
"]"				{colNumber+=yyleng;	yylval=nullptr;						return *yytext;}
"["				{colNumber+=yyleng;	yylval=nullptr;						return *yytext;}
";"				{colNumber+=yyleng;	yylval=nullptr;						return *yytext;}
","				{colNumber+=yyleng;	yylval=nullptr;						return *yytext;}
"\n"			{lineNumber++; colNumber = 0;}
.				{colNumber+=yyleng;}

%%

int yywrap(){
	return 1;
}
