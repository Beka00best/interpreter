#include <bits/stdc++.h>

std::map<std::string, int> varTable;
Lexem *ptr = nullptr;

enum TYPE_INFO {
	NUMBER,
	OPER,
	TYPE_VAR
};

enum OPERATOR {
	LBRACKET, RBRACKET,
	ASSIGN,
	OR,
	AND,
	BITOR,
	XOR,
	BITAND,
	EQ, NEQ,
	SHL, SHR,
	LEQ, LT,
	GEQ, GT,
	PLUS, MINUS,
	MULTIPLY, DIV, MOD
};

int PRIORITY[] = {
	-1, -1,
	0,
	1,
	2,
	3,
	4,
	5,
	6, 6,
	8, 8,
	7, 7,
	7, 7,
	9, 9,
	10, 10, 10
};

std::string SYMBOLS[] = {
	"(", ")", 
	"=",
	"or",
	"and",
	"|",
	"^",
	"&",
	"==", "!=",
	"<<", ">>",
	"<=", "<",
	">=", ">",
	"+", "-", 
	"*", "/", "%"
};

class Lexem {
protected:
	TYPE_INFO type;
public:
	Lexem();
	Lexem(TYPE_INFO t) : type(t) {}
	virtual void print() {}
	int virtual getValue() const {}
	TYPE_INFO getLexType();
};

class Number : public Lexem {
	int value;
public:
	Number(int number = 0) : Lexem(NUMBER), value(number) {}
	int getValue() const;
	void print();
};

class Oper : public Lexem {
	OPERATOR opertype;
public:
	Oper();
	Oper(std::string);
	OPERATOR getType();
	int getPriority();
	int getValue(const Number &left, const Number &right);
	void print();
};

class Variable : public Lexem {
	std::string name;
public:
	Variable(std::string str) : Lexem(TYPE_VAR), name(str) {}
	int getValue() const;
	void setValue(int value_);
	void print();
};

Lexem::Lexem() {}

Oper::Oper() {}

Oper::Oper(std::string str) : Lexem(OPER) {
	for (int i = 0; i < sizeof(SYMBOLS) / sizeof(std::string); i++) {
		if(SYMBOLS[i] == str) {
			opertype = (OPERATOR)i;
		}
	}
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

int Variable::getValue() const {
	return varTable[name];
}

void Variable::setValue(int value_) {
	varTable[name] = value_;
}

void Variable::print() {
	std::cout << name << "(" << varTable[name] << ")";
}

void print_vector(std::vector<Lexem *> infix) {
	for (int i = 0; i < infix.size(); i++) {
		infix[i]->print();
		std::cout << " ";
	}
	std::cout << std::endl;
}

std::string to_str(char ch) {
	std::string str(1, ch);
	return str;
}

void do_digit(std::vector<Lexem *> &infix, std::string codeline, int &i) {
	int number = 0;
	while (isdigit(codeline[i])) {
		number = number * 10 + codeline[i] - '0';
		i++;
	}
	// i--;
	
	infix.push_back(new Number(number));
}

bool is_oper(std::string oper) {
	for (int i = 0; i < sizeof(SYMBOLS) / sizeof(std::string); i++) {
		if(SYMBOLS[i] == oper) {
			return true;
		}
	}
	return false;
}

bool is_symbol(char ch) {
	if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || ch == '_') {
		return true;
	}
	return false;
}

void do_name(std::vector<Lexem *> &infix, std::string codeline, int &i) {
	std::string name;
	while (is_symbol(codeline[i]) || isdigit(codeline[i])) {
		name += codeline[i];
		i++;
	}
	std::cout << name << std::endl;
	for (int j = 0; j < sizeof(SYMBOLS) / sizeof(std::string); j++) {
		if(SYMBOLS[j] == name) {
			infix.push_back(new Oper(SYMBOLS[j]));
			return;
		}
	}
	// i--;
	infix.push_back(new Variable(name));
}

void do_oper(std::vector<Lexem *> &infix, std::string codeline, int &i) {
	int len = sizeof(SYMBOLS) / sizeof(std::string), init;
	int cnt;
	for (int j = 0;  j < len; j++) {
		init = SYMBOLS[j].size();
		if (codeline.substr(i, init) == SYMBOLS[j]) {
			// std::cout << j << " " << SYMBOLS[j] << std::endl;
			i += init;
			cnt = j;
		}
	}
	// i--;
	infix.push_back(new Oper(SYMBOLS[cnt]));
}


std::vector<Lexem *> parseLexem(std::string codeline) {
	std::vector<Lexem *> infix;
	for (int i = 0; i < codeline.size();) {
		if (isspace(codeline[i])) {
			i++;
			continue;
		} else if (isdigit(codeline[i])) {
			do_digit(infix, codeline, i);
		} else if (is_oper(to_str(codeline[i]))) {
			do_oper(infix, codeline, i);
		} else if (is_symbol(codeline[i])) {
			do_name(infix, codeline, i);
		}
		// } else {
		// 	do_name(infix, codeline, i);
		// }
	}
	return infix;
}

int assignOper(Lexem *l, Lexem *r) {
	int number;
	switch (r->getLexType()) {
		case NUMBER:
			number = ((Number *)r)->getValue();
			break;
		case TYPE_VAR:
			number = ((Variable *)r)->getValue();
			break;
	}
	((Variable *)l)->setValue(number);
	return number;
}

std::vector<Lexem *> buildPoliz(std::vector<Lexem *> infix) {
	std::vector<Lexem *> postfix;
	std::stack<Oper *> opstack;
	OPERATOR current;
	for (int i = 0; i < infix.size(); i++) {
		switch (infix[i]->getLexType()) {
		case TYPE_VAR:
		case NUMBER:
			postfix.push_back(infix[i]);
			break;
		case OPER:
			if(!opstack.empty()) {
				current = ((Oper *)infix[i])->getType();
				switch (current) {
				case RBRACKET:
					while (opstack.top()->getType() != LBRACKET) {
						postfix.push_back(opstack.top());
						opstack.pop();
					}
					if (!opstack.empty()) {
						opstack.pop();
					}
					break;
				case ASSIGN:
					if(opstack.top()->getType() == ASSIGN && ((Oper *)infix[i])->getType() == ASSIGN) {
						opstack.push((Oper *)infix[i]);				
					}
					break;
				default:
					while (!opstack.empty() && (opstack.top()->getPriority()) >= ((Oper *)infix[i])->getPriority()) {
						postfix.push_back(opstack.top());
						opstack.pop();
					}
					opstack.push((Oper *)infix[i]);
					break;
				}
			} else {
				opstack.push((Oper *)infix[i]);
			}
		}
	}
	while (!opstack.empty()) {
		postfix.push_back(opstack.top());
		opstack.pop();
	}
	return postfix;
}

int evaluatePoliz(std::vector<Lexem *> poliz) {
	int value = 0;
	int val;
	Lexem *l, *r;
	std::stack<Number *> opstack;
	for (int i = 0; i < poliz.size(); ++i) {
		switch (poliz[i]->getLexType()) {
		case TYPE_VAR:
		case NUMBER:
			opstack.push((Number *)poliz[i]);
			break;
		case OPER:
			r = opstack.top();
			opstack.pop();
			l = opstack.top();
			opstack.pop();
			if(((Oper *)poliz[i])->getType() == ASSIGN) {
				val = assignOper(l, r);
			} else {
				val = ((Oper *)poliz[i])->getValue((l)->getValue(), (r)->getValue());
			}
			opstack.push(new Number(val));
			break;
		}
	}
	value = opstack.top()->getValue();
	opstack.pop();
	return value;
}

int main() {
	std::string codeline;
	std::vector<Lexem *> infix;
	std::vector<Lexem *> postfix;
	int value;

	while (std::getline(std::cin, codeline)) {
		if (codeline == "exit") {
			return 0;
		}
		infix = parseLexem(codeline);
		print_vector(infix);
		postfix = buildPoliz(infix);
		print_vector(postfix);
		value = evaluatePoliz(postfix);
		std::cout << value << std::endl;
	}
	return 0;
}