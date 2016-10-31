%{
	/*** Auxiliary declarations section ***/

#include <iostream>
#include <cmath>

#define YYSTYPE char 

int yylex();
void yyerror (char const *s);

%}

/*** YACC Declarations section ***/
%token ALPHABET
%left '+' '-'
%left '*' '/'
%left '^'

%%

/*** Rules Section ***/
start:	expr '\n'			{exit(0);}
	    ;
		
expr:	expr '+' expr		{std::cout<<"+ ";}
	    | expr '-' expr		{std::cout<<"- ";}
	    | expr '*' expr		{std::cout<<"* ";}
	    | expr '/' expr		{std::cout<<"/ ";}
	    | expr '^' expr		{std::cout<<"^ ";}
	    | '(' expr ')'
	    | ALPHABET			{std::cout<<$1<<" ";}
	    ;

%%


/*** Auxiliary functions section ***/

void yyerror(char const *s) {
	std::cout<<"YYERROR::"<<s;
}

int main() {
	yyparse();
	return 0;
}