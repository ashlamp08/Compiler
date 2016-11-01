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

void SNode::init() {
	NODETYPE = lineNo = colNo = -1;
	VALUE = 0;
	TYPE = nullptr;
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
	if (NODETYPE == FUNC && table) delete table;
	for (SNode *i : ARGLIST)
		if (i != nullptr)
			delete i;
	count--;
}

// Getter Functions 
SNode *SNode::getPTR1() {return PTR1;}
SNode *SNode::getPTR2() {return PTR2;}
SNode *SNode::getPTR3() {return PTR3;}
SNode *SNode::getNext() {return next;}
std::vector<SNode *> &SNode::getArgs() {return ARGLIST;}

symbolNode *SNode::getTable() {return table;}
symbolNode *SNode::getEntry() {return entry;}

int SNode::getNodeType() {return NODETYPE;}
typeNode *SNode::getReturnType() {return TYPE;}

int SNode::getValue() {return VALUE;}
std::string SNode::getName() {return NAME;}

int SNode::getCount() {return count;}


// Setter Functions 
void SNode::setPTR1(SNode *ptr) {PTR1 = ptr;}
void SNode::setPTR2(SNode *ptr) {PTR2 = ptr;}
void SNode::setPTR3(SNode *ptr) {PTR3 = ptr;}
void SNode::setNext(SNode *ptr) {next = ptr;}
void SNode::setArgs(std::vector<SNode *> &arglist) {ARGLIST.swap(arglist);}

void SNode::setTable(symbolNode *ptr) {table = ptr;}
void SNode::setEntry(symbolNode *ptr) {entry = ptr;}

void SNode::setReturnType(typeNode *type) {TYPE = type;}
void SNode::setNodeType(int type) {NODETYPE = type;}

std::string SNode::to_string() {
	std::string str;
	if (NODETYPE == ID)
		if (entry != nullptr)
			str = "<ID," + std::to_string((unsigned long long)entry) + "," + NAME;
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
	if(TYPE)
		str += ","+TYPE->getTypeName();
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
		if (i->entry && i->entry->getArgs().size() > 0) {
			std::cout << str3 << "\tArguments:\n";
			for (symbolNode *arg : i->entry->getArgs())
				std::cout << str3 + "\t" + Down << arg->to_string() << "\n";
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

int SNode::typeCheck() {
	int check = PASS;
	for (SNode *i = this; i != nullptr; i = i->next) {
		check = std::min(check, typeCheck(i));
	}
	return check;
}
int SNode::typeCheck(SNode *x) {
	//std::cout<<"Entering typeCheck with"<<x->to_string()<<"\n";
	switch (x->NODETYPE) {

		//
		//	CONSTRUCTS WITH MEMORY ACCESS
		//
		case ID: {
				symbolNode *entry = x->getEntry();
//				val(getUsageType(entry));
				switch (getUsageType(entry)) {
					case FUNCTION: {
							int size = x->getArgs().size();
							int check = PASS;
							for (int i = 0; i < size; i++) {
								SNode *actualArg = x->getArgs()[i];
								symbolNode *formalArg = entry->getArgs()[i];
								check = std::min(check, typeCheck(actualArg));
								if (actualArg->getReturnType() != formalArg->getType() && formalArg->getType()) {
									error("Mismatch in Argument Type at " + std::to_string(i + 1) + "th argument\n\tType Declared:" + formalArg->getType()->getTypeName() + "\tType Passed:" + actualArg->getReturnType()->getTypeName(), actualArg->lineNo, actualArg->colNo);
									return FAIL;
								}
								if (formalArg->isPassedByReference() && (actualArg->getNodeType() != ID || getUsageType(actualArg->getEntry()) == FUNCTION)) {
									error("Argument Declared to be Passed by Reference, Invalid Argument Passed", actualArg->lineNo, actualArg->colNo);
									return FAIL;
								}
							}
							return check;
							break;
						}
					case ARRAY: {
							int check = typeCheck(x->getPTR1());
							if (x->getPTR1()->getReturnType() != integer) {
								error("Index has to be integer", x->lineNo, x->colNo);
								return FAIL;
							}
							else
								return check;
							break;
						}
					case VARIABLE: {
							return PASS;
							break;
						}
					default:	return FAIL;
				}
			}
		case READ: {
				SNode *y = x->getPTR2();
				if (y->getReturnType() != integer) {
					error("Only Integer Can be Read", y->lineNo, y->colNo);
					return FAIL;
				}
				if (y->getPTR1() == nullptr)
					return PASS;
				else {
					int check = typeCheck(y->getPTR1());
					if (y->getPTR1()->getReturnType() != integer) {
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
				if (X->getReturnType() != Y->getReturnType() && Y->getReturnType()) {
					std::string name = X->getName();
					for (SNode *i = X->getPTR2(); i; i = i->getPTR2())
						name.append("." + i->getName());
					error("'" + name + "' is of type '"+X->getReturnType()->getTypeName()+"', Assigning "+Y->getName()+" ("+Y->getReturnType()->getTypeName()+")", Y->lineNo, Y->colNo);
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
				if (x->getPTR2()->getReturnType() != integer) {
					error("Only Integer Values can be printed", x->lineNo, x->colNo);
					return FAIL;
				}
				return check;
				break;
			}
		case IF: {
				int check = typeCheck(x->getPTR1());
				if (x->getPTR1()->getReturnType() != boolean) {
					error("Condition should be a Logical Expression", x->lineNo, x->colNo);
					return FAIL;
				}
				if(x->getPTR2())
					check = std::min(check, x->getPTR2()->typeCheck());
				if(x->getPTR3())
					check = std::min(check, x->getPTR3()->typeCheck());
				return check;
				break;
			}
		case WHILE: {
				int check = typeCheck(x->getPTR1());
				if (x->getPTR1()->getReturnType() != boolean) {
					error("Condition should be a Logical Expression", x->lineNo, x->colNo);
					return FAIL;
				}
				if(x->getPTR2())
					check = std::min(check, x->getPTR2()->typeCheck());
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
		case NUM:
				return PASS;
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
				if (X->getReturnType() == boolean) {
					error("'" + X->getName() + "' is of type Boolean, needed Integer", X->lineNo, X->colNo);
					return FAIL;
				}
				if (Y->getReturnType() == boolean) {
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
				if (X->getReturnType() == integer) {
					error("'" + X->getName() + "' is of type Integer, needed Boolean", X->lineNo, X->colNo);
					return FAIL;
				}
				if (Y->getReturnType() == integer) {
					error("'" + Y->getName() + "' is of type Integer, needed Boolean", Y->lineNo, Y->colNo);
					return FAIL;
				}
				return std::min(check1, check2);;
			}
		case NOT: {
				int check = typeCheck(x->getPTR1());
				if (x->getPTR1()->getReturnType() == integer) {
					error("'" + x->getPTR1()->getName() + "' is of type Integer, needed Boolean", x->lineNo, x->colNo);
					return FAIL;
				}
				return check;
			}
	}
	return PASS;
}

