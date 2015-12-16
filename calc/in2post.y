%{

#include <stdio.h>
#include <stdlib.h>

%}

%token DIGIT
%left '+' '-'
%left '*' '/'
%left '(' ')'

%%

start : expr '\n'       {printf(" %d ",$1);exit(1);}
    ;

expr:  expr '+' expr    {$$ = (int)$1 + (int)$3;}
    | expr '-' expr     {$$ = (int)$1 - (int)$3;}
    | expr '/' expr     {$$ = (int)$1 / (int)$3;}
    | expr '*' expr     {$$ = (int)$1 * (int)$3;}
    | '(' expr ')'	{$$ = (int)$2;}
    | DIGIT             {$$ = (int)$1;}
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
    
