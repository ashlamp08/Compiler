#include <iostream>
#include <vector>
#include <stack>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include "syntaxTree.h"
#include "compiler.hpp"
#include "util.h"

#ifdef __linux__
char leftUp[] = {'\t', 0};
char leftDown[] = "\xe2\x94\x82\t";
char rightUp[] = "\xe2\x94\x82\t";
char rightDown[] = {'\t', 0};
char Up[] = "\xe2\x94\x8c\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80";//{ -38, -60, -60, -60, -60, -60, -60, -60, 0};
char Down[] = "\xe2\x94\x94\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80";//{ -64, -60, -60, -60, -60, -60, -60, -60, 0};
char Pass[] = "\xe2\x94\x9c\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80";			//├───────
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

//std::vector<int> STACK;

void SNode::init() {
	NODETYPE = TYPE = lineNo = colNo = -1;
	VALUE = 0;
	PTR1 = PTR2 = PTR3 = next = nullptr;
	table = entry = nullptr;
	NAME = "";
}

SNode::SNode(int nodetype, int l, int c) {
	init();
	NODETYPE = nodetype;
	count++;
	lineNo = l;
	colNo = c;
//	std::cout << lineNo<<","<<colNo<<":"<<to_string() << "Created" << "\n";
}
SNode::SNode(int nodetype, int value, int l, int c) {
	init();
	NODETYPE = nodetype;
	VALUE = value;
	NAME = std::to_string(value);
	count++;
	lineNo = l;
	colNo = c;
//	std::cout << lineNo<<","<<colNo<<":"<< to_string() << "Created" << "\n";
}
SNode::SNode(int nodetype, const std::string &name, int l, int c) {
	init();
	NODETYPE = nodetype;
	NAME = name;
	count++;
	lineNo = l;
	colNo = c;
//	std::cout << lineNo<<","<<colNo<<":"<< to_string() << "Created" << "\n";
}

SNode::~SNode() {
//	std::cout << lineNo<<","<<colNo<<":"<< to_string() << "Destroyed" << "\n";
	if (PTR1)	delete PTR1;
	if (PTR2)	delete PTR2;
	if (PTR3)	delete PTR3;
	if (next)	delete next;
	if (NODETYPE == FUNC && table)  delete table;
	for (SNode *i : ARGLIST)
		if (i != nullptr)
			delete i;
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
int SNode::getReturnType() {
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
			str = "<ID," + std::to_string((unsigned long long)entry);
		else
			str = "<ID," + NAME;
	else if (NODETYPE == FUNC)
		str = "<FUNC," + NAME;
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
	else if (NODETYPE == RETURN)
		str = "<return";
	else if (NODETYPE == ISEQ)
		str = "<==";
	else if (NODETYPE == NOTEQ)
		str = "<!=";
	else if (NODETYPE == INTEGER)
		str = "<int";
	else if (NODETYPE == BOOLEAN)
		str = "<bool";
	else if (NODETYPE == FALSE)
		str = "<false";
	else if (NODETYPE == TRUE)
		str = "<true";
	else str = "<OP," + std::string(1, (char)NODETYPE);
	if (TYPE == INTEGER)
		str += ",int";
	else if (TYPE == BOOLEAN)
		str += ",bool";
	return str + ">";
}
void SNode::print() {
	if (table != nullptr) {
		table->print();
	}
	std::cout << "Code\n";
	print(this->next, "", 0);
}
void SNode::printNode(SNode *i, std::string str1, std::string str2, std::string str3) {
	print(i->PTR1, str1, 1);
	std::cout << str2 << i->to_string() << "\n";
	for (auto arg : i->ARGLIST)
		print(arg, str3, 0);
	if (i->NODETYPE == FUNC) {
		if (i->table) {
			i->table->print(str3 + "\t");
		}
		if (i->entry->getArgs().size() > 0) {
			std::cout << str3 << "\tArguments:\n";
			for (symbolNode *arg : i->entry->getArgs())
				std::cout << str3 +"\t"+Down << arg->to_string() << "\n";
		}
		std::cout << str3 << "Func Code:\n";
		print(i->PTR2, str3 + "\t", 0);
		print(i->PTR3, str3 + "\t", 0);
	}
	else {
		print(i->PTR2, str3, 0);
		print(i->PTR3, str3, 0);
	}
}
void SNode::print(SNode *x, std::string str, int side) {
	if (x == nullptr)
		return;
	for (SNode *i = x; i != nullptr; i = i->next) {
		if (i->next != nullptr)
			printNode(i, str + leftDown, str + Pass, str + leftDown);
		else if (side % 2)
			printNode(i, str + "\t", str + Up, str + leftDown);
		else
			printNode(i, str + leftDown, str + Down, str + "\t");
	}
}
/*void SNode::runStatements() {
	for (SNode *i = this; i != nullptr; i = i->next) {
		//	std::cout<<"Executing "<<i->to_string()<<"\n";
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
//	std::cout<<"Executing "<<x->to_string()<<"\n";
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
}*/
int SNode::getCount() {
	return count;
}
void SNode::setReturnType(int type) {
	TYPE = type;
}
void SNode::setNodeType(int type) {
	NODETYPE = type;
}
//int main() {
//	return 0;/
//}

/*void SNode::assignSpace(symbolNode *table) {
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
}*/
int SNode::typeCheck() {
	int check = PASS;
	for (SNode *i = this; i != nullptr; i = i->next) {
//		val(i->to_string());
		check = std::min(check, typeCheck(i));
	}
	return check;
}
int SNode::typeCheck(SNode *x) {
	switch (x->NODETYPE) {

		//
		//	CONSTRUCTS WITH MEMORY ACCESS
		//

		case ID: {
				if (x->getPTR1() == nullptr)
					return PASS;
				else {
					int check = typeCheck(x->getPTR1());
					if (x->getPTR1()->getReturnType() != INTEGER) {
						error("Index has to be integer", x->lineNo, x->colNo);
						return FAIL;
					}
					else
						return check;
				}
			}
		case READ: {
				SNode *y = x->getPTR2();
				if (y->getReturnType() != INTEGER) {
					error("Only Integer Can be Read", y->lineNo, y->colNo);
					return FAIL;
				}
				if (y->getPTR1() == nullptr)
					return PASS;
				else {
					int check = typeCheck(y->getPTR1());
					if (y->getPTR1()->getReturnType() != INTEGER) {
						error("Index has to be integer", y->lineNo, y->colNo);
						return FAIL;
					}
					else
						return check;
				}
				break;
			}
		case '=': {
				SNode *X = x->getPTR1();
				SNode *Y = x->getPTR2();
				int check1 = typeCheck(X);
				int check2 = typeCheck(Y);
				if (X->getReturnType() == INTEGER && Y->getReturnType() == BOOLEAN) {
					error("'" + Y->getName() + "' is of type Boolean, needed Integer", Y->lineNo, Y->colNo);
					return FAIL;
				}
				if (X->getReturnType() == BOOLEAN && Y->getReturnType() == INTEGER) {
					error("'" + Y->getName() + "' is of type Integer, needed Boolean", Y->lineNo, Y->colNo);
					return FAIL;
				}
				return std::min(check1, check2);
				break;
			}




		//
		//	CONSTRUCTS
		//

		case WRITE: {
				int check = typeCheck(x->getPTR2());
				if (x->getPTR2()->getReturnType() != INTEGER) {
					error("Only Integer Values can be printed", x->lineNo, x->colNo);
					return FAIL;
				}
				return check;
				break;
			}
		case IF: {
				int check = typeCheck(x->getPTR1());
				if (x->getPTR1()->getReturnType() != BOOLEAN) {
					error("Condition should be a Logical Expression", x->lineNo, x->colNo);
					return FAIL;
				}
				return check;
				break;
			}
		case WHILE: {
				int check = typeCheck(x->getPTR1());
				if (x->getPTR1()->getReturnType() != BOOLEAN) {
					error("Condition should be a Logical Expression", x->lineNo, x->colNo);
					return FAIL;
				}
				return check;
				break;
			}
		case START:
			return PASS;
			break;
		case FUNC: {
				return x->getPTR2()->typeCheck();
				break;
			}
		case RETURN: {
				int check = typeCheck(x->getPTR2());
//				val(x->getPTR2()->getReturnType());
//				val(x->getReturnType());
				if (x->getPTR2()->getReturnType() != x->getReturnType()) {
					error("Mismatch in return Value Type", x->getPTR2()->lineNo, x->getPTR2()->colNo);
					return FAIL;
				}
				return check;
				break;
			}


		//
		//		CONSTANTS
		//
		case NUM: {
				return PASS;
				break;
			}
		case TRUE:
			return PASS;
		case FALSE:
			return PASS;


		//
		//		EXPRESSIONS
		//
		case '+':
		case '-':
		case '*':
		case '/':
		case '^':
		case '<':
		case '>':
		case LEQ:
		case GEQ:
		case ISEQ:
		case NOTEQ: {
				SNode *X = x->getPTR1();
				SNode *Y = x->getPTR2();
				int check1 = typeCheck(X);
				int check2 = typeCheck(Y);
				if (X->getReturnType() == BOOLEAN) {
					error("'" + X->getName() + "' is of type Boolean, needed Integer", X->lineNo, X->colNo);
					return FAIL;
				}
				if (Y->getReturnType() == BOOLEAN) {
					error("'" + Y->getName() + "' is of type Boolean, needed Integer", Y->lineNo, Y->colNo);
					return FAIL;
				}
				return std::min(check1, check2);
			}
		case AND:
		case OR: {
				SNode *X = x->getPTR1();
				SNode *Y = x->getPTR2();
				int check1 = typeCheck(X);
				int check2 = typeCheck(Y);
				if (X->getReturnType() == INTEGER) {
					error("'" + X->getName() + "' is of type Integer, needed Boolean", X->lineNo, X->colNo);
					return FAIL;
				}
				if (Y->getReturnType() == INTEGER) {
					error("'" + Y->getName() + "' is of type Integer, needed Boolean", Y->lineNo, Y->colNo);
					return FAIL;
				}
				return std::min(check1, check2);;
			}
		case NOT: {
				int check = typeCheck(x->getPTR1());
				if (x->getPTR1()->getReturnType() == INTEGER) {
					error("'" + x->getPTR1()->getName() + "' is of type Integer, needed Boolean", x->lineNo, x->colNo);
					return FAIL;
				}
				return check;
			}
	}
	return PASS;
}
void SNode::setArgs(std::vector<SNode *> &arglist) {
	ARGLIST.swap(arglist);
}
std::vector<SNode *> &SNode::getArgs() {
	return ARGLIST;
}

