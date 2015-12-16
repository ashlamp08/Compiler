%{
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include<stdbool.h>
	#include "symbol_table.h"

	#define YYSTYPE char*

	struct symbol stable[100];
	int id_count = 0; 

	#define INT 1;
	#define BOOL 0;
%}

%token ID
%token BEG
%token END
%token DECL
%token ENDDECL
%token IF
%token THEN
%token ELSE
%token ENDIF
%token WHILE
%token DO
%token ENDWHILE
%token READ
%token WRITE
%token AND
%token OR
%token NOT
%token LEQ
%token GEQ
%token LTHAN
%token GTHAN
%token INTEGER
%token BOOLEAN
%left EQEQ NEQ AND OR LEQ GEQ LTHAN GTHAN
%left NOT
%left '+' '-'
%left '*' '/'
%left '(' ')'

%%

program 	:declaration body	{printf("\nComplete\n");exit(1);}	
		; 

declaration 	:DECL dlist ENDDECL	{}
		;

dlist		:dstmt dlist 		{}
		|dstmt			{}
		;

dstmt		:INTEGER ID ';'	{strcpy(stable[id_count].name, $2);
					stable[id_count].datatype = INT;
					stable[id_count].size = 1;
					stable[id_count].store.int_store = 0;
					id_count++;}
		|BOOLEAN ID ';'	{strcpy(stable[id_count].name, $2);
					stable[id_count].datatype = BOOL;
					stable[id_count].size = 1;
					stable[id_count].store.bool_store = false;
					id_count++;}
		;


body		:BEG stmtlist END 	{}
		;

stmtlist	:stmt stmtlist		{}
		|stmt			{}
		;

stmt		:assignment		{}
		|condition		{}
		|loop			{}
		;

expr		:expr '+' expr		{}
		|expr '-' expr		{}
		|expr '/' expr		{}	
		|expr '*' expr		{}
		|expr EQEQ expr		{}
		|expr NEQ expr		{}
		|expr AND expr		{}
		|expr OR expr		{}
		|NOT expr 		{}		
		|'(' expr ')'		{}
		|ID			{}
		;

assignment	:ID '=' expr ';'	{}
		;

condition	:IF expr THEN stmtlist ENDIF ';'		{}
		|IF expr THEN stmtlist ELSE stmtlist ENDIF ';'	{}
		;

loop		:WHILE expr DO stmtlist ENDWHILE ';'		{}
		;

%%
    
yyerror()
{
    printf("\nError here\n");
}

main()
{
    yyparse();
    return 1;
}












