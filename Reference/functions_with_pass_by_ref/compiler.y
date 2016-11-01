%{
	/*** Auxiliary declarations section ***/

#include <iostream>
#include <cmath>
#include <algorithm>
#include <set>
#include "syntaxTree.h"
#include "util.h"
#include <string>

	//
	//	External Variables 
	//	Declared in compiler.l
	extern FILE *yyin;								
	extern unsigned lineNumber;						
	extern unsigned colNumber;		
	
	//
	//	Function Declarations
	//
	int yylex();									
	void yyerror(const std::string &s) {			
		std::cout << "ERROR: "<<lineNumber<<","<<colNumber<<": "<<  s << "\n";
	}							

	
	SNode *program, *Scope[2] = {nullptr, nullptr};
	int Status;

%}

/*** YACC Declarations section ***/
%token ID NUM
%token READ WRITE
%token START END
%token IF THEN ELSE ENDIF
%token WHILE DO ENDWHILE
%token ISEQ NOTEQ LEQ GEQ
%token STARTDECL ENDDECL
%token INTEGER BOOLEAN
%token AND OR NOT
%token TRUE FALSE
%token FUNC RETURN

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
PROG:	// Complete Program
	DECLERATIONS FUNCTIONLIST	{
									program->setNext($2);
									for (symbolNode *i = $1->getTable();i;i=i->getNext())
										i->setAsGlobal();
									if($1){
										program->setTable($1->getTable());
										delete $1;
									}
									return 0;
								}
	;
FUNCTIONLIST:	// List of Function Definitions
	FUNCTIONDEF FUNCTIONLIST	{ $$ = $1; $1->setNext($2); }
	| FUNCTIONDEF				{ $$ = $1; }

FUNCTIONDEF:	// A function Definition
	FUNCTIONHEADER START SLIST RETSTMT END '}'	
								{											
									$$ = $1;
									$$->setPTR2($2);
									$4->setReturnType($$->getReturnType());
									$4->setTable($$->getTable());
									if($3==nullptr){
										$2->setNext($4);
									}
									else{
										$2->setNext($3);
										SNode *i;
										for(i=$3;i->getNext();i=i->getNext());
										i->setNext($4);
									}
									Scope[0] = nullptr;
									delete $5;
								}
FUNCTIONHEADER:	// includes Arguments and Local Declarations
	TYPE ID '(' ARGLIST ')' '{' DECLERATIONS
								{
									$$ = processFunctionHeader($1, $2, $4, $7, Scope[1]);
                                    if($$==nullptr){
										Status = FAIL;
										$$ = new SNode(FUNC, $2->getName(), $2->lineNo, $2->colNo);
										$$->setReturnType($1->getReturnType());
                                    }
                                    Scope[0] = $$;
                                    delete $1;
                                    delete $2;
                                    delete $4;
                                    delete $7;   
								}

DECLERATIONS:	// A block of declarations
	STARTDECL DLIST ENDDECL		{	
									symbolNode *Table = new symbolNode("&&&", -1);
                                    processDeclerations(Table, $2);
									delete $1;delete $2;delete $3;
									$$ = new SNode(-1, "&&&",$2->lineNo, $2->colNo);
									$$->setTable(Table);
									if(!Scope[1]){
										Scope[1] = $$;
										Scope[1]->getTable()->install("main", INTEGER, -2);
									}	
								}
	| /* Empty Declerations */	{
									$$=nullptr;
									if(!Scope[1]){
										SNode *temp = new SNode(-1, "&&&", -1, -1);
										temp->setTable(new symbolNode("&&&", -1));
										Scope[1] = temp;
										Scope[1]->getTable()->install("main", INTEGER, -2);
									}
								}
	;
DLIST:			// List of Declarations
	DECLARE DLIST				{$$ = $1; $1->setNext($2);}
	| DECLARE					{$$ = $1;}
	;

DECLARE:		// A single Declaration Statement
	TYPE MULDCL ';'				{$1->setPTR3($2); $$ = $1;}
	;

MULDCL:			// Variable list for a Declaration
	VARDCL ',' MULDCL			{$$ = $1; $1->setPTR3($3);}
	| VARDCL					{$$ = $1;}
	;
	
VARDCL:			// Declarations Possible
	ID '(' ARGLIST ')' 			{$$ = $1; $$->setPTR2($3);$$->setNodeType(FUNC);}
	| ID '[' NUM ']'			{$$ = $1; $$->setPTR2($3);}
	| ID						{$$ = $1;}
	;

ARGLIST:		// Formal Arguments
	ARGGROUP ';' ARGLIST		{$$ = $1; $1->setNext($3);}
	| ARGGROUP					{$$ = $1;}
	|	/* Empty Args */		{$$ = nullptr;}
	;

ARGGROUP:		// Group of Variables with same Return Type
	TYPE IDLIST					{$$ = $1; $$->setPTR3($2);}
	;
	
IDLIST:			// List of Variables
	'&' ID ',' IDLIST			{$$ = $2; $$->setReturnType('&'); $$->setNext($4);}
	| ID ',' IDLIST				{$$ = $1; $$->setNext($3);}
	| '&' ID					{$$ = $2; $$->setReturnType('&');}
	| ID						{$$ = $1;}

TYPE:			// Data Type
	INTEGER						{$$ = $1;}
	| BOOLEAN					{$$ = $1;}
	;

SLIST:			// Block of Statement
	STATEMENTS					{$$ = $1;}
	|	/* NULL STATEMENTS */	{$$ = nullptr;}

STATEMENTS:		// List of Statement
	STMT STATEMENTS				{$$ = $1; $1->setNext($2);}
	| STMT						{$$ = $1;}
	;
	
RETSTMT:		// Return Statement
    RETURN EXPR ';'				{$$=$1; $1->setPTR2($2);}
    ;

STMT:			// A single Statement
	IDENT '=' EXPR	';'			{$$ = $2; $$->setPTR1($1); $$->setPTR2($3);}
	| READ '(' IDENT ')' ';'	{$$ = $1; $$->setPTR2($3);}
	| WRITE '(' EXPR ')' ';'	{
									$$ = $1;
									$$->setPTR2($3);
								}
	| IF '(' EXPR ')' THEN SLIST ENDIF ';'
								{
									$$ = $1;
									$$->setPTR1($3);$$->setPTR2($6);
									delete $5;delete $7;
								}
	| IF '(' EXPR ')' THEN SLIST ELSE SLIST ENDIF ';'
								{
									$$ = $1;
									$$->setPTR1($3);$$->setPTR2($6);$$->setPTR3($8);
									delete $5;delete $7;	delete $9;
								}
	| WHILE '(' EXPR ')' DO SLIST ENDWHILE ';'
								{
									$$ = $1;
									$$->setPTR1($3);$$->setPTR2($6);
									delete $5;	delete $7;
								}
	;

EXPR:			// Expression
	EXPR '+' EXPR				{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setReturnType(INTEGER);}
	| EXPR '-' EXPR				{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setReturnType(INTEGER);}
	| EXPR '*' EXPR				{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setReturnType(INTEGER);}
	| EXPR '/' EXPR				{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setReturnType(INTEGER);}
	| EXPR '^' EXPR				{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setReturnType(INTEGER);}
	| EXPR '<' EXPR				{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setReturnType(BOOLEAN);}
	| EXPR '>' EXPR				{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setReturnType(BOOLEAN);}
	| EXPR LEQ EXPR				{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setReturnType(BOOLEAN);}
	| EXPR GEQ EXPR				{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setReturnType(BOOLEAN);}
	| EXPR ISEQ EXPR			{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setReturnType(BOOLEAN);}
	| EXPR NOTEQ EXPR			{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setReturnType(BOOLEAN);}
	| EXPR AND EXPR				{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setReturnType(BOOLEAN);}
	| EXPR OR EXPR				{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setReturnType(BOOLEAN);}
	| NOT EXPR					{$$ = $1; $$->setPTR1($2); $$->setReturnType(BOOLEAN);}
	| '(' EXPR ')'				{$$ = $2;}
	| TRUE						{$$ = $1; $$->setReturnType(BOOLEAN);}
	| FALSE						{$$ = $1; $$->setReturnType(BOOLEAN);}
	| NUM						{$$ = $1; $$->setReturnType(INTEGER);}
	| IDENT						{$$ = $1;}
	| ID '(' ACTARGLIST ')'		{
                                    $$ = variableAccess($1, $3, Scope, FUNCTION);
                                    if(!$$)
										Status = FAIL;
								}
	;

IDENT:			// Variable Access
	ID '[' EXPR ']'				{
                                    $$ = variableAccess($1, $3, Scope, ARRAY);
									if(!$$)
										Status = FAIL;
								}
	| ID						{
									$$ = variableAccess($1, nullptr, Scope, VARIABLE);
									if(!$$)
										Status = FAIL;
								}
	;
ACTARGLIST:		// ACTUAL ARGUMENTS
    EXPR ',' ACTARGLIST			{ $$ = $1; $$->setNext($3); }
    | EXPR						{ $$ = $1; }
    |	/*No arguments */		{ $$ = nullptr; }
%%

/*** Auxiliary functions section ***/

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
	if(yyparse() || std::min(Status,std::min(program->typeCheck(),checkFunctionDeclared(program)))<=WARN){
		delete program->getTable();
		delete program;
		std::cout << "SNodes Left = " << SNode::getCount() << "\n";
		std::cout << "symbolNodes Left = " << symbolNode::getCount() << "\n";
		return 1;
	}
	program->print();
	
	fprintf(output, "START\n");
	fprintf(output, "MOV BP, 2\n");
	fprintf(output, "MOV SP, 2\n");
	generateCode(program, output);
//	program->run();
	delete program->getTable();
	delete program;
	std::cout << "SNodes Left = " << SNode::getCount() << "\n";
	std::cout << "symbolNodes Left = " << symbolNode::getCount() << "\n";
	return 0;
}
