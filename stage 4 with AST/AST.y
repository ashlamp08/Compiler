%{
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include<stdbool.h>
	#include<malloc.h>
	#include "astree.h"

	symbol* stable[100];
	int id_count = 0; 
	int find_id(char *);
	ast* statement(ast*, ast*);
	ast* assign(ast*, ast*, ast*);
	ast *cond(ast*, ast*, ast*);
	ast* loop(ast*, ast*);
	ast* read(ast*, ast*);
	ast* write(ast*);
	ast* expression(int, ast*, ast*);
	void make_node(ast*, int, int, char*, int, bool, ast*, ast*, ast*, symbol*);
	void make_symbol(symbol*, int, char*, int);
	void evaluate_ast(ast*);

	#define INT 1
	#define BOOL 0
	#define ASSG 10
	#define VOID -1

%}

%token BOOLE
%token NUM
%token ID
%token BEG
%token END
%token DECL
%token ENDDECL
%token IF
%token THEN
%token ELSE
%token ENDIF
%token WHILE
%token DO
%token ENDWHILE
%token READ
%token WRITE
%token PLUS
%token MINUS
%token MUL
%token DIV
%token AND
%token OR
%token NOT
%token LEQ
%token GEQ
%token LTHAN
%token GTHAN
%token INTEGER
%token BOOLEAN
%left LEQ GEQ LTHAN GTHAN
%left EQEQ NEQ 
%left AND 
%left OR
%left NOT
%left PLUS MINUS
%left MUL DIV
%left '(' ')'

%%

program 	:declaration body		{$$ = $2; evaluate_ast($$);
						printf("\nComplete\n");exit(1);}	
		; 

declaration 	:DECL dlist ENDDECL		{}
		;

dlist		:dstmt dlist 			{}

		|dstmt				{}
		;

dstmt		:INTEGER ID ';'			{stable[id_count] = (symbol *)malloc(sizeof(symbol));
						make_symbol(stable[id_count],INT,$2->name,0);
						free($2);								
						id_count++;}

		|BOOLEAN ID ';'			{stable[id_count] = (symbol *)malloc(sizeof(symbol));
						make_symbol(stable[id_count],BOOL,$2->name,0);	
						free($2);			
						id_count++;}

		|INTEGER ID '[' NUM ']' ';'	{if($4->datatype!=INT)
							yyerror();
						stable[id_count] = (symbol *)malloc(sizeof(symbol));
						make_symbol(stable[id_count],INT,$2->name,$4->int_value);	
						free($2); free($4);						
						id_count++;}

		|BOOLEAN ID '[' NUM ']' ';'	{if($4->datatype!=INT)
							yyerror();
						stable[id_count] = (symbol *)malloc(sizeof(symbol));
						make_symbol(stable[id_count],BOOL,$2->name,$4->int_value);	
						free($2); free($4);						
						id_count++;}		
		;


body		:BEG stmtlist END 		{$$=$2;}
		;

stmtlist	:stmt stmtlist			{$$ = statement($1,$2);}
		|stmt				{$$=$1;}
		;

stmt		:assignment			{$$=$1;}
		|condition			{$$=$1;}
		|loop				{$$=$1;}
		|read				{$$=$1;}
		|write				{$$=$1;}
		;

expr		:expr PLUS expr			{$$ = expression(PLUS,$1,$3);}
		|expr MINUS expr		{$$ = expression(MINUS,$1,$3);}
		|expr DIV expr			{$$ = expression(DIV,$1,$3);}
		|expr MUL expr			{$$ = expression(MUL,$1,$3);}
		|expr EQEQ expr			{$$ = expression(EQEQ,$1,$3);}
		|expr NEQ expr			{$$ = expression(NEQ,$1,$3);}	
		|expr AND expr			{$$ = expression(AND,$1,$3);}
		|expr OR expr			{$$ = expression(OR,$1,$3);}
		|expr LTHAN expr		{$$ = expression(LTHAN,$1,$3);}
		|expr GTHAN expr		{$$ = expression(GTHAN,$1,$3);}
		|expr LEQ expr			{$$ = expression(LEQ,$1,$3);}
		|expr GEQ expr			{$$ = expression(GEQ,$1,$3);}
		|NOT expr 			{$$ = expression(NOT,$1,NULL);}
		|'(' expr ')'			{$$=$2;}

		|ID				{$$ = expression(ID,$1,NULL);}
				
		|ID '[' expr ']'		{$$ = expression(ID,$1,$3);}

		|NUM				{$$=$1;}
		|BOOLE				{$$=$1;}
		;

assignment	:ID '=' expr ';'				{$$ = assign($1,$3,NULL);}
					
		|ID '[' expr ']' '=' expr ';'			{$$ = assign($1,$3,$6);}
		;

condition	:IF expr THEN stmtlist ENDIF ';'		{$$ = cond($2,$4,NULL);}
								
		|IF expr THEN stmtlist ELSE stmtlist ENDIF ';'	{$$ = cond($2,$4,$6);}
		;

loop		:WHILE expr DO stmtlist ENDWHILE ';'		{$$ = loop($2,$4);}
		;

read		:READ '(' ID ')' ';'				{$$ = read($3,NULL);}
		|READ '(' ID '[' expr ']' ')' ';'		{$$ = read($3,$5);}
		;

write		:WRITE '(' expr ')' ';'				{$$ = write($3);}

%%

void evaluate_ast(ast* node)
{
	switch(node->nodetype)
	{
		case VOID: 	evaluate_ast(node->ptr1); evaluate_ast(node->ptr2);
				break;
		case ASSG:	if(node->ptr3==NULL)
				{
					evaluate_ast(node->ptr2);
					if(node->ptr1->datatype==INT)
						*(node->ptr1->Gentry->store.int_store) = node->ptr2->int_value;
					else	
						*(node->ptr1->Gentry->store.bool_store) = node->ptr2->bool_value;
				}
				else
				{
					evaluate_ast(node->ptr2); evaluate_ast(node->ptr3);
					if(node->ptr1->datatype==INT)
						*(node->ptr1->Gentry->store.int_store + node->ptr2->int_value) = node->ptr3->int_value;
					else	
						*(node->ptr1->Gentry->store.bool_store + node->ptr2->int_value) = node->ptr3->bool_value;
				}
				break;
		case IF:	if(node->ptr3==NULL)
				{
					evaluate_ast(node->ptr1);
					if(node->ptr1->bool_value==true)
						evaluate_ast(node->ptr2);
				}
				else
				{
					evaluate_ast(node->ptr1);
					if(node->ptr1->bool_value==true)
						evaluate_ast(node->ptr2);
					else
						evaluate_ast(node->ptr3);
				}
				break;
		case WHILE:	evaluate_ast(node->ptr1);
				while(node->ptr1->bool_value==true)
				{
					evaluate_ast(node->ptr2);
					evaluate_ast(node->ptr1);
				}
				break;
		case READ:	if(node->ptr2==NULL)
				{
					if(node->ptr1->datatype==INT)
						scanf("%d",(node->ptr1->Gentry->store.int_store));
					else	
						scanf("%d",(node->ptr1->Gentry->store.bool_store));
				}
				else
				{
					evaluate_ast(node->ptr2);
					if(node->ptr1->datatype==INT)
						scanf("%d",(node->ptr1->Gentry->store.int_store + node->ptr2->int_value));
					else	
						scanf("%d",(node->ptr1->Gentry->store.bool_store + node->ptr2->int_value));
				}
				break;
		case WRITE:	evaluate_ast(node->ptr1);
				if(node->ptr1->datatype==INT)
					printf("%d",node->ptr1->int_value);
				else
					printf("%d",node->ptr1->bool_value);
				break;
		case PLUS:	evaluate_ast(node->ptr1); evaluate_ast(node->ptr2);
				node->int_value = node->ptr1->int_value + node->ptr2->int_value;
				break;
		case MINUS:	evaluate_ast(node->ptr1); evaluate_ast(node->ptr2);
				node->int_value = node->ptr1->int_value - node->ptr2->int_value;
				break;
		case MUL:	evaluate_ast(node->ptr1); evaluate_ast(node->ptr2);
				node->int_value = node->ptr1->int_value * node->ptr2->int_value;
				break;
		case DIV:	evaluate_ast(node->ptr1); evaluate_ast(node->ptr2);
				node->int_value = node->ptr1->int_value / node->ptr2->int_value;
				break;
		case LTHAN:	evaluate_ast(node->ptr1); evaluate_ast(node->ptr2);
				node->bool_value = node->ptr1->int_value < node->ptr2->int_value;
				break;
		case GTHAN:	evaluate_ast(node->ptr1); evaluate_ast(node->ptr2);
				node->bool_value = node->ptr1->int_value > node->ptr2->int_value;
				break;
		case LEQ:	evaluate_ast(node->ptr1); evaluate_ast(node->ptr2);
				node->bool_value = node->ptr1->int_value <= node->ptr2->int_value;
				break;		
		case GEQ:	evaluate_ast(node->ptr1); evaluate_ast(node->ptr2);
				node->bool_value = node->ptr1->int_value >= node->ptr2->int_value;
				break;
		case EQEQ:	evaluate_ast(node->ptr1); evaluate_ast(node->ptr2);
				node->bool_value = node->ptr1->int_value == node->ptr2->int_value;
				break;
		case NEQ:	evaluate_ast(node->ptr1); evaluate_ast(node->ptr2);
				node->bool_value = node->ptr1->int_value != node->ptr2->int_value;
				break;
		case AND:	evaluate_ast(node->ptr1); evaluate_ast(node->ptr2);
				node->bool_value = node->ptr1->bool_value && node->ptr2->bool_value;
				break;
		case OR:	evaluate_ast(node->ptr1); evaluate_ast(node->ptr2);
				node->bool_value = node->ptr1->bool_value || node->ptr2->bool_value;
				break;
		case NOT:	evaluate_ast(node->ptr1);
				node->bool_value = !(node->ptr1->bool_value);
				break;
		case ID:	if(node->ptr1==NULL)
				{
					if(node->datatype==INT)
						node->int_value = *(node->Gentry->store.int_store);
					else	
						node->bool_value = *(node->Gentry->store.bool_store);
				}
				else
				{
					evaluate_ast(node->ptr1);				
					if(node->datatype==INT)
						node->int_value = *(node->Gentry->store.int_store + (node->ptr1->int_value));
					else	
						node->bool_value = *(node->Gentry->store.bool_store + (node->ptr1->int_value));
				}
				break;
		default:	break;
	}
}


void make_node(ast* node, int dtype, int ntype, char* na, int int_val, bool bool_val, ast* p1, ast* p2, ast* p3, symbol *s)
{
	node->datatype = dtype;
	node->nodetype = ntype;
	if(na!=NULL)
		strcpy(node->name,na);
	node->int_value = int_val;
	node->bool_value = bool_val;

	node->ptr1 = p1; node->ptr2 = p2; node->ptr3 = p3;
	node->Gentry = s;
}

void make_symbol(symbol* sym, int dtype, char *n, int sz)
{
	sym->datatype = dtype;
	if(n!=NULL)
		strcpy(sym->name,n);
	sym->size = sz;
	if(sym->datatype == INT)
	{
		sym->store.int_store = (int *)malloc(sizeof(int)*(sym->size));
		memset(sym->store.int_store, 0, sizeof(int)*(sym->size));
	}
	else
	{
		sym->store.bool_store = (bool *)malloc(sizeof(bool)*(sym->size));
		memset(sym->store.bool_store, false, sizeof(bool)*(sym->size));
	}
}

int find_id(char* str)
{
	int j;	
	for(j=0;j<id_count;j++)
	{
		if(strcmp(str,stable[j]->name)==0)
			return j;
	}
	return id_count;
}

ast* statement(ast* a, ast* b)
{
	ast* ptr;
	ptr =(ast *)malloc(sizeof(ast));
	make_node(ptr,VOID,VOID,NULL,0,false,a,b,NULL,NULL);

	return ptr;
}

ast* assign(ast* a, ast* b, ast* c)
{
	int i = find_id(a->name);

	if(i!=id_count)
		a->Gentry = stable[i];
	else
		yyerror();

	a->datatype = stable[i]->datatype;
	
	ast* ptr;

	if(c == NULL)
	{
		if(a->datatype != b->datatype)
			yyerror();

		ptr =(ast *)malloc(sizeof(ast));
		make_node(ptr, VOID,ASSG,NULL,0,false,a,b,NULL,NULL);
	}
	else
	{
		if(a->datatype != c->datatype)
			yyerror();

		if(b->datatype!=INT)
			yyerror();
		ptr =(ast *)malloc(sizeof(ast));
		make_node(ptr, VOID,ASSG,NULL,0,false,a,b,c,NULL);
	}
	
	return ptr;
}	

ast *cond(ast* a, ast* b, ast* c)
{
	if(a->datatype!=BOOL || b->datatype!=VOID)
		yyerror();

	ast* ptr;

	if(c==NULL)
	{
		ptr =(ast *)malloc(sizeof(ast));
		make_node(ptr, VOID,IF,NULL,0,false,a,b,NULL,NULL);
	}
	else
	{
		if(c->datatype!=VOID)
			yyerror();
		ptr =(ast *)malloc(sizeof(ast));
		make_node(ptr, VOID,IF,NULL,0,false,a,b,c,NULL);
	}
		
	return ptr;
}

ast* loop(ast *a, ast* b)
{
	if(a->datatype!=BOOL || b->datatype!=VOID)
		yyerror();

	ast* ptr;

	ptr =(ast *)malloc(sizeof(ast));
	make_node(ptr, VOID,WHILE,NULL,0,false,a,b,NULL,NULL);

	return ptr;
}

ast* read(ast* a, ast* b)
{
	int i = find_id(a->name);

	if(i!=id_count || (b->datatype!=INT))
		a->Gentry = stable[i];
	else
		yyerror();

	a->datatype = stable[i]->datatype;

	ast* ptr;

	ptr =(ast *)malloc(sizeof(ast));
	if(b!=NULL)
		make_node(ptr, VOID,READ,NULL,0,false,a,b,NULL,NULL);
	else
		make_node(ptr, VOID,READ,NULL,0,false,a,NULL,NULL,NULL);

	return ptr;
}

ast* write(ast* a)
{
	ast* ptr;

	ptr =(ast *)malloc(sizeof(ast));
	make_node(ptr, VOID,WRITE,NULL,0,false,a,NULL,NULL,NULL);

	return ptr;
}

ast* expression(int type, ast* a, ast* b)
{
	ast *ptr;
	int i;
	switch(type)
	{
		case PLUS: 	if((a->datatype!=INT) || (b->datatype!=INT))
					yyerror();
				ptr =(ast *)malloc(sizeof(ast));
				make_node(ptr, INT,PLUS,NULL,0,false,a,b,NULL,NULL);
				break;				
		case MINUS: 	if((a->datatype!=INT) || (b->datatype!=INT))
					yyerror();
				ptr =(ast *)malloc(sizeof(ast));
				make_node(ptr, INT,MINUS,NULL,0,false,a,b,NULL,NULL);
				break;			
		case MUL: 	if((a->datatype!=INT) || (b->datatype!=INT))
					yyerror();
				ptr =(ast *)malloc(sizeof(ast));
				make_node(ptr, INT,MUL,NULL,0,false,a,b,NULL,NULL);
				break;			
		case DIV: 	if((a->datatype!=INT) || (b->datatype!=INT))
					yyerror();
				ptr =(ast *)malloc(sizeof(ast));
				make_node(ptr, INT,DIV,NULL,0,false,a,b,NULL,NULL);
				break;	
		case LTHAN: 	if((a->datatype!=INT) || (b->datatype!=INT))
					yyerror();
				ptr =(ast *)malloc(sizeof(ast));
				make_node(ptr, BOOL,LTHAN,NULL,0,false,a,b,NULL,NULL);
				break;			
		case GTHAN: 	if((a->datatype!=INT) || (b->datatype!=INT))
					yyerror();
				ptr =(ast *)malloc(sizeof(ast));
				make_node(ptr, BOOL,GTHAN,NULL,0,false,a,b,NULL,NULL);
				break;
		case LEQ: 	if((a->datatype!=INT) || (b->datatype!=INT))
					yyerror();
				ptr =(ast *)malloc(sizeof(ast));
				make_node(ptr, BOOL,LEQ,NULL,0,false,a,b,NULL,NULL);
				break;			
		case GEQ: 	if((a->datatype!=INT) || (b->datatype!=INT))
					yyerror();
				ptr =(ast *)malloc(sizeof(ast));
				make_node(ptr, BOOL,GEQ,NULL,0,false,a,b,NULL,NULL);
				break;		
		case EQEQ: 	if((a->datatype!=INT) || (b->datatype!=INT))
					yyerror();
				ptr =(ast *)malloc(sizeof(ast));
				make_node(ptr, BOOL,EQEQ,NULL,0,false,a,b,NULL,NULL);
				break;								
		case NEQ: 	if((a->datatype!=INT) || (b->datatype!=INT))
					yyerror();
				ptr =(ast *)malloc(sizeof(ast));
				make_node(ptr, BOOL,NEQ,NULL,0,false,a,b,NULL,NULL);
				break;	
		case AND: 	if((a->datatype!=BOOL) || (b->datatype!=BOOL))
					yyerror();
				ptr =(ast *)malloc(sizeof(ast));
				make_node(ptr, BOOL,AND,NULL,0,false,a,b,NULL,NULL);
				break;			
		case OR: 	if((a->datatype!=BOOL) || (b->datatype!=BOOL))
					yyerror();
				ptr =(ast *)malloc(sizeof(ast));
				make_node(ptr, BOOL,OR,NULL,0,false,a,b,NULL,NULL);
				break;			
		case NOT: 	if(a->datatype!=BOOL)
					yyerror();
				ptr =(ast *)malloc(sizeof(ast));
				make_node(ptr, BOOL,NOT,NULL,0,false,a,NULL,NULL,NULL);
				break;
		case ID:	i = find_id(a->name);
				if(i!=id_count)
					a->Gentry = stable[i];
				else
					yyerror();

				a->datatype = stable[i]->datatype;

				if(b!=NULL)
				{
					if(b->datatype != INT)
						yyerror();
					a->ptr1 = b;
				}
	
				ptr = a;
				break;

		default: 	break;
	}
	return ptr;
} 	
		
    
yyerror()
{
    printf("\nError here\n");
}

main()
{
    yyparse();
    return 1;
}
