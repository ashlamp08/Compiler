#include "typeTable.h"
#include <iostream>
int typeNode::count = 0;
typeNode::typeNode(std::string name) {
	TYPE_NAME = name;
	ENTRY = nullptr;
	NEXT = nullptr;
	INDEX = -1;
}

// Destructor
typeNode::~typeNode() {
	if (isDefinition)
		delete ENTRY;
}

//
typeNode *typeNode::install(std::string name, typeNode *structure) {
	typeNode *last = this;
	for (typeNode *i = this->NEXT; i != nullptr; i = i->NEXT) {
		if (name.compare(i->TYPE_NAME) == 0)
			return nullptr;
		last = i;
	}
	typeNode *temp = new typeNode(name);
	temp->ENTRY = structure;
	temp->isDefinition = true;
	last->NEXT = temp;
	return temp;
}
typeNode *typeNode::lookUp(std::string name) {
	for (typeNode *i = this; i != nullptr; i = i->NEXT) {
		if (name.compare(i->TYPE_NAME) == 0)
			return i;
	}
	return nullptr;
}
void typeNode::print() {
	std::cout << "Valid Data Types:\n";
	for (typeNode *i = this; i != nullptr; i = i->NEXT) {
		std::cout <<i<<":"<<i->TYPE_NAME;
		if (i->ENTRY) {
			std::cout << ":\t{";
			for (typeNode *j = i->ENTRY; j != nullptr; j = j->NEXT)
				std::cout <<j<<":"<<j->INDEX<<":("<< j->ENTRY<<":"<<j->ENTRY->TYPE_NAME << ") " << j->TYPE_NAME << ((j->NEXT) ? ',' : '}');
		}
		std::cout << '\n';
	}
}

// Getter Functions
std::string typeNode::getTypeName() {return TYPE_NAME;}
typeNode *typeNode::getNext() {return NEXT;}
typeNode *typeNode::getEntry() {return ENTRY;}
int typeNode::getIndex() {return INDEX;}

// Setter Functions
void typeNode::setNext(typeNode *next) {NEXT = next;}
void typeNode::setEntry(typeNode *entry) {ENTRY = entry;}
void typeNode::setIndex(int index) {INDEX = index;}

// Function to Return total Number of object currently in Memory
int typeNode::getCount() {return count;}