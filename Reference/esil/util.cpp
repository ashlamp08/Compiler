#include "util.h"
#include "compiler.hpp"

#include <iostream>
#include <set>

#define debug std::string(__FILE__)+std::string(",")+std::to_string(__LINE__)

void error(const std::string &s, int l = -1, int c = -1) {
	std::cout << "ERROR: ";
	if (l != -1)
		std::cout << l;

	if (c != -1)
		std::cout << "," << c << ": ";
	else
		std::cout << ": ";
	std::cout << s << "\n";
}

int getUsageType(symbolNode *entry) {
	if (!entry)
		return -1;
	if (entry->getSize() == -2)
		return FUNCTION;
	else if (entry->getSize() == -1)
		return VARIABLE;
	else
		return ARRAY;
}


//	TYPE ID '(' ARGLIST ')' '{' DECLERATIONS
SNode *processFunctionHeader(SNode *datatype, SNode *functionID, SNode *arguments, SNode *declarations, SNode *globalScope) {
	SNode *returnValue = new SNode(FUNC, functionID->getName(), functionID->lineNo, functionID->colNo);
	returnValue->setReturnType(datatype->getReturnType());
	symbolNode *entry = globalScope->getTable()->lookUp(functionID->getName());
//	val(returnValue);
//	val(entry);
	returnValue->setEntry(entry);
	if (entry == nullptr) {
		error("Function not Declared", datatype->lineNo, datatype->colNo);
		return nullptr;
	}
	if (entry->getSize() != -2) {
		error("Cant use Variable as Function", datatype->lineNo, datatype->colNo);
		return nullptr;
	}
	if (arguments == nullptr && entry->getArgs().size() != 0) {
		error("Wrong Number of Arguments", datatype->lineNo, datatype->colNo);
		return nullptr;
	}
	std::set<std::string> argmunetNames;
	std::vector<symbolNode *> arglist;
	for (SNode *temp1 = arguments; temp1 != nullptr; temp1 = temp1->getNext())
		for (SNode *temp2 = temp1->getPTR3(); temp2 != nullptr; temp2 = temp2->getNext()) {
			arglist.push_back(new symbolNode(temp2->getName(), temp1->getReturnType()));
			auto result = argmunetNames.insert(temp2->getName());
			if (!result.second) {
				error("Duplicate argument '" + temp2->getName(), temp2->lineNo, temp2->colNo);
				return nullptr;
			}
			if (temp2->getReturnType() == reference) {
				arglist.back()->setAsPassByReference();
			}
		}
	/*deb*/
	if (arglist.size() != entry->getArgs().size()) {
		error("Wrong Number of Arguments", datatype->lineNo, datatype->colNo);
		return nullptr;
	}
	/*deb*/
	for (unsigned i = 0; i < arglist.size(); i++)
		if (arglist[i]->getType() != entry->getArgs()[i]->getType()) {
			error("Argument " + std::to_string(i + 1) + "'s Data Type in decleration: " + entry->getArgs()[i]->getType()->getTypeName() + "' is not same as Argument's Data Type in definition: " + arglist[i]->getType()->getTypeName(), datatype->lineNo, datatype->colNo);
			return nullptr;
		}
		else if (arglist[i]->getName() != entry->getArgs()[i]->getName()) {
			error("Argument " + std::to_string(i + 1) + "'s Name in decleration: " + entry->getArgs()[i]->getName() + "' is not same as Argument's Name in definition: " + arglist[i]->getName(), datatype->lineNo, datatype->colNo);
			return nullptr;
		}
		else if (arglist[i]->isPassedByReference() && !entry->getArgs()[i]->isPassedByReference()) {
			error("Argument " + std::to_string(i + 1) + " is passed by value in Definition but not in Declaration", datatype->lineNo, datatype->colNo);
			return nullptr;
		}
		else if (!arglist[i]->isPassedByReference() && entry->getArgs()[i]->isPassedByReference()) {
			error("Argument " + std::to_string(i + 1) + " is passed by reference in Definition but not in Declaration", datatype->lineNo, datatype->colNo);
			return nullptr;
		}
	/*deb*/
	if (declarations)
		for (symbolNode *i = declarations->getTable()->getNext(); i; i = i->getNext()) {
			auto search = argmunetNames.find(i->getName());
			if (search != argmunetNames.end()) {
				error("Can't Declare '" + i->getName() + "'. Already Used as a Argument", declarations->lineNo, declarations->colNo);
				return nullptr;
			}
			if (i->getSize() > 0) {
				error("Cannot Declare Array in a Function", declarations->lineNo, declarations->colNo);
				return nullptr;
			}
			else if (i->getSize() == -2) {
				error("Cannot Declare Functions in a Function", declarations->lineNo, declarations->colNo);
				return nullptr;
			}
		}

	/*deb*/
	if (declarations)
		returnValue->setTable(declarations->getTable());
	entry->setArgs(arglist);
	for (symbolNode *i : arglist)
		if (i != nullptr)
			delete i;
	/*deb*/
	return returnValue;
}



bool processDeclerations(symbolNode *Table, SNode *declareList) {
	for (SNode *head = declareList; head != nullptr; head = head->getNext()) {
		for (SNode *i = head->getPTR3(); i != nullptr; i = i->getPTR3()) {
			std::vector<symbolNode *> arglist;
			if (i->getNodeType() == FUNC) {
				std::set<std::string> argmunetNames;
				for (SNode *temp1 = i->getPTR2(); temp1 != nullptr; temp1 = temp1->getNext())
					for (SNode *temp2 = temp1->getPTR3(); temp2 != nullptr; temp2 = temp2->getNext()) {
						arglist.push_back(new symbolNode(temp2->getName(), temp1->getReturnType()));
						auto result = argmunetNames.insert(temp2->getName());
						if (!result.second) {
							error("Duplicate argument '" + temp2->getName(), temp2->lineNo, temp2->colNo);
							return false;
						}
						if (temp2->getReturnType() == reference) {
							arglist.back()->setAsPassByReference();
						}
					}
			}
			symbolNode *position;
			if (i->getPTR2())
				position = Table->install(i->getName(), head->getReturnType(), i->getPTR2()->getValue());
			else
				position = Table->install(i->getName(), head->getReturnType());
			if (position == nullptr) {
				error("'" + i->getName() + "' is already declared", i->lineNo, i->colNo);
				return false;
			}
			if (i->getNodeType() == FUNC) {
				position->setArgs(arglist);
			}
		}
	}
	int size = 1;
	for (symbolNode *i = Table->getNext(); i; i = i->getNext()) {
		i->setBinding(size);
		if (i->getSize() == -1)
			size++;
		else if (i->getSize() == -2);
		else
			size += i->getSize();
	}
	return true;
}
SNode *parseMembers(SNode *variableID, symbolNode *entry) {
	typeNode *typeEntry = entry->getType()->getEntry(), *returnType = entry->getType();
	for (SNode *i = variableID->getPTR2(), *last = variableID; i; i = i->getPTR2()) {
		typeNode *memberEntry = typeEntry->lookUp(i->getName());
		if (!memberEntry) {
			error("'" + last->getName() + "' has no member '" + i->getName() + "'", i->lineNo, i->colNo);
			return nullptr;
		}		
		i->setNodeType(memberEntry->getIndex());
		typeEntry = memberEntry->getEntry()->getEntry();
		returnType = memberEntry->getEntry();
		last = i;
	}
	for (SNode *i = variableID->getPTR2(); i; i = i->getPTR2())
		i->setReturnType(returnType);
	variableID->setReturnType(returnType);
	return variableID;
}
SNode *variableAccess(SNode *variableID, SNode *indexExpr, SNode *Scope[2], int usedVariableType) {
	const char names[][20] = {"Array", "Variable", "Function"};
	for (int i = 0; i < 2; i++) {
		if (!Scope[i])
			continue;
		symbolNode *Table = Scope[i]->getTable(), *entry = nullptr;
		if (Table)
			entry = Table->lookUp(variableID->getName());
		if (entry == nullptr) {
			if (Scope[i]->getEntry()) {
				for (symbolNode *node : Scope[i]->getEntry()->getArgs()) {
					if (node->getName() == variableID->getName()) {
						entry = node;
						break;
					}
				}
			}
		}
		if (entry == nullptr)
			continue;
		int declaredVariableType = getUsageType(entry);
		if (usedVariableType != declaredVariableType) {
			error("'" + variableID->getName() + "' used as " + names[usedVariableType] + " but declared as " + names[declaredVariableType], variableID->lineNo, variableID->colNo);
			return nullptr;
		}
		switch (usedVariableType) {
			case ARRAY: {
					variableID->setEntry(entry);
					variableID->setPTR1(indexExpr);
					variableID->setReturnType(entry->getType());
					return parseMembers(variableID, entry);
					break;
				}
			case VARIABLE: {
					variableID->setEntry(entry);
					variableID->setReturnType(entry->getType());
					return parseMembers(variableID, entry);
					break;
				}
			case FUNCTION: {
					std::vector<SNode *> arglist;
					variableID->setEntry(entry);
					variableID->setReturnType(entry->getType());
					for (SNode *temp = indexExpr, *next; temp; temp = next) {
						arglist.push_back(temp);
						next = temp->getNext();
						temp->setNext(nullptr);
					}
					if (arglist.size() != entry->getArgs().size()) {
						error("Argument Mismatch at " + std::to_string(std::min(arglist.size(), entry->getArgs().size())) + "th argument", variableID->lineNo, variableID->colNo);
						return nullptr;
					}
					variableID->setArgs(arglist);
					return variableID;
					break;
				}
			default:
				break;
		}
	}
	error("'" + variableID->getName() + "' not Declared", variableID->lineNo, variableID->colNo);
	return nullptr;
}

int regNo = 0;

int getReg(const std::string &str = "") {
	if (regNo == 8) {
		std::cout << "Error: No Register left. Change your Strategy. " << str << "\n";
		exit(1);
	}
	return regNo++;
}

int freeReg(const std::string &str = "") {
	if (regNo == 0) {
		std::cout << "Error: You shouldn't be freeing a REG now. Check your Logic. " << str << "\n";
		exit(1);
	}
	return regNo--;
}

int getIfLabel() {
	static int label = 0;
	if (label < 0) {
		std::cout << "Error: What are you doing? we are out of If Labels\n";
		exit(1);
	}
	label++;
	return label;
}

int getWhileLabel() {
	static int label = 0;
	if (label < 0) {
		std::cout << "Error: What are you doing? we are out of While Labels\n";
		exit(1);
	}
	label++;
	return label;
}

int generateFunctionHead(SNode *func, FILE *output) {
	symbolNode *table = func->getTable();
	int size = 0;
	if (table)
		for (symbolNode *i = table->getNext(); i != nullptr; i = i->getNext()) {
			if (i->getSize() == -1)
				size++;
			else if (i->getSize() == -2);
			else
				size += i->getSize();
		}
	fprintf(output, "PUSH BP\n");
	fprintf(output, "MOV BP, SP\n");
	int reg1 = getReg();
	int reg2 = getReg();
	fprintf(output, "MOV R%d, BP\n", reg1);
	fprintf(output, "MOV R%d, %d\n", reg2, size);
	fprintf(output, "ADD R%d, R%d\n", reg1, reg2);
	fprintf(output, "MOV SP, R%d\n", reg1);
	freeReg();
	freeReg();
	return 0;
}
int generateCode(SNode *start, FILE *output) {
	fprintf(output, "START\n");
	fprintf(output, "MOV BP, 257\n");
	fprintf(output, "MOV SP, 256\n");
	generateFunctionHead(start, output);
	fprintf(output, "PUSH BP\n");
	fprintf(output, "CALL FUNCmain\n");
	fprintf(output, "HALT\n");
	for (SNode *i = start; i != nullptr; i = i->getNext()) {
		codeGen(i, output);
	}
	return 0;
}
int getLocation(SNode *node, FILE *output) {
	// std::cout << "Entering getLocation with node = " << node << ", " << node->to_string() << "\n";
	symbolNode *entry = node->getEntry();
	if (entry->isGlobal()) {
		int baseAddrReg = getReg();
		int offsetReg = codeGen(node->getPTR1(), output);
		fprintf(output, "MOV R%d, %d\n", baseAddrReg, entry->getBinding() + 257);
		if (offsetReg != -1) {
			fprintf(output, "ADD R%d, R%d\n", baseAddrReg, offsetReg);
			freeReg(debug);
		}
		for (SNode *i = node->getPTR2(); i; i = i->getPTR2()){
			offsetReg = getReg();
			fprintf(output, "MOV R%d, %d\n", offsetReg, i->getNodeType());
			fprintf(output, "MOV R%d, [R%d]\n", baseAddrReg, baseAddrReg);
			fprintf(output, "ADD R%d, R%d\n", baseAddrReg, offsetReg);
			freeReg(debug);
		}
		return baseAddrReg;
	}
	else {
		int baseAddrReg = getReg();
		int bindReg = getReg();
		int offsetReg = codeGen(node->getPTR1(), output);
		fprintf(output, "MOV R%d, BP\n", baseAddrReg);
		fprintf(output, "MOV R%d, %d\n", bindReg, entry->getBinding());
		fprintf(output, "ADD R%d, R%d\n", baseAddrReg, bindReg);
		if (offsetReg != -1) {
			fprintf(output, "ADD R%d, R%d\n", baseAddrReg, offsetReg);
			freeReg(debug);
		}
		if (entry->isPassedByReference())
			fprintf(output, "MOV R%d, [R%d]\n", baseAddrReg, baseAddrReg);
		freeReg(debug);
		for (SNode *i = node->getPTR2(); i; i = i->getPTR2()){
			offsetReg = getReg();
			fprintf(output, "MOV R%d, %d\n", offsetReg, i->getNodeType());
			fprintf(output, "MOV R%d, [R%d]\n", baseAddrReg, baseAddrReg);
			fprintf(output, "ADD R%d, R%d\n", baseAddrReg, offsetReg);
			freeReg(debug);
		}
		return baseAddrReg;
	}
}
int codeGen(SNode *node, FILE *output) {
	// std::cout << "Entering codeGen with node = " << node << (node ? ", " : "\n");
	if (!node)
		return -1;
	// std::cout << node->to_string() << "\n";
	switch (node->getNodeType()) {
		//
		//	THE ALL DREADED FUNCTION DEFINITION IS HERE
		//
		case FUNC: {
				fprintf(output, "FUNC%s:\n", node->getName().c_str());
				generateFunctionHead(node, output);
				for (SNode *i = node->getPTR2(); i != nullptr; i = i->getNext()) {
					codeGen(i, output);
				}
				break;
			}
		//
		// EQUALLY DREADED RETURN IS HERE
		//
		case RETURN: {
				int reg1 = getReg();
				int reg2 = getReg();
				fprintf(output, "MOV R%d, -2\n", reg1);
				fprintf(output, "MOV R%d, BP\n", reg2);
				fprintf(output, "ADD R%d, R%d\n", reg1, reg2);
				freeReg();
				reg2 = codeGen(node->getPTR2(), output);
				fprintf(output, "MOV [R%d], R%d\n", reg1, reg2);
				fprintf(output, "MOV SP, BP\n");
				fprintf(output, "POP BP\n");
				fprintf(output, "RET\n");
				freeReg();
				freeReg();
				break;
			}
		//
		//	CONSTRUCTS WITH MEMORY ACCESS
		//
		case ID: {
				symbolNode *entry = node->getEntry();
				switch (getUsageType(entry)) {
					case FUNCTION: {
							int returnReg = getReg();
							for (int i = 0; i < returnReg; i++)
								fprintf(output, "PUSH R%d\n", i);
							int reg1 = getReg();			// Stores the Original SP
							int reg2 = getReg();
							fprintf(output, "MOV R%d, SP\n", reg1);
							fprintf(output, "MOV R%d, %lu\n", reg2, entry->getArgs().size() + 1);
							fprintf(output, "ADD R%d, R%d\n", reg2, reg1);
							fprintf(output, "MOV SP, R%d\n", reg2);
							freeReg();
							for (unsigned i = 0; i < node->getArgs().size(); i++) {
								if (entry->getArgs()[i]->isPassedByReference()) {
									SNode *actualArg = node->getArgs()[i];
									int location = getLocation(actualArg, output);
									int reg2 = getReg();
									fprintf(output, "MOV R%d, %d\n", reg2, i + 1);
									fprintf(output, "ADD R%d, R%d\n", reg2, reg1);
									fprintf(output, "MOV [R%d], R%d\n", reg2, location);
									freeReg(debug);
									freeReg(debug);
								}
								else {
									int reg = codeGen(node->getArgs()[i], output);
									reg2 = getReg();
									fprintf(output, "MOV R%d, %d\n", reg2, i + 1);
									fprintf(output, "ADD R%d, R%d\n", reg2, reg1);
									fprintf(output, "MOV [R%d], R%d\n", reg2, reg);
									freeReg(debug);
									freeReg(debug);
								}
							}
							fprintf(output, "CALL FUNC%s\n", node->getName().c_str());
							freeReg();

							reg1 = getReg();
							reg2 = getReg();
							fprintf(output, "MOV R%d, SP\n", reg1);
							fprintf(output, "MOV R%d, %lu\n", reg2, entry->getArgs().size() + 1);
							fprintf(output, "SUB R%d, R%d\n", reg1, reg2);
							fprintf(output, "MOV R%d, SP\n", reg2);
							fprintf(output, "MOV SP, R%d\n", reg1);
							if (returnReg)
								fprintf(output, "MOV R%d, [R%d]\n", returnReg, reg2);
							else
								fprintf(output, "MOV R%d, [R%d]\n", returnReg, reg2);
							freeReg(debug);
							freeReg(debug);
							for (int i = returnReg - 1; i >= 0; i--)
								fprintf(output, "POP R%d\n", i);
							return returnReg;
							break;
						}
					case VARIABLE:
					case ARRAY: {
//							val("deb");
							int location = getLocation(node, output);
							fprintf(output, "MOV R%d, [R%d] //deb\n", location, location);
							return location;
						}
				}
				break;
			}
		case READ: {
				SNode *variable = node->getPTR2();
				switch (getUsageType(variable->getEntry())) {
					case FUNCTION: {
							break;
						}
					case VARIABLE:
					case ARRAY: {
							int inputReg = getReg();
							int location = getLocation(variable, output);
							fprintf(output, "IN R%d\n", inputReg);
							fprintf(output, "MOV [R%d], R%d\n", location, inputReg);
							freeReg();
							freeReg();
							break;
						}
				}
				break;
			}
		case '=': {
				SNode *lValue = node->getPTR1(), *rValue = node->getPTR2();
				symbolNode *entry = lValue->getEntry();
				switch (getUsageType(entry)) {
					case FUNCTION: {
							break;
						}
					case VARIABLE:
					case ARRAY: {
							int inputReg = codeGen(rValue, output);
							int location = getLocation(lValue, output);
							fprintf(output, "MOV [R%d], R%d\n", location, inputReg);
							freeReg();
							freeReg();
							break;
						}
				}
				break;
			}
		//
		//	CONSTRUCTS
		//
		case WRITE: {
				int reg = codeGen(node->getPTR2(), output);			// Stores the value of Expr
				fprintf(output, "OUT R%d\n", reg);
				freeReg(debug);
				break;
			}
		case IF: {
				if (node->getPTR3() == nullptr) {
					int label = getIfLabel();
					fprintf(output, "IFSTART%d:\n", label);
					int reg = codeGen(node->getPTR1(), output);			// Stores the value of conditional
					fprintf(output, "JZ R%d, ENDIF%d\n", reg, label);
					for (SNode *i = node->getPTR2(); i != nullptr; i = i->getNext()) {
						codeGen(i, output);
					}
					fprintf(output, "ENDIF%d:\n", label);
					freeReg(debug);
				}
				else {
					int label = getIfLabel();
					fprintf(output, "IFSTART%d:\n", label);
					int reg = codeGen(node->getPTR1(), output);			// Stores the value of conditional
					fprintf(output, "JZ R%d, ELSEPART%d\n", reg, label);
					freeReg(debug);
					for (SNode *i = node->getPTR2(); i != nullptr; i = i->getNext()) {
						codeGen(i, output);
					}
					fprintf(output, "JMP ENDIF%d\n", label);
					fprintf(output, "ELSEPART%d:\n", label);
					for (SNode *i = node->getPTR3(); i != nullptr; i = i->getNext()) {
						codeGen(i, output);
					}
					fprintf(output, "ENDIF%d:\n", label);
				}
				break;
			}
		case WHILE: {
				int label = getWhileLabel();
				fprintf(output, "WHILES%d:\n", label);
				int reg = codeGen(node->getPTR1(), output);		// Stores the value of conditional
				freeReg(debug);
				fprintf(output, "JZ R%d, ENDWHILE%d\n", reg, label);
				for (SNode *i = node->getPTR2(); i != nullptr; i = i->getNext()) {
					codeGen(i, output);
				}
				fprintf(output, "JMP WHILES%d\n", label);
				fprintf(output, "ENDWHILE%d:\n", label);
				break;
			}
		case START: {
				break;
			}
		//
		//		CONSTANTS
		//
		case NUM: {
				int reg = getReg();								// Stores the Number
				fprintf(output, "MOV R%d, %d\n", reg, node->getValue());
				return reg;
				break;
			}
		case TRUE: {
				int reg = getReg();								// Stores the value 1
				fprintf(output, "MOV R%d, 1\n", reg);
				return reg;
				break;
			}
		case FALSE: {
				int reg = getReg();								// Stores the value 0
				fprintf(output, "MOV R%d, 0\n", reg);
				return reg;
				break;
			}
		//
		//		EXPRESSIONS
		//
		case '+': {
				int LHS = codeGen(node->getPTR1(), output);	//	Stores the result of LHS
				int RHS = codeGen(node->getPTR2(), output);	//	Stores the result of RHS
				fprintf(output, "ADD R%d R%d\n", LHS, RHS);
				freeReg(debug);
				return LHS;
				break;
			}
		case '-': {
				int LHS = codeGen(node->getPTR1(), output);	//	Stores the result of LHS
				int RHS = codeGen(node->getPTR2(), output);	//	Stores the result of RHS
				fprintf(output, "SUB R%d R%d\n", LHS, RHS);
				freeReg(debug);
				return LHS;
				break;
			}
		case '*': {
				int LHS = codeGen(node->getPTR1(), output);	//	Stores the result of LHS
				int RHS = codeGen(node->getPTR2(), output);	//	Stores the result of RHS
				fprintf(output, "MUL R%d R%d\n", LHS, RHS);
				freeReg(debug);
				return LHS;
				break;
			}
		case '/': {
				int LHS = codeGen(node->getPTR1(), output);	//	Stores the result of LHS
				int RHS = codeGen(node->getPTR2(), output);	//	Stores the result of RHS
				fprintf(output, "DIV R%d R%d\n", LHS, RHS);
				freeReg(debug);
				return LHS;
				break;
			}
		case '<': {
				int LHS = codeGen(node->getPTR1(), output);	//	Stores the result of LHS
				int RHS = codeGen(node->getPTR2(), output);	//	Stores the result of RHS
				fprintf(output, "LT R%d R%d\n", LHS, RHS);
				freeReg(debug);
				return LHS;
				break;
			}
		case '>': {
				int LHS = codeGen(node->getPTR1(), output);	//	Stores the result of LHS
				int RHS = codeGen(node->getPTR2(), output);	//	Stores the result of RHS
				fprintf(output, "GT R%d R%d\n", LHS, RHS);
				freeReg(debug);
				return LHS;
				break;
			}
		case '^': {
				int LHS = codeGen(node->getPTR1(), output);	//	Stores the result of LHS
				int RHS = codeGen(node->getPTR2(), output);	//	Stores the result of RHS
				fprintf(output, "MOD R%d R%d\n", LHS, RHS);
				freeReg(debug);
				return LHS;
				break;
			}
		case LEQ: {
				int LHS = codeGen(node->getPTR1(), output);	//	Stores the result of LHS
				int RHS = codeGen(node->getPTR2(), output);	//	Stores the result of RHS
				fprintf(output, "LE R%d R%d\n", LHS, RHS);
				freeReg(debug);
				return LHS;
				break;
			}
		case GEQ: {
				int LHS = codeGen(node->getPTR1(), output);	//	Stores the result of LHS
				int RHS = codeGen(node->getPTR2(), output);	//	Stores the result of RHS
				fprintf(output, "GE R%d R%d\n", LHS, RHS);
				freeReg(debug);
				return LHS;
				break;
			}
		case ISEQ: {
				int LHS = codeGen(node->getPTR1(), output);	//	Stores the result of LHS
				int RHS = codeGen(node->getPTR2(), output);	//	Stores the result of RHS
				fprintf(output, "EQ R%d R%d\n", LHS, RHS);
				freeReg(debug);
				return LHS;
				break;
			}
		case NOTEQ: {
				int LHS = codeGen(node->getPTR1(), output);	//	Stores the result of LHS
				int RHS = codeGen(node->getPTR2(), output);	//	Stores the result of RHS
				fprintf(output, "NE R%d R%d\n", LHS, RHS);
				freeReg(debug);
				return LHS;
				break;
			}
		case AND: {
				int LHS = codeGen(node->getPTR1(), output);	//	Stores the result of LHS
				int RHS = codeGen(node->getPTR2(), output);	//	Stores the result of RHS
				fprintf(output, "MUL R%d R%d\n", LHS, RHS);
				freeReg(debug);
				return LHS;
				break;
			}
		case OR: {
				int LHS = codeGen(node->getPTR1(), output);	//	Stores the result of LHS
				int RHS = codeGen(node->getPTR2(), output);	//	Stores the result of RHS
				fprintf(output, "ADD R%d R%d\n", LHS, RHS);
				fprintf(output, "MOV R%d, 0\n", RHS);
				fprintf(output, "NE R%d R%d\n", LHS, RHS);
				freeReg(debug);
				return LHS;
				break;
			}
		case NOT: {
				int LHS = codeGen(node->getPTR1(), output);	//	Stores the result of Expr
				int RHS = getReg();							//	Stores the '0' for Negative
				fprintf(output, "MOV R%d 0\n", RHS);
				fprintf(output, "EQ R%d R%d\n", LHS, RHS);
				freeReg(debug);
				return LHS;
				break;
			}
		default:
			std::cout << "ERROR:\a\a Not Recognized " << node->getNodeType() <<
					  " (char)" << (char)(node->getNodeType()) << "\n";
			return -1;
	}
	return -1;
}
int checkFunctionDeclared(SNode *program) {
	std::set<symbolNode *> declaredFunctions;
	for (symbolNode *i = program->getTable()->getNext(); i; i = i->getNext())
		if (getUsageType(i) == FUNCTION && i->getName() != "free" && i->getName() != "allocate" && i->getName() != "initialize")
			declaredFunctions.insert(i);
	for (SNode *i = program->getNext(); i; i = i->getNext())
		declaredFunctions.erase(i->getEntry());
	if (declaredFunctions.empty())
		return PASS;
	for (auto i : declaredFunctions) {
		error("'" + i->getName() + "' Declared but not Defined", program->lineNo, program->colNo);
	}
	return FAIL;
}
void addLibrary(FILE *output) {
	fprintf(output, "FUNCinitialize:\n");
	fprintf(output, "PUSH BP\n");
	fprintf(output, "MOV BP, SP\n");
	fprintf(output, "MOV R0, BP\n");
	fprintf(output, "MOV R1, 1\n");
	fprintf(output, "ADD R0, R1\n");
	fprintf(output, "MOV SP, R0\n");
	fprintf(output, "MOV [256], 0\n");
	fprintf(output, "MOV R0, 0\n");
	fprintf(output, "MOV R1, BP\n");
	fprintf(output, "MOV R2, 1\n");
	fprintf(output, "ADD R2, R1\n");
	fprintf(output, "MOV [R2], R0\n");
	fprintf(output, "WHILES1:\n");
	fprintf(output, "MOV R0, BP\n");
	fprintf(output, "MOV R1, 1\n");
	fprintf(output, "ADD R1, R0\n");
	fprintf(output, "MOV R0, [R1]\n");
	fprintf(output, "MOV R1, 256\n");
	fprintf(output, "LT R0 R1\n");
	fprintf(output, "JZ R0, ENDWHILE1\n");
	fprintf(output, "MOV R0, 0\n");
	fprintf(output, "MOV R1, BP\n");
	fprintf(output, "MOV R2, 1\n");
	fprintf(output, "ADD R2, R1\n");
	fprintf(output, "MOV R1, [R2]\n");
	fprintf(output, "MOV R2, 0\n");
	fprintf(output, "ADD R1, R2\n");
	fprintf(output, "MOV [R1], R0\n");
	fprintf(output, "MOV R0, BP\n");
	fprintf(output, "MOV R1, 1\n");
	fprintf(output, "ADD R1, R0\n");
	fprintf(output, "MOV R0, [R1]\n");
	fprintf(output, "MOV R1, 1\n");
	fprintf(output, "ADD R0 R1\n");
	fprintf(output, "MOV R1, BP\n");
	fprintf(output, "MOV R2, 1\n");
	fprintf(output, "ADD R2, R1\n");
	fprintf(output, "MOV [R2], R0\n");
	fprintf(output, "JMP WHILES1\n");
	fprintf(output, "ENDWHILE1:\n");
	fprintf(output, "MOV R0, 0\n");
	fprintf(output, "MOV R1, BP\n");
	fprintf(output, "MOV R2, 1\n");
	fprintf(output, "ADD R2, R1\n");
	fprintf(output, "MOV [R2], R0\n");
	fprintf(output, "WHILES2:\n");
	fprintf(output, "MOV R0, BP\n");
	fprintf(output, "MOV R1, 1\n");
	fprintf(output, "ADD R1, R0\n");
	fprintf(output, "MOV R0, [R1]\n");
	fprintf(output, "MOV R1, 248\n");
	fprintf(output, "LT R0 R1\n");
	fprintf(output, "JZ R0, ENDWHILE2\n");
	fprintf(output, "MOV R0, BP\n");
	fprintf(output, "MOV R1, 1\n");
	fprintf(output, "ADD R1, R0\n");
	fprintf(output, "MOV R0, [R1]\n");
	fprintf(output, "MOV R1, 8\n");
	fprintf(output, "ADD R0 R1\n");
	fprintf(output, "MOV R1, BP\n");
	fprintf(output, "MOV R2, 1\n");
	fprintf(output, "ADD R2, R1\n");
	fprintf(output, "MOV R1, [R2]\n");
	fprintf(output, "MOV R2, 0\n");
	fprintf(output, "ADD R1, R2\n");
	fprintf(output, "MOV [R1], R0\n");
	fprintf(output, "MOV R0, BP\n");
	fprintf(output, "MOV R1, 1\n");
	fprintf(output, "ADD R1, R0\n");
	fprintf(output, "MOV R0, [R1]\n");
	fprintf(output, "MOV R1, 8\n");
	fprintf(output, "ADD R0 R1\n");
	fprintf(output, "MOV R1, BP\n");
	fprintf(output, "MOV R2, 1\n");
	fprintf(output, "ADD R2, R1\n");
	fprintf(output, "MOV [R2], R0\n");
	fprintf(output, "JMP WHILES2\n");
	fprintf(output, "ENDWHILE2:\n");
	fprintf(output, "MOV R0, 0\n");
	fprintf(output, "MOV R1, 1\n");
	fprintf(output, "SUB R0 R1\n");
	fprintf(output, "MOV R1, BP\n");
	fprintf(output, "MOV R2, 1\n");
	fprintf(output, "ADD R2, R1\n");
	fprintf(output, "MOV R1, [R2]\n");
	fprintf(output, "MOV R2, 0\n");
	fprintf(output, "ADD R1, R2\n");
	fprintf(output, "MOV [R1], R0\n");
	fprintf(output, "MOV R0, -2\n");
	fprintf(output, "MOV R1, BP\n");
	fprintf(output, "ADD R0, R1\n");
	fprintf(output, "MOV R1, 0\n");
	fprintf(output, "MOV [R0], R1\n");
	fprintf(output, "MOV SP, BP\n");
	fprintf(output, "POP BP\n");
	fprintf(output, "RET\n");
	fprintf(output, "FUNCallocate:\n");
	fprintf(output, "PUSH BP\n");
	fprintf(output, "MOV BP, SP\n");
	fprintf(output, "MOV R0, BP\n");
	fprintf(output, "MOV R1, 1\n");
	fprintf(output, "ADD R0, R1\n");
	fprintf(output, "MOV SP, R0\n");
	fprintf(output, "MOV R0, [256]\n");
	fprintf(output, "MOV R1, BP\n");
	fprintf(output, "MOV R2, 1\n");
	fprintf(output, "ADD R2, R1\n");
	fprintf(output, "MOV [R2], R0\n");
	fprintf(output, "IFSTART1:\n");
	fprintf(output, "MOV R0, [256]\n");
	fprintf(output, "MOV R1, 0\n");
	fprintf(output, "MOV R2, 1\n");
	fprintf(output, "SUB R1 R2\n");
	fprintf(output, "NE R0 R1\n");
	fprintf(output, "JZ R0, ENDIF1\n");
	fprintf(output, "MOV R1, [256]\n");
	fprintf(output, "MOV R2, 0 \n");
	fprintf(output, "ADD R1, R2\n");
	fprintf(output, "MOV R1, [R1]\n");
	fprintf(output, "MOV [256], R1\n");
	fprintf(output, "ENDIF1:\n");
	fprintf(output, "MOV R0, -2\n");
	fprintf(output, "MOV R1, BP\n");
	fprintf(output, "ADD R0, R1\n");
	fprintf(output, "MOV R1, BP\n");
	fprintf(output, "MOV R2, 1\n");
	fprintf(output, "ADD R2, R1\n");
	fprintf(output, "MOV R1, [R2]\n");
	fprintf(output, "MOV [R0], R1\n");
	fprintf(output, "MOV SP, BP\n");
	fprintf(output, "POP BP\n");
	fprintf(output, "RET\n");
	fprintf(output, "FUNCfree:\n");
	fprintf(output, "PUSH BP\n");
	fprintf(output, "MOV BP, SP\n");
	fprintf(output, "MOV R0, BP\n");
	fprintf(output, "MOV R1, 1\n");
	fprintf(output, "ADD R0, R1\n");
	fprintf(output, "MOV SP, R0\n");
	fprintf(output, "MOV R0, [256]\n");
	fprintf(output, "MOV R1, BP\n");
	fprintf(output, "MOV R2, -3\n");
	fprintf(output, "ADD R2, R1\n");
	fprintf(output, "MOV R1, [R2]\n");
	fprintf(output, "MOV R1, [R1]\n");
	fprintf(output, "MOV R2, 0\n");
	fprintf(output, "ADD R1, R2\n");
	fprintf(output, "MOV [R1], R0\n");
	fprintf(output, "MOV R0, BP\n");
	fprintf(output, "MOV R1, -3\n");
	fprintf(output, "ADD R1, R0\n");
	fprintf(output, "MOV R0, [R1]\n");
	fprintf(output, "MOV [256], R0\n");
	fprintf(output, "MOV R1, BP\n");
	fprintf(output, "MOV R2, -3\n");
	fprintf(output, "ADD R2, R1\n");
	fprintf(output, "MOV R1, [R2]\n");
	fprintf(output, "MOV [R1], -1\n");
	fprintf(output, "MOV R0, -2\n");
	fprintf(output, "MOV R1, BP\n");
	fprintf(output, "ADD R0, R1\n");
	fprintf(output, "MOV R1, 0\n");
	fprintf(output, "MOV [R0], R1\n");
	fprintf(output, "MOV SP, BP\n");
	fprintf(output, "POP BP\n");
	fprintf(output, "RET");
}
