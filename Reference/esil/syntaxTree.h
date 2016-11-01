#ifndef SYNTAXTREE_H
#define SYNTAXTREE_H

#include "symbolTable.h"
#include <string>

#define PASS 2
#define WARN 1
#define FAIL 0

class SNode {
	int NODETYPE;					// a) operator : (+,*,/ etc.) for expressions
	// b) statement Type : (WHILE, READ etc.) for statements */

	typeNode *TYPE;						// Data Type (INTEGER , BOOLEAN)

	std::string NAME;				// For Identifiers/Functions

	int VALUE;						// For constants

	std::vector<SNode *> ARGLIST;	// List of Arguments Passed to a Function

	SNode *PTR1, *PTR2, *PTR3;
	SNode *next;

	symbolNode *table;				// if Function, Pointer to Local Symbol Table, else NULL
	symbolNode *entry;				// Pointer to Entry for the Identifier

	static int count;				// Number of object currently in Memory

	void init();
	// void print(SNode *bst, std::string str, int side);
	void printNode(SNode *i, std::string str1, std::string str2, std::string str3);
	int typeCheck(SNode *);
  public:
	void print(SNode *bst, std::string str, int side);
	int lineNo;						// Line No of the Token in input File
	int colNo;						// Column No of the Token in input File

	// Constructors
	SNode(int nodetype, int l, int c);
	SNode(int nodetype, int value, int l, int c);
	SNode(int nodetype, const std::string &name, int l, int c);

	// Destructor
	~SNode();

	//
	void print();
	std::string to_string();
	int typeCheck();

	// Getter Functions
	std::string getName();
	int getValue();
	SNode *getPTR1();
	SNode *getPTR2();
	SNode *getPTR3();
	SNode *getNext();
	std::vector<SNode *> &getArgs();
	symbolNode *getEntry();
	symbolNode *getTable();
	int getNodeType();
	typeNode *getReturnType();


	// Setter Functions
	void setPTR1(SNode *ptr);
	void setPTR2(SNode *ptr);
	void setPTR3(SNode *ptr);
	void setNext(SNode *ptr);
	void setArgs(std::vector<SNode *> &arglist);
	void setTable(symbolNode *ptr);
	void setEntry(symbolNode *ptr);
	void setReturnType(typeNode *type);
	void setNodeType(int nodetype);


	// Returns Number of object currently in Memory
	static int getCount();
};

#define YYSTYPE SNode*

#endif // SYNTAXTREE_H
