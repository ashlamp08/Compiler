#ifndef SYNTAXTREE_H
#define SYNTAXTREE_H

#include "symbolTable.h"
#include <string>

class SNode {
						// this field should carry following information:
	int NODETYPE;		// a) operator : (+,*,/ etc.) for expressions
						// b) statement Type : (WHILE, READ etc.) for statements */
	
	int TYPE;			// Integer, Boolean
	
	std::string NAME; 	// For Identifiers/Functions

	int VALUE; 			// for constants
	SNode *ArgList; 	// List of arguments for functions
	
	SNode *PTR1, *PTR2, *PTR3;
	SNode *next;
	
	symbolNode *table;
	symbolNode *entry;
	
	static int count;
	
	
	void print(SNode *bst, std::string str, int side);
	/* Maximum of three subtrees (3 required for IF THEN ELSE */
	int execute(SNode *bst);
	int execute();
	void assignSpace(symbolNode *table);
	void deassignSpace(symbolNode *table);
	void runStatements();
  public:
	SNode(int nodetype);							//
	SNode(int nodetype, int value);					// Constructors
	SNode(int nodetype, const std::string &name);	//
	
	~SNode();						// Destructor

	SNode *getPTR1();				//
	SNode *getPTR2();				//
	SNode *getPTR3();				// Getters
	SNode *getNext();				//	
	symbolNode *getTable();				//	
	symbolNode *getEntry();				//	
	int getNodeType();				//
	int getType();				//
	int getValue();					//
	std::string getName();			//
	static int getCount();

	void setPTR1(SNode *ptr);		//
	void setPTR2(SNode *ptr);		//	Setters
	void setPTR3(SNode *ptr);		//	
	void setNext(SNode *ptr);		//
	void setTable(symbolNode *ptr);		//
	void setEntry(symbolNode *ptr);		//
	void setType(int type);		//
	
	void print();
	int run();
	std::string to_string();
};

#define YYSTYPE SNode*

#endif // SYNTAXTREE_H