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
	returnValue->setReturnType(datatype->getNodeType());
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
			arglist.push_back(new symbolNode(temp2->getName(), temp1->getNodeType()));
			auto result = argmunetNames.insert(temp2->getName());
			if (!result.second) {
				error("Duplicate argument '" + temp2->getName(), temp2->lineNo, temp2->colNo);
				return nullptr;
			}
			if (temp2->getReturnType() == '&') {
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
		if (arglist[i]->getType() != entry->getArgs()[i]->getType() || arglist[i]->getName() != entry->getArgs()[i]->getName()) {
			error("Arguments Mismatch at " + std::to_string(i + 1) + "th argument", datatype->lineNo, datatype->colNo);
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
						arglist.push_back(new symbolNode(temp2->getName(), temp1->getNodeType()));
						auto result = argmunetNames.insert(temp2->getName());
						if (!result.second) {
							error("Duplicate argument '" + temp2->getName(), temp2->lineNo, temp2->colNo);
							return false;
						}
						if (temp2->getReturnType() == '&') {
							arglist.back()->setAsPassByReference();
						}
					}
			}
			symbolNode *position;
			if (i->getPTR2())
				position = Table->install(i->getName(), head->getNodeType(), i->getPTR2()->getValue());
			else
				position = Table->install(i->getName(), head->getNodeType());
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
					return variableID;
					break;
				}
			case VARIABLE: {
					variableID->setEntry(entry);
					variableID->setReturnType(entry->getType());
					return variableID;
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
						error("Arguments Mismatch at " + std::to_string(std::min(arglist.size(), entry->getArgs().size())) + "th argument", variableID->lineNo, variableID->colNo);
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
	generateFunctionHead(start, output);
	fprintf(output, "CALL FUNCmain\n");
	fprintf(output, "HALT\n");
	for (SNode *i = start; i != nullptr; i = i->getNext()) {
		codeGen(i, output);
	}
	return 0;
}
int codeGen(SNode *node, FILE *output) {
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
							fprintf(output, "MOV R%d, %llu\n", reg2, entry->getArgs().size() + 1);
							fprintf(output, "ADD R%d, R%d\n", reg2, reg1);
							fprintf(output, "MOV SP, R%d\n", reg2);
							freeReg();
							for (unsigned i = 0; i < node->getArgs().size(); i++) {
								if (entry->getArgs()[i]->isPassedByReference()) {
									SNode *actualArg = node->getArgs()[i];
									symbolNode *actArgEntry = actualArg->getEntry();
									switch (getUsageType(actualArg->getEntry())) {
										case VARIABLE: {
												if (actArgEntry->isGlobal()) {
													reg2 = getReg();
													fprintf(output, "MOV R%d, %d\n", reg2, i + 1);
													fprintf(output, "ADD R%d, R%d\n", reg2, reg1);
													fprintf(output, "MOV [R%d], %d\n", reg2, actArgEntry->getBinding());
													freeReg(debug);
												}
												else {
													int addrOfVarPassed = getReg();

													int baseReg = getReg();
													fprintf(output, "MOV R%d, BP\n", baseReg);
													int bindReg = getReg();
													fprintf(output, "MOV R%d, %d\n", bindReg, actArgEntry->getBinding());
													fprintf(output, "ADD R%d, R%d\n", bindReg, baseReg);
													fprintf(output, "MOV R%d, [R%d]\n", addrOfVarPassed, bindReg);
													if (entry->isPassedByReference())
														fprintf(output, "MOV R%d, [R%d]\n", addrOfVarPassed, addrOfVarPassed);
													freeReg(debug);
													freeReg(debug);

													reg2 = getReg();
													fprintf(output, "MOV R%d, %d\n", reg2, i + 1);
													fprintf(output, "ADD R%d, R%d\n", reg2, reg1);
													fprintf(output, "MOV [R%d], R%d\n", reg2, addrOfVarPassed);
													freeReg(debug);

													freeReg(debug);
												}
												break;
											}
										case ARRAY: {
												if (actArgEntry->isGlobal()) {
													int addrOfVarPassed = codeGen(actualArg->getPTR1(), output);	//	Stores the offset needed
													reg2 = getReg();							//	Stores the Base Address of variable
													fprintf(output, "MOV R%d, %d\n", reg2, actArgEntry->getBinding());
													fprintf(output, "ADD R%d, R%d\n", addrOfVarPassed, reg2);
													freeReg(debug);

													reg2 = getReg();
													fprintf(output, "MOV R%d, %d\n", reg2, i + 1);
													fprintf(output, "ADD R%d, R%d\n", reg2, reg1);
													fprintf(output, "MOV [R%d], R%d\n", reg2, addrOfVarPassed);
													freeReg(debug);
													break;
												}
												break;
											}
									}
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
							fprintf(output, "MOV R%d, %llu\n", reg2, entry->getArgs().size() + 1);
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
					case VARIABLE: {
							int baseReg = getReg();
							if (entry->isGlobal()) {
								fprintf(output, "MOV R%d, [%d]\n", baseReg, entry->getBinding());
							}
							else {
								fprintf(output, "MOV R%d, BP\n", baseReg);
								int bindReg = getReg();
								fprintf(output, "MOV R%d, %d\n", bindReg, entry->getBinding());
								fprintf(output, "ADD R%d, R%d\n", bindReg, baseReg);
								if (entry->isPassedByReference())
									fprintf(output, "MOV R%d, [R%d]\n", bindReg, bindReg);
								fprintf(output, "MOV R%d, [R%d]\n", baseReg, bindReg);
								freeReg(debug);
							}
							return baseReg;
							break;
						}
					case ARRAY: {
							if (entry->isGlobal()) {
								int reg1 = codeGen(node->getPTR1(), output);	//	Stores the offset needed
								int reg2 = getReg();							//	Stores the Base Address of variable
								fprintf(output, "MOV R%d, %d\n", reg2, entry->getBinding());
								fprintf(output, "ADD R%d, R%d\n", reg1, reg2);
								fprintf(output, "MOV R%d, [R%d]\n", reg1, reg1);
								freeReg(debug);
								return reg1;
								break;
							}
						}
				}
				break;
			}
		case READ: {
				SNode *location = node->getPTR2();
				symbolNode *entry = location->getEntry();
				switch (getUsageType(entry)) {
					case FUNCTION: {
							break;
						}
					case VARIABLE: {
							int inputReg = getReg();
							fprintf(output, "IN R%d\n", inputReg);
							if (entry->isGlobal()) {
								fprintf(output, "MOV [%d], R%d\n", entry->getBinding(), inputReg);
							}
							else {
								int baseReg = getReg();
								fprintf(output, "MOV R%d, BP\n", baseReg);
								int bindReg = getReg();
								fprintf(output, "MOV R%d, %d\n", bindReg, entry->getBinding());
								fprintf(output, "ADD R%d, R%d\n", bindReg, baseReg);
								if (entry->isPassedByReference())
									fprintf(output, "MOV R%d, [R%d]\n", bindReg, bindReg);
								fprintf(output, "MOV [R%d], R%d\n", bindReg, inputReg);
								freeReg(debug);
								freeReg(debug);
							}
							freeReg(debug);
							break;
						}
					case ARRAY: {
							int inputReg = getReg();
							fprintf(output, "IN R%d\n", inputReg);
							if (entry->isGlobal()) {
								int offsetReg = codeGen(location->getPTR1(), output);
								int bindReg = getReg();
								fprintf(output, "MOV R%d, %d\n", bindReg, entry->getBinding());
								fprintf(output, "ADD R%d, R%d\n", offsetReg, bindReg);
								fprintf(output, "MOV [R%d], R%d\n", offsetReg, inputReg);
								freeReg();
								freeReg();
							}
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
					case VARIABLE: {
							int inputReg = codeGen(rValue, output);
							if (entry->isGlobal()) {
								fprintf(output, "MOV [%d], R%d\n", entry->getBinding(), inputReg);
							}
							else {
								int baseReg = getReg();
								fprintf(output, "MOV R%d, BP\n", baseReg);
								int bindReg = getReg();
								fprintf(output, "MOV R%d, %d\n", bindReg, entry->getBinding());
								fprintf(output, "ADD R%d, R%d\n", bindReg, baseReg);
								if (entry->isPassedByReference())
									fprintf(output, "MOV R%d, [R%d]\n", bindReg, bindReg);
								fprintf(output, "MOV [R%d], R%d\n", bindReg, inputReg);
								freeReg(debug);
								freeReg(debug);
							}
							freeReg(debug);
							break;
						}
					case ARRAY: {
							int inputReg = codeGen(rValue, output);
							if (entry->isGlobal()) {
								int offsetReg = codeGen(lValue->getPTR1(), output);
								int bindReg = getReg();
								fprintf(output, "MOV R%d, %d\n", bindReg, entry->getBinding());
								fprintf(output, "ADD R%d, R%d\n", offsetReg, bindReg);
								fprintf(output, "MOV [R%d], R%d\n", offsetReg, inputReg);
								freeReg();
								freeReg();
							}
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
				// std::cout << "Output = " << execute(x->getPTR2()) << "\n";
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
				int reg1 = codeGen(node->getPTR1(), output);	//	Stores the result of LHS
				int reg2 = codeGen(node->getPTR2(), output); 	//	Stores the result of RHS
				fprintf(output, "ADD R%d R%d\n", reg1, reg2);
				freeReg(debug);
				return reg1;
				break;
			}
		case '-': {
				int reg1 = codeGen(node->getPTR1(), output);	//	Stores the result of LHS
				int reg2 = codeGen(node->getPTR2(), output); 	//	Stores the result of RHS
				fprintf(output, "SUB R%d R%d\n", reg1, reg2);
				freeReg(debug);
				return reg1;
				break;
			}
		case '*': {
				int reg1 = codeGen(node->getPTR1(), output);	//	Stores the result of LHS
				int reg2 = codeGen(node->getPTR2(), output); 	//	Stores the result of RHS
				fprintf(output, "MUL R%d R%d\n", reg1, reg2);
				freeReg(debug);
				return reg1;
				break;
			}
		case '/': {
				int reg1 = codeGen(node->getPTR1(), output);	//	Stores the result of LHS
				int reg2 = codeGen(node->getPTR2(), output); 	//	Stores the result of RHS
				fprintf(output, "DIV R%d R%d\n", reg1, reg2);
				freeReg(debug);
				return reg1;
				break;
			}
		case '<': {
				int reg1 = codeGen(node->getPTR1(), output);	//	Stores the result of LHS
				int reg2 = codeGen(node->getPTR2(), output); 	//	Stores the result of RHS
				fprintf(output, "LT R%d R%d\n", reg1, reg2);
				freeReg(debug);
				return reg1;
				break;
			}
		case '>': {
				int reg1 = codeGen(node->getPTR1(), output);	//	Stores the result of LHS
				int reg2 = codeGen(node->getPTR2(), output); 	//	Stores the result of RHS
				fprintf(output, "GT R%d R%d\n", reg1, reg2);
				freeReg(debug);
				return reg1;
				break;
			}
		case '^': {
				int reg1 = codeGen(node->getPTR1(), output);	//	Stores the result of LHS
				int reg2 = codeGen(node->getPTR2(), output); 	//	Stores the result of RHS
				fprintf(output, "MOD R%d R%d\n", reg1, reg2);
				freeReg(debug);
				return reg1;
				break;
			}
		case LEQ: {
				int reg1 = codeGen(node->getPTR1(), output);	//	Stores the result of LHS
				int reg2 = codeGen(node->getPTR2(), output); 	//	Stores the result of RHS
				fprintf(output, "LE R%d R%d\n", reg1, reg2);
				freeReg(debug);
				return reg1;
				break;
			}
		case GEQ: {
				int reg1 = codeGen(node->getPTR1(), output);	//	Stores the result of LHS
				int reg2 = codeGen(node->getPTR2(), output); 	//	Stores the result of RHS
				fprintf(output, "GE R%d R%d\n", reg1, reg2);
				freeReg(debug);
				return reg1;
				break;
			}
		case ISEQ: {
				int reg1 = codeGen(node->getPTR1(), output);	//	Stores the result of LHS
				int reg2 = codeGen(node->getPTR2(), output); 	//	Stores the result of RHS
				fprintf(output, "EQ R%d R%d\n", reg1, reg2);
				freeReg(debug);
				return reg1;
				break;
			}
		case NOTEQ: {
				int reg1 = codeGen(node->getPTR1(), output);	//	Stores the result of LHS
				int reg2 = codeGen(node->getPTR2(), output); 	//	Stores the result of RHS
				fprintf(output, "NE R%d R%d\n", reg1, reg2);
				freeReg(debug);
				return reg1;
				break;
			}
		case AND: {
				int reg1 = codeGen(node->getPTR1(), output);	//	Stores the result of LHS
				int reg2 = codeGen(node->getPTR2(), output); 	//	Stores the result of RHS
				fprintf(output, "MUL R%d R%d\n", reg1, reg2);
				freeReg(debug);
				return reg1;
				break;
			}
		case OR: {
				int reg1 = codeGen(node->getPTR1(), output);	//	Stores the result of LHS
				int reg2 = codeGen(node->getPTR2(), output);	//	Stores the result of RHS
				fprintf(output, "ADD R%d R%d\n", reg1, reg2);
				fprintf(output, "MOV R%d, 0\n", reg2);
				fprintf(output, "NE R%d R%d\n", reg1, reg2);
				freeReg(debug);
				return reg1;
				break;
			}
		case NOT: {
				int reg1 = codeGen(node->getPTR1(), output);	//	Stores the result of Expr
				int reg2 = getReg();							//	Stores the '0' for Negative
				fprintf(output, "MOV R%d 0\n", reg2);
				fprintf(output, "EQ R%d R%d\n", reg1, reg2);
				freeReg(debug);
				return reg1;
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
		if(getUsageType(i)==FUNCTION)
			declaredFunctions.insert(i);
	for (SNode *i = program->getNext(); i; i = i->getNext())
		declaredFunctions.erase(i->getEntry());
	if (declaredFunctions.empty())
		return PASS;
	for (auto i : declaredFunctions) {
		error("'"+i->getName()+"' Declared but not Defined", program->lineNo, program->colNo);
	}
	return FAIL;
}
