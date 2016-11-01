%{
	/*** Auxiliary declarations section ***/

#include <iostream>
#include <cmath>
#include <algorithm>
#include "syntaxTree.h"
#include <string>

	extern FILE *yyin;
	int yylex();					//	Declarations of Functions
	void yyerror (const std::string & s);	//

	extern unsigned lineNumber;
	extern unsigned colNumber;

	extern void error (const std::string &s, int l, int c);
		
	SNode * program, *globalDecl, *Main, *currentScope;

	int currentType, Status;
	
	bool checkArguments(SNode * oper, SNode * X, SNode * Y);
	bool assignExpression(SNode *&dest, SNode * X, SNode * oper, SNode * Y);

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
PROG:
	DECLERATIONS START SLIST END	{
										program->setNext($3);
										program->setTable($1->getTable());
										delete $1;
										delete $2;
										delete $4;
										return 0;
									}
	| START SLIST END				{
										program->setNext($2);
										delete $1;
										delete $3;
										return 0;
									}
	;

DECLERATIONS:
	STARTDECL DLIST ENDDECL			{
										symbolNode *Table = new symbolNode("&&&", -1);
										for (SNode *head = $2; head != nullptr; head = head->getNext() ) {
											for (SNode *i = head->getPTR3(); i != nullptr; i = i->getPTR3() ) {
												symbolNode *position;
												if (i->getPTR2())
													position = Table->install(i->getName(), head->getNodeType(), i->getPTR2()->getValue());
												else
													position = Table->install(i->getName(), head->getNodeType());
												if (position == nullptr) {
													error("'" + i->getName() + "' is already declared",i->lineNo,i->colNo);
													Status = FAIL;
												}
											}
										}
										delete $1;
										delete $2;
										delete $3;
										SNode *temp = new SNode(-1, "&&&", -1, -1);
										temp->setTable(Table);
										currentScope = $$ = temp;
									}
	;
DLIST:
	DECLARE DLIST					{$$ = $1; $1->setNext($2);}
	| DECLARE						{$$ = $1;}
	;

DECLARE:
	TYPE MULDCL ';'					{$1->setPTR3($2); $$ = $1;}
	;

MULDCL:
	VARDCL ',' MULDCL				{$$ = $1; $1->setPTR3($3); deb;}
	| VARDCL						{$$ = $1; deb;}
	;
VARDCL:
	ID '[' NUM ']'					{$$ = $1; $$->setPTR2($3);}
	| ID							{$$ = $1;}
	;

TYPE:
	INTEGER							{$$ = $1;}
	| BOOLEAN						{$$ = $1;}
	;

SLIST:
	STMT SLIST						{$$ = $1; $1->setNext($2); deb;}
	| STMT							{$$ = $1; deb;}
	;
STMT:
	IDENT '=' EXPR	';'				{$$ = $2; $$->setPTR1($1); $$->setPTR2($3);}
	| READ '(' IDENT ')' ';'		{$$ = $1; $$->setPTR2($3);}
	| WRITE '(' EXPR ')' ';'		{	
										$$ = $1;
										$$->setPTR2($3);
										deb;
									}
	| IF '(' EXPR ')' THEN SLIST ENDIF ';' 
									{
										$$ = $1;
										$$->setPTR1($3);
										$$->setPTR2($6);
										delete $5;
										delete $7;
									}
	| IF '(' EXPR ')' THEN SLIST ELSE SLIST ENDIF ';' 
									{
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
										$$ = $1;
										$$->setPTR1($3);
										$$->setPTR2($6);
										delete $5;
										delete $7;
									}
	;

EXPR:
	EXPR '+' EXPR				{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setType(INTEGER);}
	| EXPR '-' EXPR				{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setType(INTEGER);}
	| EXPR '*' EXPR				{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setType(INTEGER);}
	| EXPR '/' EXPR				{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setType(INTEGER);}
	| EXPR '^' EXPR				{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setType(INTEGER);}
	| EXPR '<' EXPR				{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setType(BOOLEAN);}
	| EXPR '>' EXPR				{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setType(BOOLEAN);}
	| EXPR LEQ EXPR				{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setType(BOOLEAN);}
	| EXPR GEQ EXPR				{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setType(BOOLEAN);}
	| EXPR ISEQ EXPR			{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setType(BOOLEAN);}
	| EXPR NOTEQ EXPR			{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setType(BOOLEAN);}
	| EXPR AND EXPR				{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setType(BOOLEAN);}
	| EXPR OR EXPR				{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setType(BOOLEAN);}
	| NOT EXPR					{$$ = $1; $$->setPTR1($2); $$->setType(BOOLEAN);}
	| '(' EXPR ')'				{$$ = $2;}
	| TRUE						{$$ = $1; $$->setType(BOOLEAN);}
	| FALSE						{$$ = $1; $$->setType(BOOLEAN);}
	| NUM						{$$ = $1; $$->setType(INTEGER);}
	| IDENT						{$$ = $1; deb;}
	;

IDENT:
	ID '[' EXPR ']'				{
									symbolNode *Table = currentScope->getTable(), *temp;
									temp = Table->lookUp($1->getName());
									if (temp == nullptr) {
										error("'" + $1->getName() + "' not Declared", $1->lineNo, $1->colNo);
										Status = FAIL;
									}
									else if (temp->getSize() == -1) {
										error("'" + $1->getName() + " used as Array but declared as Variable",$1->lineNo, $1->colNo);
										Status = FAIL;
									}
									else{
										$1->setEntry(temp);
										$$ = $1;
										$$->setPTR1($3);
										$$->setType(temp->getType());
									}
								}
	| ID						{
									symbolNode *Table = currentScope->getTable(), *temp;
									temp = Table->lookUp($1->getName());
									if (temp == nullptr) {
										error("'" + $1->getName() + "' not Declared",$1->lineNo, $1->colNo);
										Status = FAIL;
									}
									else if (temp->getSize() != -1) {
										error("'" + $1->getName() + "' used as Variable but declared as Array",$1->lineNo, $1->colNo);
										Status = FAIL;
									}
									else{
										$1->setEntry(temp);
										$$ = $1;
										$$->setType(temp->getType());
									}
									deb;
								}
	;
%%

/*** Auxiliary functions section ***/

void yyerror(const std::string &s) {
	std::cout << "ERROR: "<<lineNumber<<","<<colNumber<<": "<<  s << "\n";
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
			if (X->getType() == BOOLEAN) {
				yyerror("'" + X->getName() + "' is of type Boolean, needed Integer");
				return false;
			}
			if (Y->getType() == BOOLEAN) {
				yyerror("'" + Y->getName() + "' is of type Boolean, needed Integer");
				return false;
			}
			return true;
		case ISEQ:
		case NOTEQ:
			if (X->getType() == INTEGER && Y->getType() == BOOLEAN) {
				yyerror("'" + Y->getName() + "' is of type Boolean, needed Integer");
				return false;
			}
			if (X->getType() == BOOLEAN && Y->getType() == INTEGER) {
				yyerror("'" + Y->getName() + "' is of type Integer, needed Boolean");
				return false;
			}
			return true;
		case AND:
		case OR:
			if (X->getType() == INTEGER) {
				yyerror("'" + X->getName() + "' is of type Integer, needed Boolean");
				return false;
			}
			if (Y->getType() == INTEGER) {
				yyerror("'" + Y->getName() + "' is of type Integer, needed Boolean");
				return false;
			}
			return true;
		case NOT:
			if (X->getType() == INTEGER && Y == nullptr) {
				yyerror("'" + X->getName() + "' is of type Integer, needed Boolean");
				return false;
			}
			return true;
	}
	return false;
}
bool assignExpression(SNode *&dest, SNode *X, SNode *oper, SNode *Y) {
	if (checkArguments(oper, X, Y)) {
		dest = oper;
		dest->setPTR1(X);
		dest->setPTR2(Y);
		return true;
	}
	return false;
}
int main(int argc, char *argv[]) {
	Status = PASS;
	if (argc != 2 && argc != 3) {
		std::cout << "Error: no input files\n";
		std::cout << "Usage: \tcompiler.exe <input_file> \n\tcompiler.exe <input_file> <output_file>\n";
		return 1;
	}
	else {
		yyin = fopen(argv[1], "r");
		if (!yyin) {
			std::cout << "'" << argv[1] << "' does not exists.\n";
			return 1;
		}
	}
	FILE *output;
	if(argc == 3)
		output = fopen(argv[2], "wb");
	else
		output = fopen("a.sil", "wb");
	if(!output){
		std::cout << "Cant write to file 'test.sil'\n";
		return 1;
	}
	program = new SNode(START,-1,-1);
	currentScope = program;
	if(yyparse() || std::min(Status,program->typeCheck())<=WARN){
		delete program->getTable();
		delete program;
		std::cout << "SNodes Left = " << SNode::getCount() << "\n";
		std::cout << "symbolNodes Left = " << symbolNode::getCount() << "\n";
		return 1;
	}
	program->print();
	program->codeGen(output);
	fprintf(output,"HALT\n");
//	program->run();
	delete program->getTable();
	delete program;
	std::cout << "SNodes Left = " << SNode::getCount() << "\n";
	std::cout << "symbolNodes Left = " << symbolNode::getCount() << "\n";
	return 0;
}
