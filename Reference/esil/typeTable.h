#ifndef TYPETABLE_H
#define TYPETABLE_H

#include<string>

#define deb std::cout<<__FILE__<<","<<__LINE__<<"\n"
#define val(x) std::cout<<#x"="<<x<<"\n"


class typeNode {
	std::string TYPE_NAME;	// Name of the Data Type
	typeNode *ENTRY;
	typeNode *NEXT;
	bool isDefinition;
	int INDEX;
	static int count;
  public:
	// Constructor
	typeNode(std::string name);

	// Destructor
	~typeNode();

	//
	typeNode *install(std::string name, typeNode *structure);
	typeNode *lookUp(std::string name);
	void print();

	// Getter Functions
	std::string getTypeName();
	typeNode *getNext();
	typeNode *getEntry();
	int getIndex();
	
	// Setter Functions
	void setNext(typeNode *next);
	void setEntry(typeNode *entry);
	void setIndex(int index);
	
	// Function to Return total Number of object currently in Memory
	static int getCount();
};

extern typeNode *integer, *boolean, *reference, *_error;

#endif // SYMBOLTABLE_H
