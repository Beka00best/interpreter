#include <lexem.h>
#include <bits/stdc++.h>
#include <semantic.h>
#include <syntax.h>
#include <lexical.h>

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
		clear_vector(recycle);
	}
	// clear_vector(infix);
	// clear_vector(postfix);
	clear_vector(recycle);
	return 0;
}