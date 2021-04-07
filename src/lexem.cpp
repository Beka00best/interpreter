#include <lexem.h>
#include <const.h>
#include <lexical.h>
#include <semantic.h>
#include <syntax.h>
#include <bits/stdc++.h>

std::map<std::string, int> varTable;
std::map<std::string, int> labelsTable;

Lexem::Lexem() {}

Lexem::Lexem(TYPE_INFO t) : type(t) {}

Lexem::~Lexem() {}

Number::Number(int number = 0) : Lexem(NUMBER), value(number) {}

Oper::Oper() {}

Oper::Oper(OPERATOR opertype) : opertype(opertype) {}

Variable::Variable(std::string str) : Lexem(TYPE_VAR), name(str) {}

Oper::Oper(std::string str) : Lexem(OPER) {
	for (int i = 0; i < OP_NUM; i++) {
		if(SYMBOLS[i] == str) {
			opertype = (OPERATOR)i;
		}
	}
}

Goto::Goto(OPERATOR opertype) : Oper(opertype) {
	row = INT32_MIN;
}

int Number::getValue() const {
	return value;
}

void Number::print() {
	std::cout << value;
}

OPERATOR Oper::getType() {
	return opertype;
}

int Oper::getPriority() {
	return PRIORITY[opertype];
}

void Oper::print() {
	std::cout << SYMBOLS[opertype];
}

int Oper::getValue(const Number &left, const Number &right) {
	switch (opertype) {
	case MINUS:
		return left.getValue() - right.getValue();
	case PLUS:
		return left.getValue() + right.getValue();
	case MULTIPLY:
		return left.getValue() * right.getValue();
	case OR:
		return left.getValue() || right.getValue(); 
	case AND:
		return left.getValue() && right.getValue(); 
	case BITOR:
		return left.getValue() | right.getValue(); 
	case XOR:
		return left.getValue() ^ right.getValue();
	case BITAND:
		return left.getValue() & right.getValue();
	case EQ:
		return left.getValue() == right.getValue();
	case NEQ:
		return left.getValue() != right.getValue();
	case LEQ:
		return left.getValue() <= right.getValue();
	case LT:
		return left.getValue() < right.getValue();
	case GEQ:
		return left.getValue() >= right.getValue();
	case GT:
		return left.getValue() > right.getValue();
	case SHL:
		return left.getValue() << right.getValue();
	case SHR:
		return left.getValue() >> right.getValue();
	case DIV:
		return left.getValue() / right.getValue();
	case MOD:
		return left.getValue() % right.getValue();
	}
}

TYPE_INFO Lexem::getLexType() {
	return type;
}

int Variable::getValue() const{
	return varTable[name];
}

void Variable::setValue(int value_) {
	varTable[name] = value_;
}

void Variable::print() {
	std::cout << name << "(" << varTable[name] << ")";
}

std::string Variable::getName() {
	return name;
}

void Goto::setRow(int row) {
	Goto::row = row;
}

int Goto::getRow() {
	return row;
}

void Goto::print() {
	std :: cout << " [ < row " << row << " >" << " ] " ;
}

void clear_vector(std::vector<Lexem *> v) {
    if (v.empty())
        return;
    for (auto it: v) {
        delete it;
    }
}

void print_vector(std::vector<Lexem *> infix) {
	for (int i = 0; i < infix.size(); i++) {
		infix[i]->print();
		std::cout << " ";
	}
	std::cout << std::endl;
}

std::vector<Lexem *> recycle;
Lexem *ptr = nullptr; 