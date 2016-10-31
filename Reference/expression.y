%{
	/*** Auxiliary declarations section ***/

#include <iostream>
#include <cmath>
#include "exptree.h" 

int yylex();
void yyerror (char const *s);

%}

/*** YACC Declarations section ***/
%token DIGIT
%left '+' '-'
%left '*' '/'
%right '^'

%%

/*** Rules Section ***/
start:	expr '\n'			{$1->print();std::cout<<"\nAns = "<<$1->evaluate();exit(0);}
	    ;
		
expr:	expr '+' expr		{$$ = new Node('+');$$->left = $1;$$->right = $3;}
	    | '-' expr			{$$ = new Node('-');$$->left = new Node(0);$$->right = $2;}
	    | expr '-' expr		{$$ = new Node('-');$$->left = $1;$$->right = $3;}
	    | expr '*' expr		{$$ = new Node('*');$$->left = $1;$$->right = $3;}
	    | expr '/' expr		{$$ = new Node('/');$$->left = $1;$$->right = $3;}
	    | expr '^' expr		{$$ = new Node('^');$$->left = $1;$$->right = $3;}
	    | '(' expr ')'		{$$ = $2;}
	    | DIGIT				{$$ = new Node($1->val);}
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