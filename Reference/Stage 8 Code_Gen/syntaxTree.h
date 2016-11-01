#ifndef SYNTAXTREE_H
#define SYNTAXTREE_H

#include "symbolTable.h"
#include <string>

#define PASS 2
#define WARN 1
#define FAIL 0

class SNode {
	// this field should carry following information:
	int NODETYPE;									// a) operator : (+,*,/ etc.) for expressions
	// b) statement Type : (WHILE, READ etc.) for statements */

	int TYPE;										// Integer, Boolean

	std::string NAME;								// For Identifiers/Functions

	int VALUE;										// for constants
	SNode *ArgList;									// List of arguments for functions

	SNode *PTR1, *PTR2, *PTR3;
	SNode *next;

	symbolNode *table;
	symbolNode *entry;

	static int count;

	void init();
	void print(SNode *bst, std::string str, int side);
	/* Maximum of three subtrees (3 required for IF THEN ELSE */
	int execute(SNode *bst);
	int execute();
	void assignSpace(symbolNode *table);
	void deassignSpace(symbolNode *table);
	void runStatements();
	int typeCheck(SNode *);
	int codeGen(SNode *node, FILE *output);
  public:
	int lineNo;
	int colNo;

	SNode(int nodetype, int l, int c);							//
	SNode(int nodetype, int value, int l, int c);					// Constructors
	SNode(int nodetype, const std::string &name, int l, int c);	//

	~SNode();										// Destructor

	SNode *getPTR1();								//
	SNode *getPTR2();								//
	SNode *getPTR3();								// Getters
	SNode *getNext();								//
	symbolNode *getTable();							//
	symbolNode *getEntry();							//
	int getNodeType();								//
	int getType();									//
	int getValue();									//
	std::string getName();							//
	static int getCount();

	void setPTR1(SNode *ptr);						//
	void setPTR2(SNode *ptr);						//	Setters
	void setPTR3(SNode *ptr);						//
	void setNext(SNode *ptr);						//
	void setTable(symbolNode *ptr);					//
	void setEntry(symbolNode *ptr);					//
	void setType(int type);							//

	void print();
	int codeGen(FILE *output);
	int run();
	int typeCheck();
	std::string to_string();
};

#define YYSTYPE SNode*

#endif // SYNTAXTREE_H
