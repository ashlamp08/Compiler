%{

#include <stdio.h>
#include <stdlib.h>

#define YYSTYPE char*

%}

%token ALPHA
%left '+' '-'
%left '*' '/'
%left '(' ')'

%%

start : expr '\n'       {printf("\ncomplete\n");exit(1);}
    ;

expr:  expr '+' expr    {printf(" + ");}
    | expr '-' expr     {printf(" - ");}
    | expr '/' expr     {printf(" / ");}
    | expr '*' expr     {printf(" * ");}
    | '(' expr ')'
    | ALPHA             {printf(" %s ",$1);}
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
    
