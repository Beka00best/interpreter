#include <semantic.h>
#include <bits/stdc++.h>
#include <lexem.h>
#include <const.h>

int evaluatePoliz(std::vector<Lexem *> poliz, int row) {
	int value = 0;
	int val;
	Lexem *l, *r;
	std::stack<Lexem *> opstack;
	for (int i = 0; i < poliz.size(); ++i) {
		if (poliz[i] == nullptr) {
			continue;
		}
		switch (poliz[i]->getLexType()) {
		case FUNC:
			std::cout << "lf fjjfjfjfjfj" << std::endl;
			break;
		case ARRTYPE:
		case TYPE_VAR:
		case NUMBER:
			opstack.push(poliz[i]);
			break;
		case OPER:
			if (poliz[i]->getType() == PRINT) {
				std::cout << "PRINT: " << opstack.top() -> getValue() << std::endl;
				break;
			}
			if (poliz[i]->getType() == GOTO ||
				poliz[i]->getType() == ELSE ||
				poliz[i]->getType() == ENDWHILE) {
				Goto *lexemgoto = (Goto *)poliz[i];
				return lexemgoto->getRow();
			} else if (poliz[i]->getType() == IF || poliz[i]->getType() == WHILE) {
				Goto *lexemgoto = (Goto *)poliz[i];
				Lexem *rvalue = opstack.top();
				opstack.pop();
				if (!(rvalue->getValue())) {
					return lexemgoto->getRow();
				}
				break;
			}
			r = opstack.top();
			opstack.pop();
			l = opstack.top();
			opstack.pop();
			if (poliz[i]->getType() == LVALUE) {
				Lexem *arrayElem = new Array(opstack.top()->getName());
				opstack.pop();
				((Array *)arrayElem)->setIndex(l->getValue());
				((Array *)arrayElem)->setValue(r->getValue());
				recycle.push_back(arrayElem);
				break;
			}
			if(poliz[i]->getType() == ASSIGN) {
				val = assignOper(l, r);
			} else {
				val = ((Oper *)poliz[i])->getValue(l, r);
			}
			ptr = new Number(val);
			opstack.push(ptr);
			recycle.push_back(ptr);
			break;
		}
	}
	if (!opstack.empty()) {
		value = opstack.top()->getValue();
		opstack.pop();
	}
	if (value) {
		// std::cout << value << std::endl; 
	}
	// opstack.pop();
	return row + 1;
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