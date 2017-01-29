typedef struct tnode{
		int flag, val;
            	char op;
		struct tnode *right, *left;
}node;

#define YYSTYPE node *
