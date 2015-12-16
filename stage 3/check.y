%{
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include<stdbool.h>
	#include<malloc.h>
	#include "symbol_table_check.h"

	symbol* stable[100];
	int id_count = 0; 
	int find_id(symbol*,int);

	#define INT 1
	#define BOOL 0
%}

%token BOOLE
%token NUM
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
%left LEQ GEQ LTHAN GTHAN
%left EQEQ NEQ 
%left AND 
%left OR
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

dstmt		:INTEGER ID ';'			{stable[id_count] = $2;
						stable[id_count]->datatype = INT;
						stable[id_count]->size = 0;
						stable[id_count]->store.int_store = (int *)malloc(sizeof(int));
						*(stable[id_count]->store.int_store) = 0;
						id_count++;}

		|BOOLEAN ID ';'			{stable[id_count] = $2;
						stable[id_count]->datatype = BOOL;
						stable[id_count]->size = 0;
						stable[id_count]->store.bool_store = (bool *)malloc(sizeof(bool));
						*(stable[id_count]->store.bool_store) = false;
						id_count++;}

		|INTEGER ID '[' expr ']' ';'	{if($4->datatype!=INT)
							yyerror();
						stable[id_count] = $2;
						stable[id_count]->datatype = INT;
						stable[id_count]->size = *($4->store.int_store);
						stable[id_count]->store.int_store = (int *)malloc(sizeof(int)*(stable[id_count]->size));
						memset( stable[id_count]->store.int_store, 0, sizeof(int)*(stable[id_count]->size));
						free($4->store.int_store);
						free($4);
						id_count++;}
		|BOOLEAN ID '[' expr ']' ';'	{if($4->datatype!=INT)
							yyerror();
						stable[id_count] = $2;
						stable[id_count]->datatype = BOOL;
						stable[id_count]->size = *($4->store.int_store);
						stable[id_count]->store.bool_store = (bool *)malloc(sizeof(bool)*(stable[id_count]->size));
						memset( stable[id_count]->store.bool_store, false, sizeof(bool)*(stable[id_count]->size));
						free($4->store.int_store);
						free($4);
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
		|read			{}
		|write			{}
		;

expr		:expr '+' expr		{if(($1->datatype==$3->datatype) && ($3->datatype==INT) )
					{
						symbol* ptr = (symbol *)malloc(sizeof(symbol));
						ptr->datatype = INT;
						ptr->store.int_store = (int *)malloc(sizeof(int));
						*(ptr->store.int_store) = *($1->store.int_store) + *($3->store.int_store);
						$$ = ptr;
						free($1->store.int_store); free($3->store.int_store);
						free($1); free($3);	
					}
					else {yyerror();}}
		|expr '-' expr		{if(($1->datatype==$3->datatype) && ($3->datatype==INT) )
					{
						symbol* ptr = (symbol *)malloc(sizeof(symbol));
						ptr->datatype = INT;
						ptr->store.int_store = (int *)malloc(sizeof(int));
						*(ptr->store.int_store) = *($1->store.int_store) - *($3->store.int_store);
						$$ = ptr;
						free($1->store.int_store); free($3->store.int_store);
						free($1); free($3);	
					}
					else {yyerror();}}
		|expr '/' expr		{if(($1->datatype==$3->datatype) && ($3->datatype==INT) )
					{
						symbol* ptr = (symbol *)malloc(sizeof(symbol));
						ptr->datatype = INT;
						ptr->store.int_store = (int *)malloc(sizeof(int));
						*(ptr->store.int_store) = *($1->store.int_store) / *($3->store.int_store);
						$$ = ptr;
						free($1->store.int_store); free($3->store.int_store);
						free($1); free($3);		
					}
					else {yyerror();}}	
		|expr '*' expr		{if(($1->datatype==$3->datatype) && ($3->datatype==INT) )
					{
						symbol* ptr = (symbol *)malloc(sizeof(symbol));
						ptr->datatype = INT;
						ptr->store.int_store = (int *)malloc(sizeof(int));
						*(ptr->store.int_store) = *($1->store.int_store) * *($3->store.int_store);
						$$ = ptr;
						free($1->store.int_store); free($3->store.int_store);
						free($1); free($3);	
					}
					else {yyerror();}}
		|expr EQEQ expr		{if($1->datatype==$3->datatype)
					{
						symbol* ptr = (symbol *)malloc(sizeof(symbol));
						ptr->datatype = BOOL;
						ptr->store.bool_store = (bool *)malloc(sizeof(bool));
						if($1->datatype==BOOL){
							*(ptr->store.bool_store) = (*($1->store.bool_store) == *($3->store.bool_store));
							free($1->store.bool_store); free($3->store.bool_store);}
						else{
							*(ptr->store.bool_store) = (*($1->store.int_store) == *($3->store.int_store));
							free($1->store.int_store); free($3->store.int_store);}	
						$$ = ptr;
						free($1); free($3);	
					}
					else {yyerror();}}
		|expr NEQ expr		{if($1->datatype==$3->datatype)
					{
						symbol* ptr = (symbol *)malloc(sizeof(symbol));
						ptr->datatype = BOOL;
						ptr->store.bool_store = (bool *)malloc(sizeof(bool));
						if($1->datatype==BOOL){
							*(ptr->store.bool_store) = (*($1->store.bool_store) != *($3->store.bool_store));
							free($1->store.bool_store); free($3->store.bool_store);}
						else{
							*(ptr->store.bool_store) = (*($1->store.int_store) != *($3->store.int_store));
							free($1->store.int_store); free($3->store.int_store);}	
						$$ = ptr;
						free($1); free($3);	
					}
					else {yyerror();}}
		|expr AND expr		{if(($1->datatype==$3->datatype) && ($3->datatype==BOOL) )
					{
						symbol* ptr = (symbol *)malloc(sizeof(symbol));
						ptr->datatype = BOOL;
						ptr->store.bool_store = (bool *)malloc(sizeof(bool));
						*(ptr->store.bool_store) = (*($1->store.bool_store) && *($3->store.bool_store));
						$$ = ptr;
						free($1->store.bool_store); free($3->store.bool_store);
						free($1); free($3);	
					}
					else {yyerror();}}
		|expr OR expr		{if(($1->datatype==$3->datatype) && ($3->datatype==BOOL) )
					{
						symbol* ptr = (symbol *)malloc(sizeof(symbol));
						ptr->datatype = BOOL;
						ptr->store.bool_store = (bool *)malloc(sizeof(bool));
						*(ptr->store.bool_store) = (*($1->store.bool_store) || *($3->store.bool_store));
						$$ = ptr;
						free($1->store.bool_store); free($3->store.bool_store);
						free($1); free($3);	
					}
					else {yyerror();}}
		|expr LTHAN expr	{if(($1->datatype==$3->datatype) && ($3->datatype==INT) )
					{
						symbol* ptr = (symbol *)malloc(sizeof(symbol));
						ptr->datatype = BOOL;
						ptr->store.bool_store = (bool *)malloc(sizeof(bool));
						*(ptr->store.bool_store) = (*($1->store.int_store) < *($3->store.int_store));
						$$ = ptr;
						free($1->store.int_store); free($3->store.int_store);
						free($1); free($3);	
					}
					else {yyerror();}}
		|expr GTHAN expr	{if(($1->datatype==$3->datatype) && ($3->datatype==INT) )
					{
						symbol* ptr = (symbol *)malloc(sizeof(symbol));
						ptr->datatype = BOOL;
						ptr->store.bool_store = (bool *)malloc(sizeof(bool));
						*(ptr->store.bool_store) = (*($1->store.int_store) > *($3->store.int_store));
						$$ = ptr;
						free($1->store.int_store); free($3->store.int_store);
						free($1); free($3);	
					}
					else {yyerror();}}
		|expr LEQ expr		{if(($1->datatype==$3->datatype) && ($3->datatype==INT) )
					{
						symbol* ptr = (symbol *)malloc(sizeof(symbol));
						ptr->datatype = BOOL;
						ptr->store.bool_store = (bool *)malloc(sizeof(bool));
						*(ptr->store.bool_store) = (*($1->store.int_store) <= *($3->store.int_store));
						$$ = ptr;
						free($1->store.int_store); free($3->store.int_store);
						free($1); free($3);	
					}
					else {yyerror();}}
		|expr GEQ expr		{if(($1->datatype==$3->datatype) && ($3->datatype==INT) )
					{
						symbol* ptr = (symbol *)malloc(sizeof(symbol));
						ptr->datatype = BOOL;
						ptr->store.bool_store = (bool *)malloc(sizeof(bool));
						*(ptr->store.bool_store) = (*($1->store.int_store) >= *($3->store.int_store));
						$$ = ptr;
						free($1->store.int_store); free($3->store.int_store);
						free($1); free($3);	
					}
					else {yyerror();}}
		|NOT expr 		{if($2->datatype==BOOL)
					{	
						*($2->store.bool_store) = !(*($1->store.bool_store));
						$$ = $2; 
					}
					else {yyerror();}}	
	
		|'(' expr ')'		{$$=$2;}

		|ID			{if(find_id($1,0)!=id_count)
						$$=$1;
					else
						yyerror();}

		|ID '[' expr ']'	{if($3->datatype!=INT)
						yyerror();
					if(find_id($1,*($3->store.int_store))==id_count)
						yyerror();
					$$=$1;
					free($3->store.int_store);
					free($3);				
					}

		|NUM			{$$=$1;}
		|BOOLE			{$$=$1;}
		;

assignment	:ID '=' expr ';'	{int i = find_id($1,0);
					if(i!=id_count)
					{	
						if((stable[i]->datatype == $3->datatype) && (stable[i]->datatype == BOOL))
							*(stable[i]->store.bool_store) = *($3->store.bool_store);
						if((stable[i]->datatype == $3->datatype) && (stable[i]->datatype == INT))
							*(stable[i]->store.int_store) = *($3->store.int_store);
						free($1->store.int_store); free($3->store.int_store); 	
						free($1); free($3);
					}
					else {yyerror();}}

		|ID '[' expr ']' '=' expr ';'		{if($3->datatype!=INT)
								yyerror();
							int pos = *($3->store.int_store);
							int i = find_id($1,pos);
							if(i!=id_count)
							{	
								if((stable[i]->datatype == $6->datatype) && (stable[i]->datatype == BOOL))
									*(stable[i]->store.bool_store + pos) = *($6->store.bool_store);
								if((stable[i]->datatype == $6->datatype) && (stable[i]->datatype == INT))
									*(stable[i]->store.int_store + pos) = *($6->store.int_store);
								free($1->store.int_store); free($3->store.int_store); free($6->store.int_store);
								free($1); free($3); free($6);
							}
							else {yyerror();}}
		;

condition	:IF expr THEN stmtlist ENDIF ';'		{if($2->datatype == INT)
									{free($2->store.int_store);}
								else {free($2->store.bool_store);}
								free($2);}
		|IF expr THEN stmtlist ELSE stmtlist ENDIF ';'	{if($2->datatype == INT)
									{free($2->store.int_store);}
								else {free($2->store.bool_store);}
								free($2);}
		;

loop		:WHILE expr DO stmtlist ENDWHILE ';'		{if($2->datatype == INT)
									{free($2->store.int_store);}
								else {free($2->store.bool_store);}
								free($2);}
		;

read		:READ "(" ID ")" ";"				{free($3);}
		;

write		:WRITE "(" expr ")" ";"				{if($3->datatype == INT)
									{free($3->store.int_store);}
								else {free($3->store.bool_store);}
								free($3);}

%%

int find_id(symbol* ptr, int pos)
{
	int j;	
	for(j=0;j<id_count;j++)
	{
		if(strcmp(ptr->name,stable[j]->name)==0)
		{
			ptr->datatype = stable[j]->datatype;
			ptr->size = stable[j]->size;

			if(ptr->datatype==INT){
				ptr->store.int_store = (int *)malloc(sizeof(int)); 
				*(ptr->store.int_store) = *(stable[j]->store.int_store + pos);
			}
			else{
				ptr->store.bool_store = (bool *)malloc(sizeof(bool)); 
				*(ptr->store.bool_store) = *(stable[j]->store.bool_store + pos);
			}
			return j;
		}
	}
	return id_count;
}

    
yyerror()
{
    printf("\nError here\n");
}

main()
{
    yyparse();
    return 1;
}












