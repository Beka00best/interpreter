#include <lexem.h>
#include <bits/stdc++.h>
#include <semantic.h>
#include <syntax.h>
#include <lexical.h>

Space space;
RetAddress retaddr;

int main() {
	globalSpace.push(space);
	StackReturnAddress.push(retaddr);
	std::string codeline;
	std::vector< std::vector<Lexem *>> infix;
	std::vector< std::vector<Lexem *>> postfix;
	int value;
	while (std::getline(std::cin, codeline) && codeline != "exit") {
		infix.push_back(parseLexem(codeline));
	}
	std::cout << "infix:" << std::endl;
	print_vector_vector(infix);		
	for (int row = 0; row < infix.size(); ++row) {
		initLabels(infix[row], row);
	}
	std::cout << "initlabel:" << std::endl;
	print_vector_vector(infix);
	initJumps(infix);
	// printMap();
	std::cout << "initJumps" << std::endl;
	print_vector_vector(infix);
	for (int row = 0; row < (int)infix.size(); ++row) {
		postfix.push_back(buildPoliz(infix[row]));
	}
	std::cout << "postfix:" << std::endl;
	print_vector_vector(postfix);	
	
	// int row = 0;
	int row = findMain(postfix);
	// std::cout << "row " << row << std::endl;
	while (0 <= row and row < (int)postfix.size()) {
		// std::cout << "row eval: " << row << std::endl;
		row = evaluatePoliz(postfix, row, &value);
	}
	// std::cout << "eval:" << std::endl;
	// print_vector_vector(postfix);
	print_arrs();
	// clear_vector(recycle);
	return 0;
}