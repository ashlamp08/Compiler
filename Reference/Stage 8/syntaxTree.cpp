#include <iostream>
#include <vector>
#include <stack>
#include <cmath>
#include "syntaxTree.h"
#include "compiler.hpp"

#ifdef __linux__
char leftUp[] = {'\t', 0};
char leftDown[] = "\xe2\x94\x82\t";
char rightUp[] = "\xe2\x94\x82\t";
char rightDown[] = {'\t', 0};
char Up[] = "\xe2\x94\x8c\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80";//{ -38, -60, -60, -60, -60, -60, -60, -60, 0};
char Down[] = "\xe2\x94\x94\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80";//{ -64, -60, -60, -60, -60, -60, -60, -60, 0};
#elif _WIN32
char leftUp[] = {'\t', 0};
char leftDown[] = { -77, '\t', 0};									//│
char rightUp[] = { -77, '\t', 0};									//│
char rightDown[] = {'\t', 0};
char Up[] = { -38, -60, -60, -60, -60, -60, -60, -60, 0};			//┌───────
char Down[] = { -64, -60, -60, -60, -60, -60, -60, -60, 0};			//└───────
char Pass[] = { -61, -60, -60, -60, -60, -60, -60, -60, 0};			//├───────
#endif

int SNode::count = 0;

std::vector<int> STACK;

SNode::SNode(int nodetype) {
	NODETYPE = nodetype;
	NAME = "";
	VALUE = 0;
	TYPE = -1;
	PTR1 = PTR2 = PTR3 = next = nullptr;
	table = nullptr;
	count++;
//	std::cout << to_string() << "Created" << "\n";
}
SNode::SNode(int nodetype, int value) {
	NODETYPE = nodetype;
	NAME = "";
	VALUE = value;
	TYPE = -1;
	PTR1 = PTR2 = PTR3 = next = nullptr;
	table = entry = nullptr;
	count++;
//	std::cout << to_string() << "Created" << "\n";
}
SNode::SNode(int nodetype, const std::string &name) {
	NODETYPE = nodetype;
	NAME = name;
	VALUE = 0;
	TYPE = -1;
	PTR1 = PTR2 = PTR3 = next = nullptr;
	table = entry = nullptr;
	count++;
//	std::cout << to_string() << "Created" << "\n";
}

SNode::~SNode() {
	if (PTR1)	delete PTR1;
	if (PTR2)	delete PTR2;
	if (PTR3)	delete PTR3;
	if (next)	delete next;
//	std::cout << to_string() << "Destroyed" << "\n";
	count--;
}

SNode *SNode::getPTR1() {
	return PTR1;
}
SNode *SNode::getPTR2() {
	return PTR2;
}
SNode *SNode::getPTR3() {
	return PTR3;
}
SNode *SNode::getNext() {
	return next;
}
symbolNode *SNode::getTable() {
	return table;
}
symbolNode *SNode::getEntry() {
	return entry;
}
int SNode::getNodeType() {
	return NODETYPE;
}
int SNode::getType() {
	return TYPE;
}
int SNode::getValue() {
	return VALUE;
}
std::string SNode::getName() {
	return NAME;
}

void SNode::setPTR1(SNode *ptr) {
	PTR1 = ptr;
}
void SNode::setPTR2(SNode *ptr) {
	PTR2 = ptr;
}
void SNode::setPTR3(SNode *ptr) {
	PTR3 = ptr;
}
void SNode::setNext(SNode *ptr) {
	next = ptr;
}
void SNode::setTable(symbolNode *ptr) {
	table = ptr;
}
void SNode::setEntry(symbolNode *ptr) {
	entry = ptr;
}
std::string SNode::to_string() {
	std::string str;
	if (NODETYPE == ID)
		if (entry != nullptr)
			str = "<ID," + entry->to_string();
		else
			str = "<ID," + NAME;
	else if (NODETYPE == NUM)
		str = "<NUM," + std::to_string(VALUE);
	else if (NODETYPE == READ)
		str = "<read";
	else if (NODETYPE == START)
		str = "<start";
	else if (NODETYPE == END)
		str = "<end";
	else if (NODETYPE == WRITE)
		str = "<write";
	else if (NODETYPE == IF)
		str = "<if";
	else if (NODETYPE == THEN)
		str = "<then";
	else if (NODETYPE == ENDIF)
		str = "<endif";
	else if (NODETYPE == WHILE)
		str = "<while";
	else if (NODETYPE == DO)
		str = "<do";
	else if (NODETYPE == ENDWHILE)
		str = "<endwhile";
	else if (NODETYPE == STARTDECL)
		str = "<decl";
	else if (NODETYPE == ENDDECL)
		str = "<enddecl";
	else if (NODETYPE == ISEQ)
		str = "<==";
	else if (NODETYPE == NOTEQ)
		str = "<!=";
	else if (NODETYPE == INTEGER)
		str = "<int";
	else if (NODETYPE == BOOLEAN)
		str = "<bool";
	else str = "<OP," + std::string(1, (char)NODETYPE);
	if (TYPE == INTEGER)
		return str + ",int>";
	else if (TYPE == BOOLEAN)
		return str + ",bool>";
	else
		return str + ">";
}
void SNode::print() {
	if (table != nullptr) {
		std::cout << "Declarations:\n";
		table->print();
	}
	std::cout << "Code:\n";
	print(this, "", 0);
	/*for (SNode *i = this; i != nullptr; i = i->next) {
	print(i->PTR1, leftDown, 0);
	if (i->next != nullptr) {
	std::cout << Pass << i->to_string() << "\n";
	print(i->PTR2, leftDown, 1);
	}
	else {
	std::cout << Down << i->to_string() << "\n";
	print(i->PTR2, "\t", 1);
	}
	}*/
}
void SNode::print(SNode *x, std::string str, int side) {
	if (x == nullptr)
		return;
	for (SNode *i = x; i != nullptr; i = i->next) {
		if (i->next != nullptr) {
			print(i->PTR1, str + leftDown, 1);
			std::cout << str + Pass << i->to_string() << "\n";
			print(i->PTR2, str + leftDown, 0);
			if (i->PTR3) {
//				print(i->PTR2, str+leftDown, 0);
				print(i->PTR3, str + leftDown, 0);
			}
		}
		else {
			if (side % 2) {
				print(i->PTR1, str + "\t", 1);
				std::cout << str + Up << i->to_string() << "\n";
				print(i->PTR2, str + leftDown, 0);
				if (i->PTR3)
					print(i->PTR3, str + leftDown, 0);
			}
			else {
				print(i->PTR1, str + leftDown, 1);
				std::cout << str + Down << i->to_string() << "\n";
				print(i->PTR2, str + "\t", 0);
				if (i->PTR3)
					print(i->PTR3, str + "\t", 0);
			}
		}
	}
	/*if (side % 2) {
	for (SNode *i = x; i != nullptr; i = i->next) {
	print(i->PTR1, str+rightUp, 0);
	if (i->next != nullptr) {
	std::cout << str + Pass << i->to_string() << "\n";
	print(i->PTR2, str+leftDown, 1);
	}
	else {
	std::cout << str + Down << i->to_string() << "\n";
	print(i->PTR2, str+rightDown, 1);
	}
	// print(i->PTR1, str + rightUp, 0);
	// std::cout << str << Down << i->to_string() << "\n";
	// print(i->PTR2, str + rightDown, 1);
	}
	}
	else {
	for (SNode *i = x; i != nullptr; i = i->next) {
	print(i->PTR1, str+leftDown, 0);
	if (i->next != nullptr) {
	std::cout << str + Pass << i->to_string() << "\n";
	print(i->PTR2, str+leftUp, 1);
	}
	else {
	std::cout << str + Up << i->to_string() << "\n";
	print(i->PTR2, str+leftDown, 1);
	}
	// print(i->PTR1, str + leftUp, 0);
	// std::cout << str << Up << i->to_string() << "\n";
	// print(i->PTR2, str + leftDown, 1);
	}
	}*/
}
void SNode::runStatements() {
	for (SNode *i = this; i != nullptr; i = i->next) {
		execute(i);
	}
}
int SNode::run() {
	assignSpace(table);
	this->runStatements();
	deassignSpace(table);
	return 0;
}

int SNode::execute() {
	return this->execute(this);
}

int SNode::execute(SNode *x) {
	switch (x->NODETYPE) {

//
//	CONSTRUCTS WITH MEMORY ACCESS
//

		case ID: {
				if (x->PTR1 == nullptr)
					return STACK.at(x->entry->getBinding());
				else
					return STACK.at(x->entry->getBinding() + x->PTR1->execute());
			}
		case READ: {
				SNode *y = x->getPTR2();
				if (y->PTR1 == nullptr) {
					std::cout << "Enter value of '" << y->NAME << "'\n";
					std::cin >> STACK.at(y->entry->getBinding());
				}
				else {
					std::cout << "Enter value of '" << y->NAME << "[" << y->PTR1->execute() << "]'\n";
					std::cin >> STACK.at(y->entry->getBinding() + y->PTR1->execute());
				}
				break;
			}
		case '=': {
//				std::cout<<"Assignment\n";
				SNode *y = x->getPTR1();
//			std::cout<<"y="<<y<<"\n";
//			std::cout<<"bind="<<y->entry->getBinding()<<"\n";
				if (y->PTR1 == nullptr)
					STACK.at(y->entry->getBinding()) = execute(x->getPTR2());
				else
					STACK.at(y->entry->getBinding() + y->PTR1->execute()) = execute(x->getPTR2());
//				val(result);
//			std::cout<<"Assignment Over\n";
				break;
			}




//
//	CONSTRUCTS
//

		case WRITE: {
				std::cout << "Output = " << execute(x->getPTR2()) << "\n";
				break;
			}
		case IF: {
				if (x->getPTR1()->execute())
					x->getPTR2()->runStatements();
				else if (x->getPTR3() != nullptr)
					x->getPTR3()->runStatements();
				break;
			}
		case WHILE: {
				while (x->getPTR1()->execute())
					x->getPTR2()->runStatements();
				break;
			}
		case START:
			break;


//
//		CONSTANTS
//
		case NUM: {
				return x->VALUE;
			}
		case TRUE:
			return 1;
		case FALSE:
			return 0;


//
//		EXPRESSIONS
//

		case '+':
			return x->getPTR1()->execute() + x->getPTR2()->execute();
		case '-':
			return x->getPTR1()->execute() - x->getPTR2()->execute();
		case '*':
			return x->getPTR1()->execute() * x->getPTR2()->execute();
		case '/':
			return x->getPTR1()->execute() / x->getPTR2()->execute();
		case '<':
			return x->getPTR1()->execute() < x->getPTR2()->execute();
		case '>':
			return x->getPTR1()->execute() > x->getPTR2()->execute();
		case '^':
			return pow(x->getPTR1()->execute(), x->getPTR2()->execute());
		case LEQ:
			return x->getPTR1()->execute() >= x->getPTR2()->execute();
		case GEQ:
			return x->getPTR1()->execute() <= x->getPTR2()->execute();
		case ISEQ:
			return x->getPTR1()->execute() == x->getPTR2()->execute();
		case NOTEQ:
			return x->getPTR1()->execute() != x->getPTR2()->execute();
		case AND:
			return x->getPTR1()->execute() && x->getPTR2()->execute();
		case OR:
			return x->getPTR1()->execute() || x->getPTR2()->execute();
		case NOT:
			return (x->getPTR1()->execute()) ? 1 : 0;
		default:
			std::cout << "ERROR:\a\a Not Recognized " << x->NODETYPE <<
					  " (char)" << (char)(x->NODETYPE) << "\n";
	}
	return 1;
}
int SNode::getCount() {
	return count;
}
void SNode::setType(int type) {
	TYPE = type;
}
//int main() {
//	return 0;/
//}

void SNode::assignSpace(symbolNode *table) {
	std::cout << "Assign Space Called\n";
	for (symbolNode *i = table->getNext(); i != nullptr; i = i->getNext()) {
		auto it = STACK.end();
		i->setBinding(STACK.size());
		if (i->getSize() == -1)
			STACK.insert(it, 0);
		else
			STACK.insert(it, i->getSize(), 0);
	}
}
void SNode::deassignSpace(symbolNode *table) {
	std::cout << "Deassign space Called\n";
	std::stack<symbolNode *> temp;
	int size = 0;
	for (symbolNode *i = table->getNext(); i != nullptr; i = i->getNext()) {
		i->setBinding(STACK.size());
		if (i->getSize() == -1)
			size++;
		else
			size += i->getSize();
	}
	STACK.resize(STACK.size() - size);
	std::cout << "Deassign space Over\n";
}