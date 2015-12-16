%{
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include<malloc.h>
	#include "exptree.h"
	
	int yylex(void);
	void yyerror(char *);
	int evaltree(node *);
%}

%token DIGIT
%left '+' '-'
%left '*' '/'
%left '(' ')'

%%

program	:	program expr'\n'	{$$=$2;
					int n=evaltree($$);
					printf(" %d\n",n);}
		|
		;

expr	:	DIGIT			{$$=$1;}
		| '(' expr ')'		{$$ = $2;}
		| expr '+' expr 	{$2->left = $1;
					$2->right = $3;
					$$ = $2;}
		| expr '-' expr 	{$2->left = $1;
					$2->right = $3;
					$$ = $2;}
		| expr '*' expr 	{$2->left = $1;
					$2->right = $3;
					$$ = $2;}
		| expr '/' expr 	{$2->left = $1;
					$2->right = $3;
					$$ = $2;}	 	
		;

%%

void yyerror(char *s) {
	fprintf(stderr, "%s\n", s);
}

int evaltree(node *nd)
{
	if(nd->flag == 0)
		return nd->val;
	else
	{
		if(nd->op == '+')
			return (evaltree(nd->left) + evaltree(nd->right));
		else if(nd->op == '-')
			return (evaltree(nd->left) - evaltree(nd->right));
		else if(nd->op == '*')
			return (evaltree(nd->left) * evaltree(nd->right));
		else if(nd->op == '/')
			return (evaltree(nd->left) / evaltree(nd->right));	
	}
}

int yywrap()
{
	return 1;
}

int main(void) 
{
	yyparse();
	return 0;
}




