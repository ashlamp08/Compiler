#include "symbolTable.h"
#include <iostream>
#include "compiler.hpp"

int symbolNode::count = 0;
extern char Pass[];
extern char Down[];

/** Symbol Table Entry is required for variables, arrays and functions**/
symbolNode::symbolNode(std::string name, int type) {
	NAME = name;
	TYPE = type;
	SIZE = -1;
	BINDING = -1;
	NEXT = nullptr;
	global = false;
	count++;
//	std::cout <<to_string()<< "\tCreated" << "\n";
}
symbolNode::~symbolNode() {
//	std::cout <<to_string()<< "\tDestroyed" << "\n";
	for (symbolNode *i : ARGLIST)
		if (i != nullptr)
			delete i;
	if (NEXT != nullptr)
		delete NEXT;
	count--;
}
symbolNode *symbolNode::install(std::string name, int type, int size) {
	symbolNode *last = this;
	for (symbolNode *i = this->NEXT; i != nullptr; i = i->NEXT) {
		if (name.compare(i->NAME) == 0)
			return nullptr;
		last = i;
	}
	symbolNode *temp = new symbolNode(name, type);
	if (size != -1)
		temp->setSize(size);
	last->NEXT = temp;
	return temp;
}
symbolNode *symbolNode::lookUp(std::string name) {
	for (symbolNode *i = this->NEXT; i != nullptr; i = i->NEXT) {
		if (name.compare(i->NAME) == 0)
			return i;
	}
	return nullptr;
}
std::string symbolNode::to_string() {
	std::string str = std::to_string((unsigned long long)this) + ":<" + NAME;
	if (TYPE == INTEGER)
		str += ",int";
	else if (TYPE == BOOLEAN)
		str += ",bool";
	if (global)
		str += ",g";
	str += ","+std::to_string(BINDING);
	if (SIZE > 0)
		str += "," + std::to_string(SIZE);
	else if (SIZE == -2) {
		str += ",FUNC";
		for (auto i : ARGLIST) {
			str += "," + i->to_string();
		}
	}
	return str + ">";
}
void symbolNode::print(std::string str) {
	std::cout << str << "Declerations:\n";
	for (symbolNode *i = this; i != nullptr; i = i->NEXT)
		if (i->NEXT)
			std::cout << str << Pass << i->to_string() << "\n";
		else
			std::cout << str << Down << i->to_string() << "\n";
	val(ARGLIST.size());
	if (ARGLIST.size() > 0) {
		std::cout << str << "Argumenents:\n";
		for (int i = 0; i < (int)ARGLIST.size() - 1; i++)
			std::cout << str << Pass << ARGLIST[i]->to_string() << "\n";

		std::cout << str << Down << ARGLIST.back()->to_string() << "\n";
	}
}
void symbolNode::setSize(int size) {
	SIZE = size;
}
std::string symbolNode::getName() {
	return NAME;
}
int symbolNode::getSize() {
	return SIZE;
}
int symbolNode::getType() {
	return TYPE;
}
int symbolNode::getCount() {
	return count;
}
symbolNode *symbolNode::getNext() {
	return NEXT;
}
void symbolNode::setBinding(int bind) {
	BINDING = bind;
}
int symbolNode::getBinding() {
	return BINDING;
}
void symbolNode::setArgs(std::vector<symbolNode *> &arglist) {
	SIZE = -2;
	ARGLIST.swap(arglist);
	int size = ARGLIST.size();
	for(int i=0;i<size;i++)
		ARGLIST[i]->setBinding(i-2-size);
}
std::vector<symbolNode *> &symbolNode::getArgs() {
	return ARGLIST;
}
void symbolNode::setAsGlobal(){
	global = true;
}
bool symbolNode::isGlobal(){
	return global;
}
