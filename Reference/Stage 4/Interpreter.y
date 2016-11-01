%{
	/*** Auxiliary declarations section ***/

#include <iostream>
#include <cmath>
#include "syntaxTree.h"
#include <string>

extern FILE * yyin;
int yylex();					//	Declarations of Functions
void yyerror (char const *s);	//

SNode *program;

%}

/*** YACC Declarations section ***/
%token ID
%token NUM
%token READ
%token WRITE
%token START
%token END
%token IF
%token THEN
%token ENDIF
%token WHILE
%token DO
%token ENDWHILE
%token ISEQ
%token NOTEQ
%nonassoc NOTEQ
%nonassoc ISEQ
%nonassoc '<'
%nonassoc '>'
%left '+' '-'
%left '*' '/'
%right '^'
%%

/*** Rules Section ***/
PROG:	START SLIST END			{
									program = $2;
									std::cout<<"Program Complete\n";
									delete $1;
									delete $3;
									return 0;
								}
		;
SLIST:	SLIST STMT				{$$=$2;$2->setPrev($1);}
		| STMT					{$$=$1;}
		;

STMT:	ID '=' EXPR	';'			{$$=$2;$$->setPTR1($1);$$->setPTR2($3);}
		| READ '(' ID ')' ';' 	{$$=$1;$$->setPTR2($3);}
		| WRITE '(' EXPR ')' ';'{$$=$1;$$->setPTR2($3);}
		| IF '(' EXPR ')' THEN SLIST ENDIF ';'	
								{
									$$=$1;
									$$->setPTR1($3);
									$$->setPTR2($6);
									delete $5;
									delete $7;
								}
		| WHILE '(' EXPR ')' DO SLIST ENDWHILE ';' 
								{
									
									$$=$1;
									$$->setPTR1($3);
									$$->setPTR2($6);
									delete $5;
									delete $7;
								}
		;

EXPR:	EXPR '+' EXPR			{$$=$2;$$->setPTR1($1);$$->setPTR2($3);}
	    | '-' EXPR				{$$=$1;$$->setPTR1(new SNode(NUM,0));$$->setPTR2($2);}
	    | EXPR '-' EXPR			{$$=$2;$$->setPTR1($1);$$->setPTR2($3);}
	    | EXPR '*' EXPR			{$$=$2;$$->setPTR1($1);$$->setPTR2($3);}
	    | EXPR '/' EXPR			{$$=$2;$$->setPTR1($1);$$->setPTR2($3);}
	    | EXPR '^' EXPR			{$$=$2;$$->setPTR1($1);$$->setPTR2($3);}
		| EXPR '<' EXPR			{$$=$2;$$->setPTR1($1);$$->setPTR2($3);}
		| EXPR '>' EXPR			{$$=$2;$$->setPTR1($1);$$->setPTR2($3);}
		| EXPR ISEQ EXPR		{$$=$2;$$->setPTR1($1);$$->setPTR2($3);}
		| EXPR NOTEQ EXPR		{$$=$2;$$->setPTR1($1);$$->setPTR2($3);}
	    | '(' EXPR ')'			{$$=$2;}
	    | NUM					{$$=$1;}
	    | ID					{$$=$1;}
	    ;		

%%

/*** Auxiliary functions section ***/

void yyerror(char const *s) {
	std::cout<<"YYERROR::"<<s;
}

int main(int argc, char *argv[]) {
//	if(argc!=2){
//		std::cout<<"ERROR:Invalid Usage\n";
//		return 0;
//	}
	program = nullptr;
//	yyin = fopen(argv[1],"r");;
	if(yyparse()){
		return 1;	
	}
	program->print();
	program->execute();
	delete program;
	std::cout<<"Nodes Left = "<<SNode::getCount()<<"\n";
	return 0;
}