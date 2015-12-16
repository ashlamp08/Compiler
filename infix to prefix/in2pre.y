%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define YYSTYPE char*

%}

%token ALPHA
%left '+' '-'
%left '*' '/'
%left '(' ')'

%%

start : expr '\n'       {$$=$1; printf(" %s ",$$);exit(1);}
    ;

expr:  expr '+' expr    {strcat($2,$1);strcat($2,$3);$$=$2;}
    | expr '-' expr     {strcat($2,$1);strcat($2,$3);$$=$2;}
    | expr '/' expr     {strcat($2,$1);strcat($2,$3);$$=$2;}
    | expr '*' expr     {strcat($2,$1);strcat($2,$3);$$=$2;}
    | '(' expr ')'	{$$=$2;}
    | ALPHA             {$$=$1;}
    ;

%%
    
yyerror()
{
    printf("Error");
}

main()
{
    yyparse();
    return 1;
}
    
