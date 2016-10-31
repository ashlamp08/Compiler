%{
	/*** Auxiliary declarations section ***/

#include <iostream>
#include <cmath>
#include <algorithm>
#include <set>
#include "syntaxTree.h"
#include "util.h"
#include <string>

	extern FILE *yyin;
	int yylex();											//	Declarations of Functions
	void yyerror (const std::string & s);					//

	extern unsigned lineNumber;
	extern unsigned colNumber;

	SNode *program, *Scope[2] = {nullptr, nullptr}, *Main;

	int currentType, Status;

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
%token FUNC
%token RETURN
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
	DECLERATIONS FUNCTIONLIST	{
										program->setNext($2);
										for (symbolNode *i = $1->getTable();i;i=i->getNext())
											i->setAsGlobal();
										deb;
										if($1){
											program->setTable($1->getTable());
											delete $1;
										}
										return 0;
								}
	;
FUNCTIONLIST:
	FUNCTIONDEF FUNCTIONLIST	{ $$ = $1; $1->setNext($2);deb; }
	| FUNCTIONDEF				{ $$ = $1;deb; }

FUNCTIONDEF:
	FUNCTIONHEADER START SLIST RETSTMT END '}'	{
											deb;
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
                                            deb;
                                            delete $5;
										}
FUNCTIONHEADER:
	TYPE ID '(' ARGLIST ')' '{' DECLERATIONS
								{
									deb;
									$$ = processFunctionHeader($1, $2, $4, $7, Scope[1]);
									deb;
                                    if($$==nullptr){
										Status = FAIL;
										$$ = new SNode(FUNC, $2->getName(), $2->lineNo, $2->colNo);
										$$->setReturnType($1->getReturnType());
                                    }
                                    deb;
                                    Scope[0] = $$;
                                    delete $1;
                                    delete $2;
                                    delete $4;
                                    delete $7;
                                    deb;
								}

DECLERATIONS:
	STARTDECL DLIST ENDDECL		{
									deb;
									symbolNode *Table = new symbolNode("&&&", -1);
                                    processDeclerations(Table, $2);
									delete $1;delete $2;delete $3;
									$$ = new SNode(-1, "&&&",$2->lineNo, $2->colNo);
									$$->setTable(Table);
									if(!Scope[1]){
										Scope[1] = $$;
										Scope[1]->getTable()->install("main", INTEGER, -2);
									}
									deb;
								}
	| /* Empty Declerations */		{$$=nullptr;}
	;
DLIST:
	DECLARE DLIST					{$$ = $1; $1->setNext($2);}
	| DECLARE						{$$ = $1;}
	;

DECLARE:
	TYPE MULDCL ';'					{$1->setPTR3($2); $$ = $1;}
	;

MULDCL:
	VARDCL ',' MULDCL				{$$ = $1; $1->setPTR3($3);}
	| VARDCL						{$$ = $1;}
	;
VARDCL:
	ID '(' ARGLIST ')' 				{$$ = $1; $$->setPTR2($3);$$->setNodeType(FUNC);}
	| ID '[' NUM ']'				{$$ = $1; $$->setPTR2($3);}
	| ID							{$$ = $1;}
	;

ARGLIST:
	ARGGROUP ';' ARGLIST			{$$ = $1; $1->setNext($3);}
	| ARGGROUP						{$$ = $1;}
	|	/* Empty Args */			{$$ = nullptr;}
	;

ARGGROUP:
	TYPE IDLIST						{$$ = $1; $$->setPTR3($2);}
	;
IDLIST:
	ID ',' IDLIST					{$$ = $1; $1->setNext($3);}
	| ID							{$$ = $1;}

TYPE:
	INTEGER							{$$ = $1;}
	| BOOLEAN						{$$ = $1;}
	;

SLIST:
	STATEMENTS						{$$ = $1;deb;}
	|	/* NULL STATEMENTS */		{$$ = nullptr;deb;}

RETSTMT:
    RETURN EXPR ';'					{$$=$1; $1->setPTR2($2);deb;}
    ;

STATEMENTS:
	STMT STATEMENTS					{deb;$$ = $1; $1->setNext($2);}
	| STMT							{deb;$$ = $1;}
	;
STMT:
	IDENT '=' EXPR	';'				{deb;$$ = $2; $$->setPTR1($1); $$->setPTR2($3);}
	| READ '(' IDENT ')' ';'		{deb;$$ = $1; $$->setPTR2($3);}
	| WRITE '(' EXPR ')' ';'		{deb;
										$$ = $1;
										$$->setPTR2($3);
									}
	| IF '(' EXPR ')' THEN SLIST ENDIF ';'
									{deb;
										$$ = $1;
										$$->setPTR1($3);$$->setPTR2($6);
										delete $5;delete $7;
									}
	| IF '(' EXPR ')' THEN SLIST ELSE SLIST ENDIF ';'
									{deb;
										$$ = $1;
										$$->setPTR1($3);$$->setPTR2($6);$$->setPTR3($8);
										delete $5;delete $7;	delete $9;
									}
	| WHILE '(' EXPR ')' DO SLIST ENDWHILE ';'
									{deb;
										$$ = $1;
										$$->setPTR1($3);$$->setPTR2($6);
										delete $5;	delete $7;
									}
	;

EXPR:
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

IDENT:
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
ACTARGLIST:
    EXPR ',' ACTARGLIST			{ $$ = $1; $$->setNext($3); }
    | EXPR						{ $$ = $1; }
    |	/*No arguments */		{ $$ = nullptr; }
%%

/*** Auxiliary functions section ***/

void yyerror(const std::string &s) {
	std::cout << "ERROR: "<<lineNumber<<","<<colNumber<<": "<<  s << "\n";
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
	if(yyparse() || std::min(Status,program->typeCheck())<=WARN){
		return 1;
	}
	program->print();
	fprintf(output, "START\n");
	fprintf(output, "MOV BP, 2\n");
	fprintf(output, "MOV SP, 2\n");
	generateCode(program, output);
//	program->run();
	delete program;
	delete program->getTable();
	std::cout << "SNodes Left = " << SNode::getCount() << "\n";
	std::cout << "symbolNodes Left = " << symbolNode::getCount() << "\n";
	return 0;
}
