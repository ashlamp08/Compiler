struct Node {
	int val;
	char op;
	Node *left, *right;
	Node(int value);
	Node(char oper);
	int evaluate();
	void print();
	void print(Node *bst, std::string str, int side);
};

#define YYSTYPE Node*