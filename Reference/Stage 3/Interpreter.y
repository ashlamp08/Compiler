%{
	/*** Auxiliary declarations section ***/

#include <iostream>
#include <cmath>
#include "syntaxTree.h"
#include <string>
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

STMT:	ID '=' EXPR	';'			{$$=$2;$1->setUsed($1->getValue());$$->setPTR1($1);$$->setPTR2($3);}
		| READ '(' ID ')' ';' 	{$$=$1;$3->setUsed($1->getValue());$$->setPTR2($3);}
		| WRITE '(' EXPR ')' ';'{$$=$1;$$->setPTR2($3);}
		;

EXPR:	EXPR '+' EXPR			{$$=$2;$$->setPTR1($1);$$->setPTR2($3);}
	    | '-' EXPR				{$$=$1;$$->setPTR1(new SNode(NUM,0));$$->setPTR2($2);}
	    | EXPR '-' EXPR			{$$=$2;$$->setPTR1($1);$$->setPTR2($3);}
	    | EXPR '*' EXPR			{$$=$2;$$->setPTR1($1);$$->setPTR2($3);}
	    | EXPR '/' EXPR			{$$=$2;$$->setPTR1($1);$$->setPTR2($3);}
	    | EXPR '^' EXPR			{$$=$2;$$->setPTR1($1);$$->setPTR2($3);}
	    | '(' EXPR ')'			{$$=$2;}
	    | NUM					{$$=$1;}
	    | ID					{if(!$1->getUsed($1->getValue())){std::cout<<"'"<<(char)('a' + $1->getValue())<<"' not initialized\n";return 1;}$$=$1;}
	    ;		

%%

/*** Auxiliary functions section ***/

void yyerror(char const *s) {
	std::cout<<"YYERROR::"<<s;
}

int main() {
	std::ios_base::sync_with_stdio(true);
	program = nullptr;
	printHex(std::cin.peek());
	if(yyparse()){
		return 1;
	}
	//program->print();	
	printHex(std::cin.peek());
	program->execute();
	delete program;
	std::cout<<"Nodes Left = "<<SNode::getCount()<<"\n";
	return 0;
}