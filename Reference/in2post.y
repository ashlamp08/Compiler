%{
	/*** Auxiliary declarations section ***/

#include <iostream>
#include <cmath>
int yylex();
void yyerror (char const *s);

%}

/*** YACC Declarations section ***/
%token DIGIT
%left '+' '-'
%left '*' '/'
%left '^'

%%

/*** Rules Section ***/
start:	expr '\n'			{std::cout<<"\nAns = "<<$1<<"\n";exit(0);}
	    ;
		
expr:	expr '+' expr		{$$ = $1 + $3;std::cout<<"\nCheck $1="<<$1<<" $2="<<$2<<" $3="<<$3<<"\n"}
	    | expr '-' expr		{$$ = $1 - $3;}
	    | expr '*' expr		{$$ = $1 * $3;}
	    | expr '/' expr		{$$ = $1 / $3;}
	    | expr '^' expr		{$$ = pow($1,$3);}
	    | '(' expr ')'		{$$ = $2}
	    | DIGIT				{$$ = $1}
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