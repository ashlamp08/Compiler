#include <iostream>
#include <cmath>
#include "exptree.h"

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
char Pass[] = { -61, -60, -60, -60, -60, -60, -60, -60, 0};
#endif


Node::Node(int value) {
	val = value;
	op = 0;
	left = right = nullptr;
}
Node::Node(char oper) {
	op = oper;
	val = 0;
	left = right = nullptr;
}
int Node::evaluate() {
	switch (op) {
		case 0:
			return val;
		case '+':
			return left->evaluate() + right->evaluate();
		case '-':
			return left->evaluate() - right->evaluate();
		case '*':
			return left->evaluate() * right->evaluate();
		case '/':
			return left->evaluate() / right->evaluate();
		case '^':
			return pow(left->evaluate(), right->evaluate());
	}
	return -1;
}
void Node::print() {
	print(this->right, "", 0);
	if (this->op == 0)
		std::cout << this->val << "\n";
	else
		std::cout << this->op << "\n";
	print(this->left, "", 1);
}
void Node::print(Node *bst, std::string str, int side) {
	if (bst == nullptr)
		return;
	if (side) {
		print(bst->right, str + leftDown, 0);
		if (bst->op == 0)
			std::cout << str <<Down<< bst->val << "\n";
		else
			std::cout << str <<Down<< bst->op << "\n";
		print(bst->left, str + "\t", 1);
	}
	else {
		print(bst->right, str + "\t", 0);
		if (bst->op == 0)
			std::cout << str <<Up<< bst->val << "\n";
		else
			std::cout << str << Up<<bst->op << "\n";
		print(bst->left, str + leftDown, 1);
	}
	/*if (side % 2) {
		print(bst->right, str + rightUp, 0);
		if (bst->op == 0)
			std::cout << str << Down << bst->val << "\n";
		else
			std::cout << str << Down << bst->op << "\n";
		print(bst->left, str + rightDown, 1);
	}
	else {
		print(bst->right, str + leftUp, 0);
		if (bst->op == 0)
			std::cout << str << Up << bst->val << "\n";
		else
			std::cout << str << Up << bst->op << "\n";
		print(bst->left, str + leftDown, 1);
	}*/
}