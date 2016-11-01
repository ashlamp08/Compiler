#include "symbolTable.h"
#include "compiler.hpp"
#include <iostream>

int symbolNode::count = 0;
extern char Pass[];
extern char Down[];

symbolNode::symbolNode(std::string name, typeNode *type) {
	NAME = name;
	TYPE = type;
	SIZE = -1;
	BINDING = -1;
	NEXT = nullptr;
	global = false;
	passedByRef = false;
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

symbolNode *symbolNode::install(std::string name, typeNode *type, int size) {
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
	if(TYPE)
		str += ","+TYPE->getTypeName();
	if (global)
		str += ",g";
	if (passedByRef)
		str += ",&";
	str += "," + std::to_string(BINDING);
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
	if (ARGLIST.size() > 0) {
		std::cout << str << "Argumenents:\n";
		for (int i = 0; i < (int)ARGLIST.size() - 1; i++)
			std::cout << str << Pass << ARGLIST[i]->to_string() << "\n";

		std::cout << str << Down << ARGLIST.back()->to_string() << "\n";
	}
}

// Getter Functions
std::vector<symbolNode*> &symbolNode::getArgs() {return ARGLIST;}
int symbolNode::getBinding() {return BINDING;}
int symbolNode::getCount() {return count;}
std::string symbolNode::getName() {return NAME;}
symbolNode *symbolNode::getNext() {return NEXT;}
int symbolNode::getSize() {return SIZE;}
typeNode *symbolNode::getType() {return TYPE;}
bool symbolNode::isGlobal() {return global;}
bool symbolNode::isPassedByReference() {return passedByRef;}

// Setter Functions
void symbolNode::setAsGlobal()			{global = true;}
void symbolNode::setAsPassByReference()	{passedByRef = true;}
void symbolNode::setBinding(int bind)	{BINDING = bind;}
void symbolNode::setSize(int size)		{SIZE = size;}

void symbolNode::setArgs(std::vector<symbolNode *> &arglist) {
	SIZE = -2;
	ARGLIST.swap(arglist);
	int size = ARGLIST.size();
	for (int i = 0; i < size; i++)
		ARGLIST[i]->setBinding(i - 2 - size);
}


