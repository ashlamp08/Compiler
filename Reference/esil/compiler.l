%{

#include <iostream>
#include "syntaxTree.h"
#define YY_NO_UNPUT
#define verbose(x) ;//std::cout<<"LEX found "<<x<<" at "<<__LINE__<<lineNumber<<","<<colNumber<<" \n"
#include "compiler.hpp"
unsigned lineNumber = 1;
unsigned colNumber = 1;

%}

A 	[a-zA-Z]
D 	[0-9]
AD	[a-zA-Z0-9]

%%

"read"		{verbose(yytext);yylval = new SNode(READ,lineNumber,colNumber);				colNumber+=yyleng;	return READ;}
"write"		{verbose(yytext);yylval = new SNode(WRITE,lineNumber,colNumber);			colNumber+=yyleng;	return WRITE;}
"begin"		{verbose(yytext);yylval = new SNode(START,lineNumber,colNumber);			colNumber+=yyleng;	return START;}
"end"		{verbose(yytext);yylval = new SNode(END,lineNumber,colNumber);				colNumber+=yyleng;	return END;}
"if"		{verbose(yytext);yylval = new SNode(IF,lineNumber,colNumber);				colNumber+=yyleng;	return IF;}
"then"		{verbose(yytext);yylval = new SNode(THEN,lineNumber,colNumber);				colNumber+=yyleng;	return THEN;}
"else"		{verbose(yytext);yylval = new SNode(ELSE,lineNumber,colNumber);				colNumber+=yyleng;	return ELSE;}
"endif"		{verbose(yytext);yylval = new SNode(ENDIF,lineNumber,colNumber);			colNumber+=yyleng;	return ENDIF;}
"while"		{verbose(yytext);yylval = new SNode(WHILE,lineNumber,colNumber);			colNumber+=yyleng;	return WHILE;}
"do"		{verbose(yytext);yylval = new SNode(DO,lineNumber,colNumber);				colNumber+=yyleng;	return DO;}
"endwhile"	{verbose(yytext);yylval = new SNode(ENDWHILE,lineNumber,colNumber);			colNumber+=yyleng;	return ENDWHILE;}
"decl"		{verbose(yytext);yylval = new SNode(STARTDECL,lineNumber,colNumber);		colNumber+=yyleng;	return STARTDECL;}
"enddecl"	{verbose(yytext);yylval = new SNode(ENDDECL,lineNumber,colNumber);			colNumber+=yyleng;	return ENDDECL;}
"integer"	{verbose(yytext);yylval = new SNode(INTEGER,lineNumber,colNumber);			colNumber+=yyleng;	return INTEGER;}
"boolean"	{verbose(yytext);yylval = new SNode(BOOLEAN,lineNumber,colNumber);			colNumber+=yyleng;	return BOOLEAN;}
"<="		{verbose(yytext);yylval = new SNode(LEQ,lineNumber,colNumber);				colNumber+=yyleng;	return LEQ;}
">="		{verbose(yytext);yylval = new SNode(GEQ,lineNumber,colNumber);				colNumber+=yyleng;	return GEQ;}
"=="		{verbose(yytext);yylval = new SNode(ISEQ,lineNumber,colNumber);				colNumber+=yyleng;	return ISEQ;}
"!="		{verbose(yytext);yylval = new SNode(NOTEQ,lineNumber,colNumber);			colNumber+=yyleng;	return NOTEQ;}
"AND"		{verbose(yytext);yylval = new SNode(AND,lineNumber,colNumber);				colNumber+=yyleng;	return AND;}
"OR"		{verbose(yytext);yylval = new SNode(OR,lineNumber,colNumber);				colNumber+=yyleng;	return OR;}
"NOT"		{verbose(yytext);yylval = new SNode(NOT,lineNumber,colNumber);				colNumber+=yyleng;	return NOT;}
"TRUE"		{verbose(yytext);yylval = new SNode(TRUE,"TRUE",lineNumber,colNumber);		colNumber+=yyleng;	return TRUE;}
"FALSE"		{verbose(yytext);yylval = new SNode(FALSE,"FALSE",lineNumber,colNumber);	colNumber+=yyleng;	return FALSE;}
"return"	{verbose(yytext);yylval = new SNode(RETURN,lineNumber,colNumber);			colNumber+=yyleng;	return RETURN;}
"typedef"	{verbose(yytext);yylval = new SNode(TYPEDEF,lineNumber,colNumber);			colNumber+=yyleng;	return TYPEDEF;}
{A}{AD}*	{verbose(yytext);yylval = new SNode(ID,yytext,lineNumber,colNumber);		colNumber+=yyleng;	return ID;}
{D}+		{verbose(yytext);yylval = new SNode(NUM, atoi(yytext),lineNumber,colNumber);colNumber+=yyleng;	return NUM;}
"+"			{verbose(yytext);yylval = new SNode('+',lineNumber,colNumber);				colNumber+=yyleng;	return *yytext;}
"-"			{verbose(yytext);yylval = new SNode('-',lineNumber,colNumber);				colNumber+=yyleng;	return *yytext;}
"*"			{verbose(yytext);yylval = new SNode('*',lineNumber,colNumber);				colNumber+=yyleng;	return *yytext;}
"/"			{verbose(yytext);yylval = new SNode('/',lineNumber,colNumber);				colNumber+=yyleng;	return *yytext;}
"^"			{verbose(yytext);yylval = new SNode('^',lineNumber,colNumber);				colNumber+=yyleng;	return *yytext;}
"="			{verbose(yytext);yylval = new SNode('=',lineNumber,colNumber);				colNumber+=yyleng;	return *yytext;}
"<"			{verbose(yytext);yylval = new SNode('<',lineNumber,colNumber);				colNumber+=yyleng;	return *yytext;}
">"			{verbose(yytext);yylval = new SNode('>',lineNumber,colNumber);				colNumber+=yyleng;	return *yytext;}
"("			{verbose(yytext);yylval=nullptr;											colNumber+=yyleng;	return *yytext;}
")"			{verbose(yytext);yylval=nullptr;											colNumber+=yyleng;	return *yytext;}
"]"			{verbose(yytext);yylval=nullptr;											colNumber+=yyleng;	return *yytext;}
"["			{verbose(yytext);yylval=nullptr;											colNumber+=yyleng;	return *yytext;}
"}"			{verbose(yytext);yylval=nullptr;											colNumber+=yyleng;	return *yytext;}
"{"			{verbose(yytext);yylval=nullptr;											colNumber+=yyleng;	return *yytext;}
";"			{verbose(yytext);yylval=nullptr;											colNumber+=yyleng;	return *yytext;}
","			{verbose(yytext);yylval=nullptr;											colNumber+=yyleng;	return *yytext;}
"&"			{verbose(yytext);yylval=nullptr;											colNumber+=yyleng;	return *yytext;}
"."			{verbose(yytext);yylval=nullptr;											colNumber+=yyleng;	return *yytext;}
"\n"		{lineNumber++; colNumber = 1;}
"\t"		{colNumber+=4;}
.			{colNumber+=yyleng;}

%%

int yywrap(){
	return 1;
}
