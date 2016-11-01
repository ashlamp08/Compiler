#ifndef SYNTAXTREE_H
#define SYNTAXTREE_H

#include <string>

class SNode {
	// this field should carry following information:
	int NODETYPE;		// a) operator : (+,*,/ etc.) for expressions
	// b) statement Type : (WHILE, READ etc.) for statements */

	std::string NAME; 	// For Identifiers/Functions

	int VALUE; 			// for constants

	SNode *PTR1, *PTR2;
	SNode *prev;
	
	static int count;
	
	void print(SNode *bst, std::string str, int side);
	/* Maximum of three subtrees (3 required for IF THEN ELSE */
	int execute(SNode *bst);
	
  public:
	SNode(int nodetype);							//
	SNode(int nodetype, int value);					// Constructors
	SNode(int nodetype, const std::string &name);	//
	
	~SNode();						// Destructor

	SNode *getPTR1();				//
	SNode *getPTR2();				//
	SNode *getPrev();				//	Getters
	int getNodeType();				//
	int getValue();					//
	std::string getName();			//
	static int getCount();

	void setPTR1(SNode *ptr);		//
	void setPTR2(SNode *ptr);		//	Setters
	void setPrev(SNode *ptr);		//
	
	void print();
	int execute();
	std::string to_string();
};

#define YYSTYPE SNode*

#endif // SYNTAXTREE_H