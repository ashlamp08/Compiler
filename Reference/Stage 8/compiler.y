%{
	/*** Auxiliary declarations section ***/

#include <iostream>
#include <cmath>
#include "syntaxTree.h"
#include <string>

extern FILE *yyin;
int yylex();					//	Declarations of Functions
void yyerror (const std::string &s);	//

extern unsigned lineNumber;
extern unsigned colNumber;

SNode * program, *globalDecl, *Main, *currentScope;

int currentType;

bool checkArguments(SNode *oper, SNode *X, SNode *Y);
bool assignExpression(SNode *&dest, SNode *X, SNode *oper, SNode *Y);

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
%token ELSE
%token ENDIF
%token WHILE
%token DO
%token ENDWHILE
%token ISEQ
%token NOTEQ
%token LEQ
%token GEQ
%token STARTDECL
%token ENDDECL
%token INTEGER
%token BOOLEAN
%token AND
%token OR
%token NOT
%token TRUE
%token FALSE
%nonassoc NOTEQ
%nonassoc ISEQ
%nonassoc LEQ
%nonassoc GEQ
%nonassoc '<'
%nonassoc '>'
%left '+' '-'
%left '*' '/'
%right '^'
%left NOT
%left AND
%left OR
%%

/*** Rules Section ***/
PROG:	DECLERATIONS START SLIST END	{
											program->setNext($3);
											program->setTable($1->getTable());
											std::cout << "Program Complete\n";
											delete $1;
											delete $2;
											delete $4;
											return 0;
										}
		| START SLIST END				{
											program->setNext($2);
											std::cout << "Program Complete\n";
											delete $1;
											delete $3;
											return 0;
										}
		;
DECLERATIONS:	STARTDECL DLIST ENDDECL	{
											symbolNode *Table = new symbolNode("&&&", -1);
											for (SNode *head = $2; head != nullptr; head = head->getNext() ){
												for (SNode *i = head->getPTR3(); i != nullptr; i = i->getPTR3() ){
													symbolNode *position;
													if(i->getPTR2())
														position = Table->install(i->getName(), head->getNodeType(), i->getPTR2()->getValue());
													else
														position = Table->install(i->getName(), head->getNodeType());
													if (position == nullptr) {
														yyerror("'"+i->getName()+"' is already declared");
														return 1;
													}
												}
											}
											delete $1;
											delete $2;
											delete $3;
											SNode *temp = new SNode(-1,"&&&");
											temp->setTable(Table);
											currentScope = $$ = temp;
										}
DLIST:			DECLARE DLIST 			{$$=$1;$1->setNext($2);}
				| DECLARE				{$$=$1;}

DECLARE:	TYPE MULDCL ';'	{$1->setPTR3($2);$$=$1;}
			;

MULDCL:	VARDCL ',' MULDCL 			{$$ = $1; $1->setPTR3($3);deb;}
		| VARDCL					{$$ = $1;deb;}
		;
VARDCL: ID '[' NUM ']'				{$$ = $1; $$->setPTR2($3);}
		| ID						{$$ = $1;}
		;

TYPE:	INTEGER						{$$ = $1;}
		| BOOLEAN					{$$ = $1;}
		;

SLIST:	STMT SLIST 					{$$=$1;$1->setNext($2);deb;}
		| STMT						{$$=$1;deb;}
		;
STMT:	IDENT '=' EXPR	';'			{$$ = $2; $$->setPTR1($1); $$->setPTR2($3);}
		| READ '(' IDENT ')' ';' 	{$$ = $1; $$->setPTR2($3);}
		| WRITE '(' EXPR ')' ';' 	{$$ = $1; $$->setPTR2($3);deb;if($3->getType()!=INTEGER){yyerror("Can print Integers only");return 1;}}
		| IF '(' EXPR ')' THEN SLIST ENDIF ';'
									{
										if($3->getType()!=BOOLEAN){
											yyerror("Expected a boolean Expression as the Condition");
											return 1;
										}
										$$ = $1;
										$$->setPTR1($3);
										$$->setPTR2($6);
										delete $5;
										delete $7;
									}
		| IF '(' EXPR ')' THEN SLIST ELSE SLIST ENDIF ';'
									{
										if($3->getType()!=BOOLEAN){
											yyerror("Expected a boolean Expression as the Condition");
											return 1;
										}
										$$ = $1;
										$$->setPTR1($3);
										$$->setPTR2($6);
										$$->setPTR3($8);
										delete $5;
										delete $7;
										delete $9;
									}
		| WHILE '(' EXPR ')' DO SLIST ENDWHILE ';'
									{
										if($3->getType()!=BOOLEAN){
											yyerror("Expected a boolean Expression as the Condition");
											return 1;
										}
										$$ = $1;
										$$->setPTR1($3);
										$$->setPTR2($6);
										delete $5;
										delete $7;
									}
		;

EXPR:	  EXPR '+' EXPR				{if(!assignExpression($$,$1,$2,$3))	return 1;$$->setType(INTEGER);}
		| EXPR '-' EXPR				{if(!assignExpression($$,$1,$2,$3))	return 1;$$->setType(INTEGER);}
		| EXPR '*' EXPR				{if(!assignExpression($$,$1,$2,$3))	return 1;$$->setType(INTEGER);}
		| EXPR '/' EXPR				{if(!assignExpression($$,$1,$2,$3))	return 1;$$->setType(INTEGER);}
		| EXPR '^' EXPR				{if(!assignExpression($$,$1,$2,$3))	return 1;$$->setType(INTEGER);}
		| EXPR '<' EXPR				{if(!assignExpression($$,$1,$2,$3))	return 1;$$->setType(BOOLEAN);}
		| EXPR '>' EXPR				{if(!assignExpression($$,$1,$2,$3))	return 1;$$->setType(BOOLEAN);}
		| EXPR LEQ EXPR				{if(!assignExpression($$,$1,$2,$3))	return 1;$$->setType(BOOLEAN);}
		| EXPR GEQ EXPR				{if(!assignExpression($$,$1,$2,$3))	return 1;$$->setType(BOOLEAN);}
		| EXPR ISEQ EXPR			{if(!assignExpression($$,$1,$2,$3))	return 1;$$->setType(BOOLEAN);}
		| EXPR NOTEQ EXPR			{if(!assignExpression($$,$1,$2,$3))	return 1;$$->setType(BOOLEAN);}
		| EXPR AND EXPR				{if(!assignExpression($$,$1,$2,$3))	return 1;$$->setType(BOOLEAN);}
		| EXPR OR EXPR				{if(!assignExpression($$,$1,$2,$3))	return 1;$$->setType(BOOLEAN);}
		| NOT EXPR					{if(!assignExpression($$,$1,$2,nullptr))return 1;$$->setType(BOOLEAN);}
		| '(' EXPR ')'				{$$ = $2;}
		| TRUE						{$$ = $1;$$->setType(BOOLEAN);}
		| FALSE						{$$ = $1;$$->setType(BOOLEAN);}
		| NUM						{$$ = $1;$$->setType(INTEGER);}
		| IDENT						{$$ = $1;deb;}
		;
IDENT:	ID '[' EXPR ']'				{
										if($3->getType()!=INTEGER){yyerror("Index can be Integer only");return 1;}
										symbolNode *Table = currentScope->getTable(), *temp;
										temp = Table->lookUp($1->getName());
										if(temp==nullptr){
											yyerror("'"+$1->getName()+"' not Declared");
											return 1;
										}
										else if(temp->getSize()==-1){
											yyerror("'"+$1->getName()+" used as Array but declared as Variable");
											return 1;
										}
										else{
											$1->setEntry(temp);
											$$=$1;
											$$->setPTR1($3);
											$$->setType(temp->getType());
										}
									}
		| ID						{
										symbolNode *Table = currentScope->getTable(), *temp;
										temp = Table->lookUp($1->getName());
										if(temp==nullptr){
											yyerror("'"+$1->getName()+"' not Declared");
											return 1;
										}
										else if(temp->getSize()!=-1){
											yyerror("'"+$1->getName()+"' used as Variable but declared as Array");
											return 1;
										}
										else{
											$1->setEntry(temp);
											$$=$1;
											$$->setType(temp->getType());
										}
										deb;
									}
		;
%%

/*** Auxiliary functions section ***/

void yyerror(const std::string &s) {
	std::cout << "YYERROR: " << lineNumber<<":"<<colNumber<<":\t"<<s<<"\n";
}

bool checkArguments(SNode *oper, SNode *X, SNode *Y) {
	switch (oper->getNodeType()) {
		case '+':
		case '-':
		case '*':
		case '/':
		case '^':
		case '<':
		case '>':
		case LEQ:
		case GEQ:
			if (X->getType() == BOOLEAN){
				yyerror("'"+X->getName()+"' is of type Boolean, needed Integer");
				return false;
			}
			if(Y->getType() == BOOLEAN){
				yyerror("'"+Y->getName()+"' is of type Boolean, needed Integer");
				return false;
			}
			return true;
		case ISEQ:
		case NOTEQ:
			if (X->getType() == INTEGER && Y->getType() == BOOLEAN){
				yyerror("'"+Y->getName()+"' is of type Boolean, needed Integer");
				return false;
			}
			if (X->getType() == BOOLEAN && Y->getType() == INTEGER){
				yyerror("'"+Y->getName()+"' is of type Integer, needed Boolean");
				return false;
			}
			return true;
		case AND:
		case OR:
			if (X->getType() == INTEGER){
				yyerror("'"+X->getName()+"' is of type Integer, needed Boolean");
				return false;
			}
			if (Y->getType() == INTEGER){
				yyerror("'"+Y->getName()+"' is of type Integer, needed Boolean");
				return false;
			}
			return true;
		case NOT:
			if (X->getType() == INTEGER && Y==nullptr){
				yyerror("'"+X->getName()+"' is of type Integer, needed Boolean");
				return false;
			}
			return true;
	}
	return false;
}
bool assignExpression(SNode *&dest, SNode *X, SNode *oper, SNode *Y){
	if(checkArguments(oper,X,Y)){
		dest = oper;
		dest->setPTR1(X);
		dest->setPTR2(Y);
		return true;
	}
	return false;
}
int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cout << "Reading from STD Input\n";
	}
	else{
		yyin = fopen(argv[1], "r");
		if(!yyin){
			std::cout << "'"<<argv[1]<<"' does not exists.\n";
			return 1;
		}
		std::cout << "Reading Code from '"<<argv[1]<<"'\n";
	}
	program = new SNode(START);
	currentScope = program;
	if (yyparse()) {
		return 1;
	}
	program->print();
	program->run();
	delete program->getTable();
	delete program;
	std::cout << "SNodes Left = " << SNode::getCount() << "\n";
	std::cout << "symbolNodes Left = " << symbolNode::getCount() << "\n";
	return 0;
}
