#include <lexem.h>
#include <const.h>
#include <lexical.h>
#include <semantic.h>
#include <syntax.h>
#include <bits/stdc++.h>

std::map<std::string, int> varTable;
std::map<std::string, int> labelsTable;
std::map<std::string, std::vector<int>> arrayTable;
std::map<std::string, int> arraySizeTable;

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

Goto::Goto() {}

Goto::Goto(OPERATOR opertype) : Oper(SYMBOLS[opertype]){
	row = INT32_MIN;
	oper = opertype;
}

Array::Array() {}

Array::Array(std::string str) : Lexem(ARRTYPE) {
	arrayName = str;
}

Array::Array(int size_) {
	if (size_ < 0) {
		perror("Error: array");
	}
	if (!arraySizeTable.count(arrayName)) {
		arraySizeTable[arrayName] = size_;
		// int *values = new int[size_];
		// std::fill(values, values + size_, 0);
		// memset(values, 0, size_);
		for (int i = 0; i < size_; i++) {
			data.push_back(0);
		}
		arrayTable[arrayName] = data;
	} else {
		perror("WTF allocate?");
	}
}

int Number::getType() {
	return NUMBER;
}

int Number::getValue() const {
	return value;
}

void Number::print() {
	std::cout << "[" << value << "]";
}

int Oper::getType() {
	return opertype;
}

int Oper::getPriority() {
	return PRIORITY[opertype];
}

void Oper::print() {
	std::cout << "[" << SYMBOLS[opertype] << "]";
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

int Variable::getType() {
	return TYPE_VAR;
}

int Variable::getValue() const{
	return varTable[name];
}

void Variable::setValue(int value_) {
	varTable[name] = value_;
}

void Variable::print() {
	std::cout << "[" << name << "(" << varTable[name] << ")" << "]";
}

bool Variable::inLabelTable() {
    if (labelsTable.find(name) != labelsTable.end()) {
        return true;
    }
    return false;
}

std::string Variable::getName() {
	return name;
}

void Goto::setRow(int row) {
	Goto::row = row;
}

void Goto::setRow(const std::string name) {
	row = labelsTable[name];
}

int Goto::getRow() {
	return row;
}

void Goto::print() {
	std :: cout << "[<row "<< row << ">" << SYMBOLS[oper] << "]" ;
}

int Goto::getType() {
	return oper;
}

void Array::setIndex(int index_) {
	if (index_ < 0 || (arraySizeTable.count(arrayName) && index_ > arraySizeTable[arrayName])) {
		perror("Invalid index");
	}
	index = index_;
}

int Array::getValue() const{
	return data[index]; 
}

void Array::setValue(int value) {
	data[index] = value;
}

void Array::print() {
	std::cout << arrayName << ": ";
	for (std::vector<int>::iterator it=data.begin(); it!=data.end(); ++it)
    std::cout << ' ' << *it;
}

void clear_vector(std::vector<Lexem *> v) {
    if (v.empty())
        return;
    for (auto it: v) {
        delete it;
    }
}

void clear_lines(std::vector<std::vector<Lexem *>> infix) {
	for (int i = 0; i < infix.size(); ++i) {
		clear_vector(infix[i]);
	}
}

void print_vector(std::vector<Lexem *> infix) {
	for (int i = 0; i < infix.size(); i++) {
		if (infix[i] == nullptr) {
			continue;
		}
		infix[i]->print();
		std::cout << " ";
	}
	std::cout << std::endl;
}

void print_vector_vector(std::vector<std::vector<Lexem *>> infix) {
	for (int i = 0; i < (int)infix.size(); i++) {
		std::cout << i << ": ";
		print_vector(infix[i]);
	}
}

void printMap() {
    std::cout << "VarTable" << std::endl;
    for (std::map<std::string,int>::iterator it = varTable.begin(); it != varTable.end(); it++) {
        std::cout << it->first << " = " << it->second << std::endl;
    }
}

std::vector<Lexem *> recycle;
Lexem *ptr = nullptr; 