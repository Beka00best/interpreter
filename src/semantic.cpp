#include <semantic.h>
#include <bits/stdc++.h>
#include <lexem.h>
#include <const.h>

int evaluatePoliz(std::vector<std::vector<Lexem *>> postfix, int row, int *mainval) {
	std::vector<Lexem *> poliz = postfix[row];
	int value = 0;
	int val;
	int Row;
	int nextVal;
	Lexem *l, *r;
	int i = 0;
	if (returnFlag) {
		i = StackReturnAddress.top().Index;
		StackReturnAddress.pop();
	}
	for (; i < poliz.size(); ++i) {
		if (poliz[i] == nullptr) {
			continue;
		}
		switch (poliz[i]->getLexType()) {
		case FUNC:
			RetAddress Retadd;
			returnFlag = false;
			Retadd.Index = i + 1;
			returnFunctionStack.push(poliz[i]);
			Retadd.row = row;
			StackReturnAddress.push(Retadd);
			for (int j = 0; j < functionsArgNumberTable[poliz[i] ->getName()]; j++) {
				Number *tmp = new Number((globalSpace.top().opstack.top())->getValue());
				prevVariables.push(tmp);
				recycle.push_back(tmp);
				globalSpace.top().opstack.pop();
			}
			return ((Function *)poliz[i])->getRow();
		case ARRTYPE:
		case TYPE_VAR:
		case NUMBER:
			globalSpace.top().opstack.push(poliz[i]);
			break;
		case OPER:
			if (poliz[i]->getType() == FUNCTION) {
				Space spaceLocal;
				// std::cout << "FUNCTION" << std::endl;
				while (!prevVariables.empty()) {
					i--;
					spaceLocal.varTable[globalSpace.top().opstack.top() -> getName()] = prevVariables.top()->getValue();
					globalSpace.top().opstack.pop();
					prevVariables.pop();
				}
				globalSpace.push(spaceLocal);
				return row + 1;
			}
			if (poliz[i]->getType() == RETURN) {
				returnFlag = true;
				Number *tmp = new Number((globalSpace.top().opstack.top())->getValue());
				recycle.push_back(tmp);
				globalSpace.pop();
				globalSpace.top().opstack.push(tmp);
				int ret = StackReturnAddress.top().row;
				returnFunctionStack.pop();
				return ret;
			}
			if (poliz[i]->getType() == PRINT) {
				std::cout << "PRINT: " << globalSpace.top().opstack.top() -> getValue() << std::endl;
				break;
			}
			if (poliz[i]->getType() == GOTO ||
				poliz[i]->getType() == ELSE ||
				poliz[i]->getType() == ENDWHILE) {
				Goto *lexemgoto = (Goto *)poliz[i];
				return lexemgoto->getRow();
			} else if (poliz[i]->getType() == IF || poliz[i]->getType() == WHILE) {
				Goto *lexemgoto = (Goto *)poliz[i];
				Lexem *rvalue = globalSpace.top().opstack.top();
				globalSpace.top().opstack.pop();
				if (!(rvalue->getValue())) {
					return lexemgoto->getRow();
				}
				break;
			}
			r = globalSpace.top().opstack.top();
			globalSpace.top().opstack.pop();
			l = globalSpace.top().opstack.top();
			globalSpace.top().opstack.pop();
			if (poliz[i]->getType() == LVALUE) {
				Lexem *arrayElem = new Array(globalSpace.top().opstack.top()->getName());
				globalSpace.top().opstack.pop();
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
			globalSpace.top().opstack.push(ptr);
			recycle.push_back(ptr);
			break;
		}
	}
	returnFlag = false;
	if (!globalSpace.top().opstack.empty()) {
		value = globalSpace.top().opstack.top()->getValue();
		globalSpace.top().opstack.pop();
	}
	if (value) {
		(*mainval) = value;
		// std::cout << value << std::endl; 
	}
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