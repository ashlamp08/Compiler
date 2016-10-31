#include "syntaxTree.h"
#include <iostream>
#include "Interpreter.hpp"
#include <cmath>

#ifdef __linux__
char leftUp[] = {'\t', 0};
char leftDown[] = "\xe2\x94\x82\t";
char rightUp[] = "\xe2\x94\x82\t";
char rightDown[] = {'\t', 0};
char Up[] = "\xe2\x94\x8c\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80";//{ -38, -60, -60, -60, -60, -60, -60, -60, 0};
char Down[] = "\xe2\x94\x94\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80";//{ -64, -60, -60, -60, -60, -60, -60, -60, 0};
#elif _WIN32
char leftUp[] = {'\t', 0};
char leftDown[] = { -77, '\t', 0};
char rightUp[] = { -77, '\t', 0};
char rightDown[] = {'\t', 0};
char Up[] = { -38, -60, -60, -60, -60, -60, -60, -60, 0};
char Down[] = { -64, -60, -60, -60, -60, -60, -60, -60, 0};
#endif

int Memory[26] = {0};
bool used[26] = {false};
int SNode::count = 0;

SNode::SNode(int nodetype) {
	NODETYPE = nodetype;
	NAME = "";
	VALUE = 0;
	PTR1 = PTR2 = prev = nullptr;
	count++;
//	std::cout << "Object Created" << to_string() << "\n";
}
SNode::SNode(int nodetype, int value) {
	NODETYPE = nodetype;
	NAME = "";
	VALUE = value;
	PTR1 = PTR2 = prev = nullptr;
	count++;
//	std::cout << "Object Created" << to_string() << "\n";
}
SNode::SNode(int nodetype, const std::string &name) {
	NODETYPE = nodetype;
	NAME = name;
	VALUE = 0;
	PTR1 = PTR2 = prev = nullptr;
	count++;
//	std::cout << "Object Created" << to_string() << "\n";
}

SNode::~SNode() {
	if (PTR1)	delete PTR1;
	if (PTR2)	delete PTR2;
	if (prev)	delete prev;
	count--;
//	std::cout << "Object Destroyed" << to_string() << "\n";
}

SNode *SNode::getPTR1() {
	return PTR1;
}
SNode *SNode::getPTR2() {
	return PTR2;
}
SNode *SNode::getPrev() {
	return prev;
}
int SNode::getNodeType() {
	return NODETYPE;
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
void SNode::setPrev(SNode *ptr) {
	prev = ptr;
}
std::string SNode::to_string() {
	if (NODETYPE == ID)
		return "<ID," + std::string(1, (char)('a' + VALUE)) + ">";
	if (NODETYPE == NUM)
		return "<NUM," + std::to_string(VALUE) + ">";
	if (NODETYPE == READ)
		return "<read, >";
	if (NODETYPE == START)
		return "<start, >";
	if (NODETYPE == END)
		return "<end, >";
	if (NODETYPE == WRITE)
		return "<write, >";
	else
		return "<OP," + std::string(1, (char)NODETYPE) + ">";
}
void SNode::print() {
	if (this->prev != nullptr)
		this->prev->print();
	print(this->PTR1, "", 0);
	std::cout << this->to_string() << "\n";
	print(this->PTR2, "", 1);
}
void SNode::print(SNode *x, std::string str, int side) {
	if (x == nullptr)
		return;
	if (side % 2) {
		print(x->PTR1, str + rightUp, 0);
		std::cout << str << Down << x->to_string() << "\n";
		print(x->PTR2, str + rightDown, 1);
	}
	else {
		print(x->PTR1, str + leftUp, 0);
		std::cout << str << Up << x->to_string() << "\n";
		print(x->PTR2, str + leftDown, 1);
	}
}

int SNode::execute() {
	if (this->prev != nullptr)
		this->prev->execute();
	return this->execute(this);
}

int SNode::execute(SNode *x) {
	switch (x->NODETYPE) {
		case ID: {
				return Memory[x->VALUE];
			}
		case NUM: {
				return x->VALUE;
			}
		case READ: {
				SNode *y = x->getPTR2();
				std::cout << "Enter value for " << (char)('a' + y->VALUE) << "\n";
				std::cin >> Memory[y->VALUE];
				break;
			}
		case WRITE: {
				std::cout << "Output: " << execute(x->getPTR2()) << "\n";
				break;
			}
		case '=': {
				SNode *y = x->getPTR1();
				Memory[y->VALUE] = execute(x->getPTR2());
				break;
			}
		case '+':
			return x->getPTR1()->execute() + x->getPTR2()->execute();
		case '-':
			return x->getPTR1()->execute() - x->getPTR2()->execute();
		case '*':
			return x->getPTR1()->execute() * x->getPTR2()->execute();
		case '/':
			return x->getPTR1()->execute() / x->getPTR2()->execute();
		case '^':
			return pow(x->getPTR1()->execute(), x->getPTR2()->execute());
	}
	return 1;
}
int SNode::getCount(){
	return count;
}
//int main() {
//	return 0;/
//}
void printHex(int a){
	std::cout<<std::hex<<a;
	std::cout<<std::dec<<"\n";	
}

bool SNode::getUsed(int index){
	return used[index];
}
void SNode::setUsed(int index){
	used[index] = true;
}