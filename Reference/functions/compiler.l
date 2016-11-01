%{

#include <iostream>
#include "syntaxTree.h"
#define YY_NO_UNPUT
#include "compiler.hpp"
#define verbose(x) std::cout<<"LEX found "<<x<<" at "<<lineNumber<<","<<colNumber<<" \n"
unsigned lineNumber = 1;
unsigned colNumber = 1;

%}

%%

"read"			{yylval = new SNode(READ,lineNumber,colNumber);				colNumber+=yyleng;	return READ;}
"write"			{yylval = new SNode(WRITE,lineNumber,colNumber);			colNumber+=yyleng;	return WRITE;}
"begin"			{yylval = new SNode(START,lineNumber,colNumber);			colNumber+=yyleng;	return START;}
"end"			{yylval = new SNode(END,lineNumber,colNumber);				colNumber+=yyleng;	return END;}
"if"			{yylval = new SNode(IF,lineNumber,colNumber);				colNumber+=yyleng;	return IF;}
"then"			{yylval = new SNode(THEN,lineNumber,colNumber);				colNumber+=yyleng;	return THEN;}
"else"			{yylval = new SNode(ELSE,lineNumber,colNumber);				colNumber+=yyleng;	return ELSE;}
"endif"			{yylval = new SNode(ENDIF,lineNumber,colNumber);			colNumber+=yyleng;	return ENDIF;}
"while"			{yylval = new SNode(WHILE,lineNumber,colNumber);			colNumber+=yyleng;	return WHILE;}
"do"			{yylval = new SNode(DO,lineNumber,colNumber);				colNumber+=yyleng;	return DO;}
"endwhile"		{yylval = new SNode(ENDWHILE,lineNumber,colNumber);			colNumber+=yyleng;	return ENDWHILE;}
"decl"			{yylval = new SNode(STARTDECL,lineNumber,colNumber);		colNumber+=yyleng;	return STARTDECL;}
"enddecl"		{yylval = new SNode(ENDDECL,lineNumber,colNumber);			colNumber+=yyleng;	return ENDDECL;}
"integer"		{yylval = new SNode(INTEGER,lineNumber,colNumber);			colNumber+=yyleng;	return INTEGER;}
"boolean"		{yylval = new SNode(BOOLEAN,lineNumber,colNumber);			colNumber+=yyleng;	return BOOLEAN;}
"<="			{yylval = new SNode(LEQ,lineNumber,colNumber);				colNumber+=yyleng;	return LEQ;}
">="			{yylval = new SNode(GEQ,lineNumber,colNumber);				colNumber+=yyleng;	return GEQ;}
"=="			{yylval = new SNode(ISEQ,lineNumber,colNumber);				colNumber+=yyleng;	return ISEQ;}
"!="			{yylval = new SNode(NOTEQ,lineNumber,colNumber);			colNumber+=yyleng;	return NOTEQ;}
"AND"			{yylval = new SNode(AND,lineNumber,colNumber);				colNumber+=yyleng;	return AND;}
"OR"			{yylval = new SNode(OR,lineNumber,colNumber);				colNumber+=yyleng;	return OR;}
"NOT"			{yylval = new SNode(NOT,lineNumber,colNumber);				colNumber+=yyleng;	return NOT;}
"TRUE"			{yylval = new SNode(TRUE,"TRUE",lineNumber,colNumber);		colNumber+=yyleng;	return TRUE;}
"FALSE"			{yylval = new SNode(FALSE,"FALSE",lineNumber,colNumber);	colNumber+=yyleng;	return FALSE;}
"return"		{yylval = new SNode(RETURN,lineNumber,colNumber);			colNumber+=yyleng;	return RETURN;}
[a-zA-Z][a-zA-Z0-9]*	{yylval = new SNode(ID,yytext,lineNumber,colNumber);		colNumber+=yyleng;	return ID;}
[0-9]+			{yylval = new SNode(NUM, atoi(yytext),lineNumber,colNumber);colNumber+=yyleng;	return NUM;}
"+"				{yylval = new SNode('+',lineNumber,colNumber);				colNumber+=yyleng;	return *yytext;}
"-"				{yylval = new SNode('-',lineNumber,colNumber);				colNumber+=yyleng;	return *yytext;}
"*"				{yylval = new SNode('*',lineNumber,colNumber);				colNumber+=yyleng;	return *yytext;}
"/"				{yylval = new SNode('/',lineNumber,colNumber);				colNumber+=yyleng;	return *yytext;}
"^"				{yylval = new SNode('^',lineNumber,colNumber);				colNumber+=yyleng;	return *yytext;}
"="				{yylval = new SNode('=',lineNumber,colNumber);				colNumber+=yyleng;	return *yytext;}
"<"				{yylval = new SNode('<',lineNumber,colNumber);				colNumber+=yyleng;	return *yytext;}
">"				{yylval = new SNode('>',lineNumber,colNumber);				colNumber+=yyleng;	return *yytext;}
"("				{yylval=nullptr;											colNumber+=yyleng;	return *yytext;}
")"				{yylval=nullptr;											colNumber+=yyleng;	return *yytext;}
"]"				{yylval=nullptr;											colNumber+=yyleng;	return *yytext;}
"["				{yylval=nullptr;											colNumber+=yyleng;	return *yytext;}
"}"				{yylval=nullptr;											colNumber+=yyleng;	return *yytext;}
"{"				{yylval=nullptr;											colNumber+=yyleng;	return *yytext;}
";"				{yylval=nullptr;											colNumber+=yyleng;	return *yytext;}
","				{yylval=nullptr;											colNumber+=yyleng;	return *yytext;}
"&"				{yylval=nullptr;											colNumber+=yyleng;	return *yytext;}
"\n"			{lineNumber++; colNumber = 1;}
"\t"			{colNumber+=4;}
.				{colNumber+=yyleng;}

%%

int yywrap(){
	return 1;
}
