#ifndef UTIL_H
#define UTIL_H

#include <string>
#include "syntaxTree.h"

#define ARRAY 0
#define VARIABLE 1
#define FUNCTION 2

void error (const std::string &s, int l, int c);
SNode *processFunctionHeader(SNode *datatype, SNode *functionID, SNode *arguments, SNode *declarations, SNode *globalScope);
SNode *variableAccess(SNode *variableID, SNode *indexExpr, SNode *Scope[2], int);
bool processDeclerations(symbolNode *Table, SNode *$2);
int codeGen(SNode *node, FILE *output);
int generateCode(SNode *start, FILE *output);
int getUsageType(symbolNode *entry);
int checkFunctionDeclared(SNode *program);

#endif // SYNTAXTREE_H
