%{
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include<stdbool.h>
	#include<malloc.h>
	
	#include "astree.h"

	symbol* stable[100];
	int id_count = 0; 
	int label_count = 0;
	int var_count = 0;
	int reg_count = 0;
	int find_id(char *);
	int getreg();
	void freereg(); 
	int getlabel();
	ast* statement(ast*, ast*);
	ast* assign(ast*, ast*, ast*);
	ast *cond(ast*, ast*, ast*);
	ast* loop(ast*, ast*);
	ast* read(ast*, ast*);
	ast* write(ast*);
	ast* expression(int, ast*, ast*);
	void make_node(ast*, int, int, char*, int, bool, ast*, ast*, ast*, symbol*);
	void make_symbol(symbol*, int, char*, int);
	int evaluate_ast(ast*);
	FILE *fp;

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

program 	:declaration body		{$$ = $2; 
						fprintf(fp,"START\n");						
						evaluate_ast($$);
						fprintf(fp,"HALT\n");
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

int getreg() {return reg_count++;}
void freereg() {reg_count--;}
int getlabel() {return label_count++;}

int evaluate_ast(ast* node)
{
	int i,r1,r2,r3,r4,l1,l2,l3,l4,temp,add;

	switch(node->nodetype)
	{
		case VOID: 	evaluate_ast(node->ptr1); evaluate_ast(node->ptr2);
				break;
		case ASSG:	if(node->ptr3==NULL)
				{
					i = find_id(node->ptr1->name);
					
					add = stable[i]->store;
					r1 = evaluate_ast(node->ptr2);

					fprintf(fp, "MOV [%d], R%d\n",add,r1);

					freereg();
					return 1;
				}
				else
				{
					i = find_id(node->ptr1->name);
					
					add = stable[i]->store;
					r1 = evaluate_ast(node->ptr2);
					r2 = evaluate_ast(node->ptr3);
					r3 = getreg();

					fprintf(fp, "MOV R%d, %d\n",r3,add);
					fprintf(fp, "ADD R%d, R%d\n",r1,r3);
					fprintf(fp, "MOV [R%d], R%d\n",r1,r2);
					
					freereg();
					freereg();
					freereg();

					return 1;					
				}
				break;
		case IF:	if(node->ptr3==NULL)
				{
					l1 = getlabel();
					r1 = evaluate_ast(node->ptr1);
					fprintf(fp, "JZ R%d, L%d\n",r1,l1);
					freereg();
					evaluate_ast(node->ptr2);
					fprintf(fp, "L%d:\n", l1);
					return 1;
				}
				else
				{
					l1 = getlabel();
					l2 = getlabel();
					r1 = evaluate_ast(node->ptr1);
					fprintf(fp, "JZ R%d, L%d\n",r1,l1);
					freereg();
					evaluate_ast(node->ptr2);
					fprintf(fp, "JMP L%d\n", l2);
					fprintf(fp, "L%d:\n", l1);
					evaluate_ast(node->ptr3);
					fprintf(fp, "L%d:\n", l2);
					return 1;
				}
				break;


		case WHILE:	l1 = getlabel();
				l2 = getlabel();
				fprintf(fp,"L%d:\n",l1);
				r1 = evaluate_ast(node->ptr1);
				fprintf(fp, "JZ R%d, L%d\n",r1,l2);
				freereg();
				evaluate_ast(node->ptr2);
				fprintf(fp, "JMP L%d\n", l1);
				fprintf(fp, "L%d:\n", l2);
				return 1;
				break;

		case READ:	if(node->ptr2==NULL)
				{
					i = find_id(node->ptr1->name);
					
					add = stable[i]->store;
					r1 = getreg();

					fprintf(fp, "IN R%d\n",r1);
					fprintf(fp, "MOV [%d], R%d\n",add,r1);

					freereg();
					return 1;
				}
				else
				{
					i = find_id(node->ptr1->name);
					
					add = stable[i]->store;
					r1 = evaluate_ast(node->ptr2);
					r2 = getreg();

					fprintf(fp, "MOV R%d, %d\n",r2,add);
					fprintf(fp, "ADD R%d, R%d\n",r1,r2);
					fprintf(fp, "IN R%d\n",r2);
					fprintf(fp, "MOV [R%d], R%d\n",r1,r2);
					
					freereg();
					freereg();

					return 1;					
				}
				break;

		case WRITE:	r1 = evaluate_ast(node->ptr1);
				fprintf(fp,"OUT R%d\n",r1);
				freereg();
				break;

		case PLUS:	r1 = evaluate_ast(node->ptr1); r2 = evaluate_ast(node->ptr2);
				fprintf(fp,"ADD R%d, R%d\n",r1,r2);
				freereg();
				return r1;
				break;
		case MINUS:	r1 = evaluate_ast(node->ptr1); r2 = evaluate_ast(node->ptr2);
				fprintf(fp,"SUB R%d, R%d\n",r1,r2);
				freereg();
				return r1;
				break;
		case MUL:	r1 = evaluate_ast(node->ptr1); r2 = evaluate_ast(node->ptr2);
				fprintf(fp,"MUL R%d, R%d\n",r1,r2);
				freereg();
				return r1;
				break;
		case DIV:	r1 = evaluate_ast(node->ptr1); r2 = evaluate_ast(node->ptr2);
				fprintf(fp,"DIV R%d, R%d\n",r1,r2);
				freereg();
				return r1;
				break;
		case LTHAN:	r1 = evaluate_ast(node->ptr1); r2 = evaluate_ast(node->ptr2);
				fprintf(fp,"LT R%d, R%d\n",r1,r2);
				freereg();
				return r1;
				break;
		case GTHAN:	r1 = evaluate_ast(node->ptr1); r2 = evaluate_ast(node->ptr2);
				fprintf(fp,"GT R%d, R%d\n",r1,r2);
				freereg();
				return r1;
				break;
		case LEQ:	r1 = evaluate_ast(node->ptr1); r2 = evaluate_ast(node->ptr2);
				fprintf(fp,"LE R%d, R%d\n",r1,r2);
				freereg();
				return r1;
				break;		
		case GEQ:	r1 = evaluate_ast(node->ptr1); r2 = evaluate_ast(node->ptr2);
				fprintf(fp,"GE R%d, R%d\n",r1,r2);
				freereg();
				return r1;
				break;
		case EQEQ:	r1 = evaluate_ast(node->ptr1); r2 = evaluate_ast(node->ptr2);
				fprintf(fp,"EQ R%d, R%d\n",r1,r2);
				freereg();
				return r1;
				break;
		case NEQ:	r1 = evaluate_ast(node->ptr1); r2 = evaluate_ast(node->ptr2);
				fprintf(fp,"NE R%d, R%d\n",r1,r2);
				freereg();
				return r1;
				break;
		case ID:	if(node->ptr1==NULL)
				{
					i = find_id(node->name);					
					temp = stable[i]->store;
					
					r1 = getreg();
					fprintf(fp,"MOV R%d, [%d]\n",r1,temp);

					return r1;	
				}
				else
				{
					i = find_id(node->name);		
					
					r1 = getreg();
					r2 = getreg();
					r3 = evaluate_ast(node->ptr1);		
				
					fprintf(fp,"MOV R%d, %d\n",r2,stable[i]->store); 
					fprintf(fp,"ADD R%d, R%d\n",r2,r3);
					fprintf(fp,"MOV R%d,[R%d]\n",r1,r2);

					freereg();			
					freereg();		
					return r1;
				}
				break;
		case NUM:	r1 = getreg();
				fprintf(fp,"MOV R%d, %d\n",r1,node->int_value);
				return r1;
		case BOOLE:	r1 = getreg();
				fprintf(fp,"MOV R%d, %d\n",r1,node->bool_value);
				return r1;		
				
		default:	break;
	}
	return 1;
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
	sym->store = var_count;
	var_count = var_count + sym->size;
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
	fp = fopen("target.sil","w+");
	yyparse();
	fclose(fp);
	return 1;
}
