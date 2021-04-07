#include <lexem.h>
#include <bits/stdc++.h>
#include <semantic.h>
#include <syntax.h>
#include <lexical.h>

int main() {
	std::string codeline;
	std::vector< std::vector<Lexem *>> infix;
	std::vector< std::vector<Lexem *>> postfix;
	int value;

	while (std::getline(std::cin, codeline)) {
		infix.push_back(parseLexem(codeline));
	}
	for (int row = 0; row < infix.size(); ++row) {
		initLabels(infix[row], row);
	}
	initJumps(infix);
	for (int row = 0; row < (int)infix.size(); ++row) {
		postfix.push_back(buildPoliz(infix[row]));
	}
	int row = 0;
	while (0 <= row and row < (int)postfix.size()) {
		row = evaluatePoliz(postfix[row], row);
	}
	clear_vector(recycle);
	return 0;
}