#include <bits/stdc++.h>

enum TYPE_INFO {
	NUMBER,
	OPER
};

enum OPERATOR {
	LBRACKET,
	RBRACKET,
	PLUS,
	MINUS,
	MULTIPLY
};

int PRIORITY[] = {
	-1, -1,
	0, 0,
	1
};

std::string SYMBOLS[] = {
	"(", ")", "+", "-", "*"
};

class Lexem {
protected:
	TYPE_INFO type;
public:
	Lexem();
	Lexem(TYPE_INFO t) : type(t) {}
	virtual void print() {}
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

Lexem::Lexem() {}

Oper::Oper() {}

Oper::Oper(std::string str) : Lexem(OPER) {
	if (str == "+") {
		opertype = PLUS;
	} else if (str == "-") {
		opertype = MINUS;
	} else if (str == "*") {
		opertype = MULTIPLY;
	} else if (str == "(") {
		opertype = LBRACKET;
	} else if (str == ")") {
		opertype = RBRACKET;
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
	}
}

TYPE_INFO Lexem::getLexType() {
	return type;
}

void print_vector(std::vector<Lexem *> infix) {
	// for (std::vector<Lexem *>::const_iterator i = infix.begin(); i != infix.end(); ++i) {
	//   i->print();
	// }
	for (int i = 0; i < infix.size(); i++) {
		infix[i]->print();
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
	i--;
	infix.push_back(new Number(number));
}

std::vector<Lexem *> parseLexem(std::string codeline) {
	std::vector<Lexem *> infix;
	for (int i = 0; i < codeline.size(); i++) {
		if (isspace(codeline[i])) {
			continue;
		} else if (isdigit(codeline[i])) {
			do_digit(infix, codeline, i);
		} else {
			infix.push_back(new Oper(to_str(codeline[i])));
		}
	}
	return infix;
}

std::vector<Lexem *> buildPoliz(std::vector<Lexem *> infix) {
	std::vector<Lexem *> postfix;
	std::stack<Oper *> opstack;
	OPERATOR current;
	for (int i = 0; i < infix.size(); i++) {
		switch (infix[i]->getLexType()) {
		case NUMBER:
			postfix.push_back(infix[i]);
			break;
		case OPER:
			current = ((Oper *)infix[i])->getType();
			// if (opstack.empty())
			switch (current) {
			case LBRACKET:
				opstack.push((Oper *)infix[i]);
				break;
			case RBRACKET:
				while (opstack.top()->getType() != LBRACKET) {
					postfix.push_back(opstack.top());
					opstack.pop();
				}
				opstack.pop();
				break;
			case PLUS:
			case MINUS:
			case MULTIPLY:
				while (!opstack.empty() && (opstack.top()->getPriority()) >= ((Oper *)infix[i])->getPriority()) {
					postfix.push_back(opstack.top());
					opstack.pop();
				}
				opstack.push((Oper *)infix[i]);
				break;
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
	int l, r;
	std::stack<Number *> opstack;
	for (int i = 0; i < poliz.size(); ++i) {
		switch (poliz[i]->getLexType()) {
		case NUMBER:
			opstack.push((Number *)poliz[i]);
			break;
		case OPER:
			r = opstack.top()->getValue();
			opstack.pop();
			l = opstack.top()->getValue();
			opstack.pop();
			int val = ((Oper *)poliz[i])->getValue(l, r);
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
		postfix = buildPoliz(infix);
		print_vector(postfix);
		value = evaluatePoliz(postfix);
		std::cout << value << std::endl;
	}
	return 0;
}