%{
	#include<stdlib.h>
	#include<string.h>
	#include<malloc.h>
	#include "exptree.h"

	void yyerror(char *);
	#include "y.tab.h"
%}

%%

[0-9]+		{yylval = (node *)malloc(sizeof(node));
		yylval-> val = atoi(yytext);
		yylval-> flag = 0;
		yylval-> left = NULL;
		yylval-> right = NULL;
		return DIGIT;}

[-+*/]		{yylval = (node *)malloc(sizeof(node));
		yylval-> op = *yytext;
		yylval-> flag = 1;
		yylval-> left = NULL;
		yylval-> right = NULL;
		return *yytext;}	

[()]		return *yytext;

"\n"		return *yytext;

[ \t]		;			//skip whitspaces

.		yyerror("invalid");
