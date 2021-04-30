#include <lexem.h>
#include <const.h>
#include <lexical.h>
#include <semantic.h>
#include <syntax.h>
#include <bits/stdc++.h>

std::map<std::string, int> varTable;
std::map<std::string, int> labelsTable;
std::map<std::string, int *> arrayTable;
std::map<std::string, int> arraySizeTable;
std::map<std::string, int> functionsTable;
std::map<std::string, int> returnRow;
std::stack<Lexem *> returnFunctionStack;
std::stack<Lexem *> prevVariables;
std::stack<Space> globalSpace;

Lexem::Lexem() {}

Lexem::Lexem(TYPE_INFO t) : type(t) {}

Lexem::~Lexem() {}

Number::Number(int number = 0) : Lexem(NUMBER), value(number) {}

Oper::Oper() {}

Oper::Oper(OPERATOR opertype) : opertype(opertype), Lexem(OPER) {}

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

Function::Function() {}

Function::Function(std::string str) : Lexem(FUNC) {
	functionName = str;
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

std::string Number::getName() {
	return "";
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

std::string Oper::getName() {
	return "";
}

int Oper::getValue(Lexem *left, Lexem *right) {
	Array *arrayElem = nullptr;
	switch (opertype) {
	case MINUS:
		return left->getValue() - right->getValue();
	case PLUS:
		return left->getValue() + right->getValue();
	case MULTIPLY:
		return left->getValue() * right->getValue();
	case OR:
		return left->getValue() || right->getValue(); 
	case AND:
		return left->getValue() && right->getValue(); 
	case BITOR:
		return left->getValue() | right->getValue(); 
	case XOR:
		return left->getValue() ^ right->getValue();
	case BITAND:
		return left->getValue() & right->getValue();
	case EQ:
		return left->getValue() == right->getValue();
	case NEQ:
		return left->getValue() != right->getValue();
	case LEQ:
		return left->getValue() <= right->getValue();
	case LT:
		return left->getValue() < right->getValue();
	case GEQ:
		return left->getValue() >= right->getValue();
	case GT:
		return left->getValue() > right->getValue();
	case SHL:
		return left->getValue() << right->getValue();
	case SHR:
		return left->getValue() >> right->getValue();
	case DIV:
		return left->getValue() / right->getValue();
	case MOD:
		return left->getValue() % right->getValue();
	case SIZE:
		// ((Array *)left)->setSize(right->getValue());
		arraySizeTable[left->getName()] = right->getValue();
		return 0;
	case RVALUE:
		return arrayTable[left->getName()][right->getValue()];
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

void Array::setSize(int size_) {
	if (size_ < 0) {
		perror("Error: array");
	}
	if (!arraySizeTable.count(arrayName)) {
		arraySizeTable[arrayName] = size_;
		int *ptr = new int[size_];
		for (int i = 0; i < size_; i++) {
			ptr[i] = 0;
		}
		arrayTable[arrayName] = ptr;
	} else {
		perror("WTF allocate?");
	}
}

void Array::setIndex(int index_) {
	if (index_ < 0 || (arraySizeTable.count(arrayName) && index_ > arraySizeTable[arrayName])) {
		perror("Invalid index");
	}
	if (!arrayTable.count(arrayName)) {
		int size = arraySizeTable[arrayName];
		int *ptr = new int[size];
		for (int i = 0; i < size; i++) {
			ptr[i] = 0;
		}
		arrayTable[arrayName] = ptr;
	}
	index = index_;
}

int Array::getValue() const{
	return (arrayTable[arrayName])[index]; 
}

void Array::setValue(int value) {
	(arrayTable[arrayName])[index] = value;
}

void Array::print() {
	std::cout << arrayName << ": ";
	for (int i = 0; i < arraySizeTable[arrayName]; i++) {
		std::cout << (arrayTable[arrayName])[i] << ' ';
	}
}

std::string Array::getName() {
	return arrayName;
}

void Function::setRow(int row) {
	jumpRow = row;
	functionsTable[functionName] = row;
}

void Function::setNumberArg(int num) {
	numberArgument = num;
}

int Function::getRow() {
	return jumpRow;
}

int Function::getNumberArg() {
	return numberArgument;
}

std::string Function::getName() {
	return functionName;
}

void Function::print() {
	std::cout << "[" << functionName << " -> " << functionsTable[functionName] << "]";
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

void print_arrs() {
	std::string key;
	for (auto & unit: arrayTable) {
		key = unit.first;
		std::cout << key << ": " << std::endl;
		for (unsigned i = 0; i < (unsigned)(arraySizeTable[key]); i++) {
			std::cout << (arrayTable[key])[i] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int findMain(std::vector<std::vector<Lexem *>> postfix) {
	int begin = 0;
	for (int i = 0; i < postfix.size(); i++) {
		for (int j = 0; j < postfix[i].size(); j++) {
			if (postfix[i][j] == nullptr) {
				continue;
			}
			if (postfix[i][j] -> getLexType() == OPER && postfix[i][j] -> getType() == RETURN) {
				begin = i + 1;
			}
		}
	}
	return begin;
}

std::vector<Lexem *> recycle;
Lexem *ptr = nullptr; 