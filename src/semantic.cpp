#include <semantic.h>
#include <bits/stdc++.h>
#include <lexem.h>
#include <const.h>

int evaluatePoliz(std::vector<Lexem *> poliz, int row) {
	int value = 0;
	int val;
	Lexem *l, *r;
	std::stack<Number *> opstack;
	for (int i = 0; i < poliz.size(); ++i) {
		if (poliz[i] == nullptr) {
			continue;
		}
		switch (poliz[i]->getLexType()) {
		case TYPE_VAR:
		case NUMBER:
			opstack.push((Number *)poliz[i]);
			break;
		case OPER:
		if(((Oper *)poliz[i])->getType() == IF || ((Oper *)poliz[i])->getType() == WHILE) {
			int rvalue = opstack.top()->getValue();
			opstack.pop();
			if(!rvalue) {
				return ((Goto *)poliz[i])->getRow();
			}
		}
			if (((Oper *)poliz[i])->getType() == ELSE || ((Oper *)poliz[i])->getType() == ENDWHILE) {
				return ((Goto *)poliz[i])->getRow();
			}
			if(((Oper *)poliz[i])->getType() == GOTO) {
				Lexem *label = opstack.top();
				opstack.pop();
				return labelsTable[((Variable *)label) -> getName()];
			}
			r = opstack.top();
			opstack.pop();
			l = opstack.top();
			opstack.pop();
			if(((Oper *)poliz[i])->getType() == ASSIGN) {
				val = assignOper(l, r);
			} else {
				val = ((Oper *)poliz[i])->getValue((l)->getValue(), (r)->getValue());
			}
			ptr = new Number(val);
			opstack.push((Number*)ptr);
			recycle.push_back(ptr);
			break;
		}
	}
	if (opstack.top()) {
		value = opstack.top()->getValue();
		opstack.pop();
	}
	opstack.pop();
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