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
	count++;
}
symbolNode::~symbolNode() {
	for (symbolNode *i : ARGLIST)
		if (i != nullptr)
			delete i;
	if (NEXT != nullptr)
		delete NEXT;
	count--;
}
symbolNode *symbolNode::install(std::string name, int type) {
	symbolNode *last = this;
	for (symbolNode *i = this->NEXT; i != nullptr; i = i->NEXT) {
		if (name.compare(i->NAME) == 0)
			return nullptr;
		last = i;
	}
	symbolNode *temp = new symbolNode(name, type);
	last->NEXT = temp;
	return temp;
}
symbolNode *symbolNode::install(std::string name, int type, int size) {
	symbolNode *last = this;
	for (symbolNode *i = this->NEXT; i != nullptr; i = i->NEXT) {
		if (name.compare(i->NAME) == 0)
			return nullptr;
		last = i;
	}
	symbolNode *temp = new symbolNode(name, type);
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
	std::string str = "<" + NAME;
	if (TYPE == INTEGER)
		str += ",int";
	else if (TYPE == BOOLEAN)
		str += ",bool";
	if (SIZE > 0)
		str += "," + std::to_string(SIZE);
	return str + ">";
}
void symbolNode::print() {
	for (symbolNode *i = this; i != nullptr; i = i->NEXT)
		if(i->NEXT)
			std::cout << Pass << i->to_string() << "\n";
		else
			std::cout << Down << i->to_string() << "\n";
}
void symbolNode::setSize(int size) {
	SIZE = size;
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
symbolNode *symbolNode::getNext(){
	return NEXT;
}
void symbolNode::setBinding(int bind){
	BINDING = bind;
}
int symbolNode::getBinding(){
	return BINDING;
}
