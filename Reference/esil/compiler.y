%{
	/*** Auxiliary declarations section ***/

#include <iostream>
#include <cmath>
#include <algorithm>
#include <set>
#include "syntaxTree.h"
#include "typeTable.h"
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
	
	//
	//	Type Table declaration
	//	INTEGER, BOOLEAN are cached in integer, boolean to avoid searching again
	//	_error helps in error Checking by providing a value for comparison
	//	reference signifies that an argument is to be passed by reference
	//
	typeNode *typeTable, *integer, *boolean, *reference, *_error, *last=nullptr;
	
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
%token TYPEDEF

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
//									typeTable->print();
									return 0;
								}
	| TYPEDEFLIST DECLERATIONS FUNCTIONLIST					
								{
									program->setNext($3);
									for (symbolNode *i = $2->getTable();i;i=i->getNext())
										i->setAsGlobal();
									if($2){
										program->setTable($2->getTable());
										delete $2;
									}
				//					typeTable->print();
									delete $1;
									return 0;
								}
	;
TYPEDEFLIST:
	TYPEDEFITEM TYPEDEFLIST		{
									$$ = $1;
									$$->setNext($2);
								}
	| TYPEDEFITEM					{ $$ = $1; }
	;
	
TYPEDEFITEM:
	TYPEDEFHEAD '{' DLIST '}'	{
									SNode *definintionList = $3;
									typeNode *structure = nullptr;
									symbolNode *tempTable = new symbolNode("&&&", nullptr);
                                    if(!definintionList || !processDeclerations(tempTable, definintionList)){
										return 1;
									}
									int count = 0;
									for (symbolNode *i = tempTable->getNext(); i != nullptr; i = i->getNext()){
										if(i->getSize()>=0){
											error("No Array declarations allowed",definintionList->lineNo, definintionList->colNo);
											return 1;
										}
										if(i->getSize()==-2){
											error("No Function declarations allowed (yet)",definintionList->lineNo, definintionList->colNo);
											return 1;
										}
										if(count == 9){
											error("Currently only 8 data members allowed",definintionList->lineNo, definintionList->colNo);
											return 1;
										}
										typeNode *next = new typeNode(i->getName());
										next->setEntry(i->getType());
										next->setNext(structure);
										next->setIndex(count);
										structure = next;

										count++;
									}
									delete tempTable;
									delete definintionList;
									last->setEntry(structure);
									$1->setPTR1($2);
									$1->setPTR2($4);
									$$ = $1;
								}
	;
TYPEDEFHEAD:
	TYPEDEF ID 					{
									if(typeTable->lookUp($2->getName())){
										error("'"+$2->getName()+"' already Declared. Redefining not Allowed.",$2->lineNo, $2->colNo);
										return 1;
									}
									last = typeTable->install($2->getName(), last);
									$$ = $2;
									delete $1;
								}
	;
FUNCTIONLIST:	// List of Function Definitions
	FUNCTIONDEF FUNCTIONLIST	{ $$ = $1; $1->setNext($2); }
	| FUNCTIONDEF				{ $$ = $1; }
	;

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
	;
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
	;

DECLERATIONS:	// A block of declarations
	STARTDECL DLIST ENDDECL		{
									symbolNode *Table = new symbolNode("&&&", nullptr);
                                    processDeclerations(Table, $2);
									delete $1;delete $2;delete $3;
									$$ = new SNode(-1, "&&&",$2->lineNo, $2->colNo);
									$$->setTable(Table);
									if(!Scope[1]){
										// deb;
										Scope[1] = $$;
										Scope[1]->getTable()->install("main", integer, -2);
										Scope[1]->getTable()->install("initialize", integer, -2);
										Scope[1]->getTable()->install("allocate", nullptr, -2);
										Table = Scope[1]->getTable()->install("free", integer, -2);
										std::vector<symbolNode *> arglist;
										arglist.push_back(new symbolNode("addr", nullptr));
										arglist.back()->setAsPassByReference();
										// val(Table);
										Table->setArgs(arglist);
									}	
								}
	| /* Empty Declerations */	{
									$$=nullptr;
									if(!Scope[1]){
										SNode *temp = new SNode(-1, "&&&", -1, -1);
										temp->setTable(new symbolNode("&&&", nullptr));
										$$ = Scope[1] = temp;
										Scope[1]->getTable()->install("main", integer, -2);
										Scope[1]->getTable()->install("initialize", integer, -2);
										Scope[1]->getTable()->install("allocate", nullptr, -2);
										symbolNode *Table = Scope[1]->getTable()->install("free", integer, -2);
										std::vector<symbolNode *> arglist;
										arglist.push_back(new symbolNode("addr", nullptr));
										arglist.back()->setAsPassByReference();
										Table->setArgs(arglist);
									}
								}
	;
DLIST:			// List of Declarations
	DECLARE DLIST				{$$ = $1; $1->setNext($2);}
	| DECLARE					{$$ = $1;}
	;

DECLARE:		// A single Declaration Statement
	TYPE MULDCL ';'			{$1->setPTR3($2); $$ = $1;}
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
	'&' ID ',' IDLIST			{$$ = $2; $$->setReturnType(reference); $$->setNext($4);}
	| ID ',' IDLIST				{$$ = $1; $$->setNext($3);}
	| '&' ID					{$$ = $2; $$->setReturnType(reference);}
	| ID						{$$ = $1;}

TYPE:			// Data Type
	INTEGER						{$$ = $1;$$->setReturnType(integer);}
	| BOOLEAN					{$$ = $1;$$->setReturnType(boolean);}
	| ID						{
									typeNode *temp = typeTable->lookUp($1->getName());
									if(!temp){
										error("No Data Type '"+$1->getName()+"'", $1->lineNo, $1->colNo);
										return 1;
									}
									$$ = $1;
									$$->setReturnType(temp);
								}
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
	EXPR '+' EXPR				{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setReturnType(integer);}
	| EXPR '-' EXPR				{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setReturnType(integer);}
	| EXPR '*' EXPR				{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setReturnType(integer);}
	| EXPR '/' EXPR				{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setReturnType(integer);}
	| EXPR '^' EXPR				{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setReturnType(integer);}
	| EXPR '<' EXPR				{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setReturnType(boolean);}
	| EXPR '>' EXPR				{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setReturnType(boolean);}
	| EXPR LEQ EXPR				{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setReturnType(boolean);}
	| EXPR GEQ EXPR				{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setReturnType(boolean);}
	| EXPR ISEQ EXPR			{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setReturnType(boolean);}
	| EXPR NOTEQ EXPR			{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setReturnType(boolean);}
	| EXPR AND EXPR				{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setReturnType(boolean);}
	| EXPR OR EXPR				{$$ = $2; $$->setPTR1($1); $$->setPTR2($3); $$->setReturnType(boolean);}
	| NOT EXPR					{$$ = $1; $$->setPTR1($2); $$->setReturnType(boolean);}
	| '(' EXPR ')'				{$$ = $2;}
	| TRUE						{$$ = $1; $$->setReturnType(boolean);}
	| FALSE						{$$ = $1; $$->setReturnType(boolean);}
	| NUM						{$$ = $1; $$->setReturnType(integer);}
	| IDENT						{$$ = $1;}
	| ID '(' ACTARGLIST ')'		{
                                    $$ = variableAccess($1, $3, Scope, FUNCTION);
									if(!$$){
										Status = FAIL;
										$$ = $1;
										$1->setReturnType(_error);
                                    }
								}
	;
IDENT:			// Variable Access
	ID '[' EXPR ']' '.' IDENTLIST	
								{
									$1->setPTR2($6);
									$$ = variableAccess($1, $3, Scope, ARRAY);
									if(!$$){
										Status = FAIL;
										$$ = $1;
										$1->setReturnType(_error);
                                    }
								}
	| ID '[' EXPR ']'			{
                                    $$ = variableAccess($1, $3, Scope, ARRAY);
									if(!$$){
										Status = FAIL;
										$$ = $1;
										$1->setReturnType(_error);
                                    }
								}
	| IDENTLIST					{
									$$ = variableAccess($1, nullptr, Scope, VARIABLE);
									if(!$$){
										Status = FAIL;
										$$ = $1;
										$1->setReturnType(_error);
                                    }
								}
	;
IDENTLIST:
	ID '.' IDENTLIST			{ $$ = $1; $$->setPTR2($3);}
	| ID						{ $$ = $1; }
	;
ACTARGLIST:		// ACTUAL ARGUMENTS
    EXPR ',' ACTARGLIST			{ $$ = $1; $$->setNext($3); }
    | EXPR						{ $$ = $1; }
    |	/*No arguments */		{ $$ = nullptr; }
	;
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
	typeTable = new typeNode("&&&");
//	val(typeTable);
	_error = typeTable->install("_ERROR", nullptr);
	integer = typeTable->install("integer", nullptr);
	boolean = typeTable->install("boolean", nullptr);
	reference = new typeNode("&");
	if(yyparse()){
		Status = FAIL;
	} 
	typeTable->print();
	program->print();
	Status = std::min(Status, program->typeCheck());
	Status = std::min(Status, checkFunctionDeclared(program));
	if(Status<=WARN){
		delete program->getTable();
		delete program;
		std::cout << "SNodes Left = " << SNode::getCount() << "\n";
		std::cout << "symbolNodes Left = " << symbolNode::getCount() << "\n";
		return 1;
	}
//	val(Status);
	
	// typeTable->print();
	// program->print();
	generateCode(program, output);
	addLibrary(output);
	
	delete program->getTable();
	delete program;
	std::cout << "SNodes Left = " << SNode::getCount() << "\n";
	std::cout << "symbolNodes Left = " << symbolNode::getCount() << "\n";
	return 0;
}
