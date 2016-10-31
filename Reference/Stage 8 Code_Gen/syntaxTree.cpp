#include <iostream>
#include <vector>
#include <stack>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include "syntaxTree.h"
#include "compiler.hpp"

#define debug std::string(__FILE__)+std::string(",")+std::to_string(__LINE__)

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

void error (const std::string &s, int l = -1, int c = -1) {
	std::cout << "ERROR: ";
	if (l != -1)
		std::cout << l;
	if (c != -1)
		std::cout << "," << c << ": ";
	else
		std::cout << ": ";
	std::cout << s << "\n";
}

int regNo = 0;

int getReg(const std::string &str="") {
	if (regNo == 8) {
		std::cout << "Error: No Register left. Change your Strategy. "<<str<<"\n";
		exit(1);
	}
	return regNo++;
}

int freeReg(const std::string &str="") {
	if (regNo == 0) {
		std::cout << "Error: You shouldn't be freeing a REG now. Check your Logic. "<<str<<"\n";
		exit(1);
	}
	return regNo--;
}

int getIfLabel(){
	static int label=0;
	if(label<0){
		std::cout << "Error: What are you doing? we are out of If Labels\n";
		exit(1);
	}
	label++;
	return label;
}

int getWhileLabel(){
	static int label=0;
	if(label<0){
		std::cout << "Error: What are you doing? we are out of While Labels\n";
		exit(1);
	}
	label++;
	return label;
}


int SNode::count = 0;

std::vector<int> STACK;

void SNode::init() {
	NODETYPE = TYPE = lineNo = colNo = -1;
	VALUE = 0;
	ArgList = PTR1 = PTR2 = PTR3 = next = nullptr;
	table = entry = nullptr;
	NAME = "";
}

SNode::SNode(int nodetype, int l, int c) {
	init();
	NODETYPE = nodetype;
	count++;
	lineNo = l;
	colNo = c;
//	std::cout << to_string() << "Created" << "\n";
}
SNode::SNode(int nodetype, int value, int l, int c) {
	init();
	NODETYPE = nodetype;
	VALUE = value;
	NAME = std::to_string(value);
	count++;
	lineNo = l;
	colNo = c;
//	std::cout << to_string() << "Created" << "\n";
}
SNode::SNode(int nodetype, const std::string &name, int l, int c) {
	init();
	NODETYPE = nodetype;
	NAME = name;
	count++;
	lineNo = l;
	colNo = c;
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
}
void SNode::runStatements() {
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
int SNode::typeCheck() {
	int check = PASS;
	for (SNode *i = this; i != nullptr; i = i->next) {
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
					if (x->getPTR1()->getType() != INTEGER) {
						error("Index has to be integer", x->lineNo, x->colNo);
						return FAIL;
					}
					else
						return check;
				}
			}
		case READ: {
				SNode *y = x->getPTR2();
				if (y->getType() != INTEGER) {
					error("Only Integer Can be Read", y->lineNo, y->colNo);
					return FAIL;
				}
				if (y->getPTR1() == nullptr)
					return PASS;
				else {
					int check = typeCheck(y->getPTR1());
					if (y->getPTR1()->getType() != INTEGER) {
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
				if (X->getType() == INTEGER && Y->getType() == BOOLEAN) {
					error("'" + Y->getName() + "' is of type Boolean, needed Integer", Y->lineNo, Y->colNo);
					return FAIL;
				}
				if (X->getType() == BOOLEAN && Y->getType() == INTEGER) {
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
				if (x->getPTR2()->getType() != INTEGER) {
					error("Only Integer Values can be printed", x->lineNo, x->colNo);
					return FAIL;
				}
				return check;
				break;
			}
		case IF: {
				int check = typeCheck(x->getPTR1());
				if (x->getPTR1()->getType() != BOOLEAN) {
					error("Condition should be a Logical Expression", x->lineNo, x->colNo);
					return FAIL;
				}
				return check;
				break;
			}
		case WHILE: {
				int check = typeCheck(x->getPTR1());
				if (x->getPTR1()->getType() != BOOLEAN) {
					error("Condition should be a Logical Expression", x->lineNo, x->colNo);
					return FAIL;
				}
				return check;
				break;
			}
		case START:
			return PASS;
			break;


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
				if (X->getType() == BOOLEAN) {
					error("'" + X->getName() + "' is of type Boolean, needed Integer", X->lineNo, X->colNo);
					return FAIL;
				}
				if (Y->getType() == BOOLEAN) {
					error("'" + Y->getName() + "' is of type Boolean, needed Integer", Y->lineNo, Y->colNo);
					return FAIL;
				}
				return std::min(check1, check2);
			}
		/*		case ISEQ:
				case NOTEQ: {
						SNode *X = x->getPTR1();
						SNode *Y = x->getPTR2();
						int check1 = typeCheck(X);
						int check2 = typeCheck(Y);

						if (X->getType() == INTEGER && Y->getType() == BOOLEAN) {
							error("'" + Y->getName() + "' is of type Boolean, needed Integer", Y->lineNo, Y->colNo);
							return FAIL;
						}
						if (X->getType() == BOOLEAN && Y->getType() == INTEGER) {
							error("'" + Y->getName() + "' is of type Integer, needed Boolean", Y->lineNo, Y->colNo);
							return FAIL;
						}
						return std::min(check1, check2);
					}*/
		case AND:
		case OR: {
				SNode *X = x->getPTR1();
				SNode *Y = x->getPTR2();
				int check1 = typeCheck(X);
				int check2 = typeCheck(Y);
				if (X->getType() == INTEGER) {
					error("'" + X->getName() + "' is of type Integer, needed Boolean", X->lineNo, X->colNo);
					return FAIL;
				}
				if (Y->getType() == INTEGER) {
					error("'" + Y->getName() + "' is of type Integer, needed Boolean", Y->lineNo, Y->colNo);
					return FAIL;
				}
				return std::min(check1, check2);;
			}
		case NOT: {
				int check = typeCheck(x->getPTR1());
				if (x->getPTR1()->getType() == INTEGER) {
					error("'" + x->getPTR1()->getName() + "' is of type Integer, needed Boolean", x->lineNo, x->colNo);
					return FAIL;
				}
				return check;
			}
	}
	return PASS;
}
int SNode::codeGen(FILE *output) {
	for (SNode *i = this; i != nullptr; i = i->next) {
		codeGen(i, output);
	}
	return 0;
}
int SNode::codeGen(SNode *node, FILE *output) {
	switch (node->NODETYPE) {

		//
		//	CONSTRUCTS WITH MEMORY ACCESS
		//

		case ID: {
				// if (x->PTR1 == nullptr)
				// return STACK.at(x->entry->getBinding());
				// else
				// return STACK.at(x->entry->getBinding() + x->PTR1->execute());
				break;
			}
		case READ: {
				// SNode *y = x->getPTR2();
				// if (y->PTR1 == nullptr) {
				// std::cout << "Enter value of '" << y->NAME << "'\n";
				// std::cin >> STACK.at(y->entry->getBinding());
				// }
				// else {
				// std::cout << "Enter value of '" << y->NAME << "[" << y->PTR1->execute() << "]'\n";
				// std::cin >> STACK.at(y->entry->getBinding() + y->PTR1->execute());
				// }
				break;
			}
		case '=': {
//				std::cout<<"Assignment\n";
				// SNode *y = x->getPTR1();
				//			std::cout<<"y="<<y<<"\n";
				//			std::cout<<"bind="<<y->entry->getBinding()<<"\n";
				// if (y->PTR1 == nullptr)
				// STACK.at(y->entry->getBinding()) = execute(x->getPTR2());
				// else
				// STACK.at(y->entry->getBinding() + y->PTR1->execute()) = execute(x->getPTR2());
//				val(result);
				//			std::cout<<"Assignment Over\n";
				break;
			}




		//
		//	CONSTRUCTS
		//

		case WRITE: {
				int reg = codeGen(node->getPTR2(), output);
				fprintf(output,"OUT R%d\n",reg);
				freeReg(debug);
				// std::cout << "Output = " << execute(x->getPTR2()) << "\n";
				break;
			}
		case IF: {
				if(node->getPTR3()==nullptr){
					int label = getIfLabel();
					fprintf(output,"IFSTART%d:\n",label);
					int reg = codeGen(node->getPTR1(),output);
					fprintf(output,"JZ R%d, ENDIF%d\n",reg,label);
					node->getPTR2()->codeGen(output);
					fprintf(output,"ENDIF%d:\n",label);
					freeReg(debug);
				}
				else{
					int label = getIfLabel();
					fprintf(output,"IFSTART%d:\n",label);
					int reg = codeGen(node->getPTR1(),output);
					fprintf(output,"JZ R%d, ELSEPART%d\n",reg,label);
					node->getPTR2()->codeGen(output);
					fprintf(output,"JMP ENDIF%d\n",label);
					fprintf(output,"ELSEPART%d:\n",label);
					node->getPTR3()->codeGen(output);
					fprintf(output,"ENDIF%d:\n",label);
					freeReg(debug);
				}
				break;
			}
		case WHILE: {
				// while (x->getPTR1()->execute())
				// x->getPTR2()->runStatements();
					int label = getWhileLabel();
					fprintf(output,"WHILES%d:\n",label);
					int reg = codeGen(node->getPTR1(),output);
					fprintf(output,"JZ R%d, ENDWHILE%d\n",reg,label);
					node->getPTR2()->codeGen(output);
					fprintf(output,"JMP WHILES%d\n",label);
					fprintf(output,"ENDWHILE%d:\n",label);
					freeReg(debug);
				break;
			}
		case START: {
				fprintf(output,"START\n");
				break;
			}


		//
		//		CONSTANTS
		//
		case NUM: {
				// return x->VALUE;
				int reg = getReg();
				fprintf(output,"MOV R%d, %d\n",reg, node->getValue());
				return reg;
				break;
			}
		case TRUE: {
				int reg = getReg();
				fprintf(output,"MOV R%d, 1\n",reg);
				return reg;
				break;
			}
		case FALSE: {
				int reg = getReg();
				fprintf(output,"MOV R%d, 0\n",reg);
				return reg;
				break;
			}


		//
		//		EXPRESSIONS
		//

		case '+': {
				int reg1 = codeGen(node->getPTR1(),output);
				int reg2 = codeGen(node->getPTR2(),output);
				fprintf(output,"ADD R%d R%d\n",reg1, reg2);
				freeReg(debug);
				return reg1;
				break;
			}
		case '-': {
				int reg1 = codeGen(node->getPTR1(),output);
				int reg2 = codeGen(node->getPTR2(),output);
				fprintf(output,"SUB R%d R%d\n",reg1, reg2);
				freeReg(debug);
				return reg1;
				break;
			}
		case '*': {
				int reg1 = codeGen(node->getPTR1(),output);
				int reg2 = codeGen(node->getPTR2(),output);
				fprintf(output,"MUL R%d R%d\n",reg1, reg2);
				freeReg(debug);
				return reg1;
				break;
			}
		case '/': {
				int reg1 = codeGen(node->getPTR1(),output);
				int reg2 = codeGen(node->getPTR2(),output);
				fprintf(output,"DIV R%d R%d\n",reg1, reg2);
				freeReg(debug);
				return reg1;
				break;
			}
		case '<': {
				int reg1 = codeGen(node->getPTR1(),output);
				int reg2 = codeGen(node->getPTR2(),output);
				fprintf(output,"LT R%d R%d\n",reg1, reg2);
				freeReg(debug);
				return reg1;
				break;
			}
		case '>': {
				int reg1 = codeGen(node->getPTR1(),output);
				int reg2 = codeGen(node->getPTR2(),output);
				fprintf(output,"GT R%d R%d\n",reg1, reg2);
				freeReg(debug);
				return reg1;
				break;
			}
		case '^': {
				int reg1 = codeGen(node->getPTR1(),output);
				int reg2 = codeGen(node->getPTR2(),output);
				fprintf(output,"MOD R%d R%d\n",reg1, reg2);
				freeReg(debug);
				return reg1;
				break;
			}
		case LEQ: {
				int reg1 = codeGen(node->getPTR1(),output);
				int reg2 = codeGen(node->getPTR2(),output);
				fprintf(output,"LE R%d R%d\n",reg1, reg2);
				freeReg(debug);
				return reg1;
				break;
			}
		case GEQ: {
				int reg1 = codeGen(node->getPTR1(),output);
				int reg2 = codeGen(node->getPTR2(),output);
				fprintf(output,"GE R%d R%d\n",reg1, reg2);
				freeReg(debug);
				return reg1;
				break;
			}
		case ISEQ: {
				int reg1 = codeGen(node->getPTR1(),output);
				int reg2 = codeGen(node->getPTR2(),output);
				fprintf(output,"EQ R%d R%d\n",reg1, reg2);
				freeReg(debug);
				return reg1;
				break;
			}
		case NOTEQ: {
				int reg1 = codeGen(node->getPTR1(),output);
				int reg2 = codeGen(node->getPTR2(),output);
				fprintf(output,"NE R%d R%d\n",reg1, reg2);
				freeReg(debug);
				return reg1;
				break;
			}
		case AND: {
				int reg1 = codeGen(node->getPTR1(),output);
				int reg2 = codeGen(node->getPTR2(),output);
				fprintf(output,"MUL R%d R%d\n",reg1, reg2);
				freeReg(debug);
				return reg1;
				break;
			}
		case OR: {
				int reg1 = codeGen(node->getPTR1(),output);
				int reg2 = codeGen(node->getPTR2(),output);
				fprintf(output,"ADD R%d R%d\n",reg1, reg2);
				fprintf(output,"MOV R%d, 0\n", reg2);
				fprintf(output,"NE R%d R%d\n",reg1, reg2);
				freeReg(debug);
				return reg1;
				break;
			}
		case NOT: {
				int reg1 = codeGen(node->getPTR1(),output);
				int reg2 = getReg();
				fprintf(output,"MOV R%d 0\n",reg2);
				fprintf(output,"EQ R%d R%d\n",reg1, reg2);
				freeReg(debug);
				return reg1;
				// return (x->getPTR1()->execute()) ? 1 : 0;
				break;
			}
		default:
			std::cout << "ERROR:\a\a Not Recognized " << node->NODETYPE <<
					  " (char)" << (char)(node->NODETYPE) << "\n";
			exit(1);
	}
	return -1;
}