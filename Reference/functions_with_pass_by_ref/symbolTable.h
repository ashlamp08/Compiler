#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H


#include <string>
#include <vector>
#define deb std::cout<<__FILE__<<","<<__LINE__<<"\n"
#define val(x) std::cout<<#x"="<<x<<"\n"

class symbolNode {
	std::string NAME; 	// Name of the Identifier

	int TYPE; 			// Data Type (INTEGER , BOOLEAN)

	int SIZE; 			// -1 == Variable
						// -2 == Function
						// else	 Array

	int BINDING; 		// Address of the Identifier in Memory
						
						// Argument List for functions
	std::vector<symbolNode *> ARGLIST; 

	symbolNode *NEXT; 	// Pointer to next Symbol Table Entry

	bool global;		// TRUE for global Variables

	bool passedByRef;	// TRUE if Argument Passed By Reference

	static int count;	// Number of object currently in Memory

  public:
	// Constructor
	symbolNode(std::string name, int type);
	
	// Destructor
	~symbolNode();
	
	// 
	symbolNode *install(std::string name, int type, int size = -1);
	symbolNode *lookUp(std::string name);
	void print(std::string str = "");
	std::string to_string();

	// Getter Functions
	std::vector<symbolNode *> &getArgs();
	int getBinding();
	std::string getName();
	symbolNode *getNext();
	int getSize();
	int getType();
	bool isGlobal();
	bool isPassedByReference();
	
	// Setter Functions
	void setArgs(std::vector<symbolNode *> &arglist);
	void setAsGlobal();
	void setAsPassByReference();
	void setBinding(int bind);
	void setSize(int size);
	
	// Function to Return total Number of object currently in Memory
	static int getCount();
};

#endif // SYMBOLTABLE_H
