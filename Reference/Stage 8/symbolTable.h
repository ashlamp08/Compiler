#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H


#include <string>
#include <vector>
#define deb ;//std::cout<<__FILE__<<","<<__LINE__<<"\n"
#define val(x) std::cout<<#x"="<<x<<"\n"

/* Sample Global and Local Symbol Table Structure */
/** Symbol Table Entry is required for variables, arrays and functions**/
class symbolNode {
	std::string NAME; // Name of the Identifier
	
	int TYPE; // TYPE can be INTEGER or BOOLEAN
	
	int SIZE; // Size field for arrays
	
	
	int BINDING; // Address of the Identifier in Memory
	std::vector<symbolNode*> ARGLIST; // Argument List for functions
	
	symbolNode *NEXT; // Pointer to next Symbol Table Entry */
	
	static int count;
	
	public:
	symbolNode(std::string name, int type);
	~symbolNode();
	symbolNode *install(std::string name, int type);
	symbolNode *install(std::string name, int type, int size);
	symbolNode *lookUp(std::string name);
	void setSize(int size);
	int getSize();
	int getType();
	void setBinding(int bind);
	int getBinding();
	symbolNode *getNext();
	std::string to_string();
	void print();
	
	static int getCount();
};

#endif // SYMBOLTABLE_H