#include <lexical.h>
#include <bits/stdc++.h>
#include <lexem.h>
#include <const.h>

int Lbr = 0;

std::vector<Lexem *> parseLexem(std::string codeline) {
	std::vector<Lexem *> infix;
	Lexem *ptr = nullptr;
	for (int i = 0; i < codeline.size();) {
		if (isspace(codeline[i])) {
			i++;
			continue;
		} 
		if (isdigit(codeline[i])) {
			do_digit(infix, codeline, i);
		} else {
			ptr = do_oper(infix, codeline, i);
			if (ptr == nullptr) {
				do_name(infix, codeline, i);
			}
		}
	}
	Lbr = 0;
	return infix;
}

std::string to_str(char ch) {
	std::string str(1, ch);
	return str;
}

void do_digit(std::vector<Lexem *> &infix, std::string codeline, int &i) {
	int number = 0;
	Lexem *ptr = nullptr;
	while (isdigit(codeline[i])) {
		number = number * 10 + codeline[i] - '0';
		i++;
	}
	ptr = new Number(number);
	infix.push_back(ptr);
	recycle.push_back(ptr);
}

bool is_oper(std::string oper) {
	for (int i = 0; i < OP_NUM; i++) {
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
	Lexem *ptr = nullptr;
	if (!is_symbol(codeline[i])) {
		return;
	}
	while (is_symbol(codeline[i]) || isdigit(codeline[i])) {
		name += codeline[i];
		i++;
	}
	if (i < codeline.size() && (codeline[i] == '[')) {
		ptr = new Array(name);
	} else {
		ptr = new Variable(name); 
	}
	infix.push_back(ptr);
	recycle.push_back(ptr);
}

Lexem *do_oper(std::vector<Lexem *> &infix, std::string codeline, int &i) {
	int init;
	int cnt;
	Lexem *ptr = nullptr;
	for (int j = 0;  j < OP_NUM; j++) {
		init = SYMBOLS[j].size();
		if (codeline.substr(i, init) == SYMBOLS[j]) {
			i += init;
			if (j == GOTO || j == IF || j == ELSE || j == WHILE || j == ENDWHILE) {
				ptr = new Goto(static_cast<OPERATOR>(j));
			} else if (j == LSQUBR) {
				if (!Lbr) {
					Lbr = 1;
					ptr = new Oper(SYMBOLS[LVALUE]);
				} else {
					ptr = new Oper(SYMBOLS[RVALUE]);
				}
			} else {
				ptr = new Oper(SYMBOLS[j]); 
			}
			infix.push_back(ptr);
			recycle.push_back(ptr);
			return ptr;
		}
	}
	return nullptr;
}