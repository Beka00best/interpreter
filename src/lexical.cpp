#include <lexical.h>
#include <bits/stdc++.h>
#include <lexem.h>
#include <const.h>

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
	while (is_symbol(codeline[i]) || isdigit(codeline[i])) {
		name += codeline[i];
		i++;
	}
	// std::cout << name << std::endl;
	for (int j = 0; j < OP_NUM; j++) {
		if(SYMBOLS[j] == name) {
			// can be improved
			for (int k = 0; k < 6; k++) {
				if(SYMBOLS[k] == name) {
					ptr = new Goto(static_cast<OPERATOR>(j));
					infix.push_back(ptr);
					recycle.push_back(ptr);
					return;
				}
			}
			ptr = new Oper(SYMBOLS[j]);
			infix.push_back(ptr);
			recycle.push_back(ptr);
			return;
		}
	}
	// i--;
	infix.push_back(new Variable(name));
}

void do_oper(std::vector<Lexem *> &infix, std::string codeline, int &i) {
	int len = OP_NUM, init;
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
	ptr = new Oper(SYMBOLS[cnt]); 
	infix.push_back(ptr);
	recycle.push_back(ptr);
}