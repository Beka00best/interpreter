#include <syntax.h>
#include <bits/stdc++.h>
#include <const.h>
#include <lexem.h>


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
