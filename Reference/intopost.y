%{
	/*** Auxiliary declarations section ***/

#include <iostream>
#include <cstdlib>
#include <cctype>

/* Custom function to print an operator*/
void print_operator(char op);
int yylex();
void yyerror (char const *s);
/* Variable to keep track of the position of the number in the input */
int pos = 0;

%}

/*** YACC Declarations section ***/
%token DIGIT
%left '+'
%left '*'
%%

/*** Rules Section ***/
start 	:			expr '\n'		{exit(1);}
		;

expr	:	expr '+' expr {print_operator('+');}
		|	expr '*' expr {print_operator('*');}
		| 	'(' expr ')'
		| 	DIGIT {std::cout<<"NUM"<<pos<<" ";}
		;

%%


/*** Auxiliary functions section ***/

void print_operator(char c) {
	switch (c) {
		case '+' :
			std::cout<<"PLUS ";
			break;
		case '*' :
			std::cout<<"MUL ";
			break;
	}
	return;
}

void yyerror(char const *s) {
	std::cout<<"yyerror "<<s;
}

int yylex() {
	char c;
	c = getchar();
	if (isdigit(c)) {
		pos++;
		return DIGIT;
	}
	else if (c == ' ') {
		yylex(); /*This is to ignore whitespaces in the input*/
	}
	else {
		return c;
	}
}

int main() {
	yyparse();
	return 0;
}