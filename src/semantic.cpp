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
		std::cout << "Index " << i << std::endl;
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
				// prevVariables.push(globalSpace.top().opstack.top());
				// Number *tmp = new Number(*mainval);
				Number *tmp = new Number((globalSpace.top().opstack.top())->getValue());
				// tmp->print();
				prevVariables.push(tmp);
				recycle.push_back(tmp);
				// std::cout << "Value: " << *mainval << std::endl; 
				globalSpace.top().opstack.pop();
			}
			std::cout << "ROW " << ((Function *)poliz[i])->getRow() << std::endl;
			return ((Function *)poliz[i])->getRow();
		case ARRTYPE:
		case TYPE_VAR:
		case NUMBER:
			// std::cout << "OK Lex" << std::endl;
			globalSpace.top().opstack.push(poliz[i]);
			break;
		case OPER:
			if (poliz[i]->getType() == FUNCTION) {
				Space spaceLocal;
				std::cout << "FUNCTION" << std::endl;
				while (!prevVariables.empty()) {
					i--;
					if (globalSpace.top().opstack.empty()) {
						// std::cout << "OK" << std::endl;
					}
					// if (prevVariables.top()->getLexType() == TYPE_VAR) {

						// spaceLocal.varTable[globalSpace.top().opstack.top() -> getName()] = globalSpace.top().varTable[prevVariables.top()->getName()];
						spaceLocal.varTable[globalSpace.top().opstack.top() -> getName()] = prevVariables.top()->getValue();
						
						// std::cout << "OK " << i << std::endl;
						globalSpace.top().opstack.pop();
					// }
					prevVariables.pop();
				}
				// varTable.clear();
				// varTable = spaceLocal.varTable;
				globalSpace.push(spaceLocal);
				// std::cout << "OK" << std::endl;
				return row + 1;
			}
			if (poliz[i]->getType() == RETURN) {
				if (globalSpace.top().opstack.empty()) {
					// std::cout << "OK" << std::endl;
				}
				returnFlag = true;
				// (globalSpace.top().opstack.top())->print();
				// std::cout << returnFlag << std::endl;
				// std::cout << "OK" << std::endl;
				Number *tmp = new Number((globalSpace.top().opstack.top())->getValue());
				recycle.push_back(tmp);
				// Number *tmp1 = new Number(tmp->getValue());
				// Lexem *tmp = poliz[i - 1];
				tmp->print();
				// std::cout << "OK" << std::endl;
				// globalSpace.top().opstack.pop();
				globalSpace.pop();
				// std::cout << "OK" << std::endl;
				if (globalSpace.empty()) {
					std::cout << "NOT" << std::endl;
				}
				globalSpace.top().opstack.push(tmp);
				// int ret = returnRow[returnFunctionStack.top()->getName()];
				int ret = StackReturnAddress.top().row;
				// StackReturnAddress.pop();
				std::cout << "RET " << ret << std::endl;
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
			// std::cout << "AGGA" << std::endl;
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
	// Index = 0;
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