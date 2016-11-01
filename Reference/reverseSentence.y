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
%token WORD

%%

/*** Rules Section ***/
start:	phrase '\n'			{std::cout<<$$<<"\n";exit(0);}
	    ;
		
phrase:	phrase ' ' WORD		{$$ = $3 + " " + $1;}
		| WORD				{$$ = $1;}
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