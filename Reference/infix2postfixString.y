%{
	/*** Auxiliary declarations section ***/

#include <iostream>
#include <cmath>
#include <string>

#define YYSTYPE std::string 

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
start:	expr '\n'			{std::cout<<$1<<"\n";exit(0);}
	    ;
		
expr:	expr '+' expr		{$$ = "(" + $1 + "+" +  $3 + ")"}
	    | expr '-' expr		{$$ = "(" + $1 + "-" +  $3 + ")"}
	    | expr '*' expr		{$$ = "(" + $1 + "*" +  $3 + ")"}
	    | expr '/' expr		{$$ = "(" + $1 + "/" +  $3 + ")"}
	    | expr '^' expr		{$$ = "(" + $1 + "^" +  $3 + ")"}
	    | '(' expr ')'		{$$ = $2;}
	    | ALPHABET			{$$ = $1;}
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