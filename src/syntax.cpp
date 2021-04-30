#include <syntax.h>
#include <bits/stdc++.h>
#include <const.h>
#include <lexem.h>

void initJumps(std::vector< std::vector<Lexem *>> infix) {
	std::stack<Goto *> stackIfElse, stackWhile;
	std::stack<int> stackFunction;
	int current;
	for (int row = 0; row < infix.size(); row++) {
		for (int i = 0; i < infix[row].size(); i++) {
			if (infix[row][i] == nullptr) {
				continue;
			}
			if (infix[row][i] -> getLexType() == OPER) {
				current = infix[row][i] -> getType();
				switch (current) {
					case IF:
						stackIfElse.push((Goto *)infix[row][i]);
						break;
					case ELSE:
						if (stackIfElse.empty()) {
							perror("empty stackIfelse wrong syntax: else");
							exit(1);
						}
						stackIfElse.top() -> setRow(row + 1);
						stackIfElse.pop();
						stackIfElse.push((Goto *)infix[row][i]);
						break;
					case ENDIF:
						if (stackIfElse.empty()) {
							perror("empty stackIfelse wrong syntax: endif");
							exit(1);
						}
						stackIfElse.top() -> setRow(row + 1);
						stackIfElse.pop();
						break;
					case WHILE:
						((Goto *)infix[row][i]) -> setRow(row);
						stackWhile.push((Goto *)infix[row][i]);
						break;
					case ENDWHILE:
						if (stackWhile.empty()) {
							perror("empty stackwhile wrong syntax: endwhile");
							exit(1);
						}
						((Goto *)infix[row][i]) -> setRow(stackWhile.top() -> getRow());
						stackWhile.top() -> setRow(row + 1);
						stackWhile.pop();
						break;
				}
			}
		}
	}
}

void joinGotoAndLabel(Lexem *lexemvar, std::vector<Lexem *> &postfix) {
	if (postfix.back()->getType() == GOTO) {
		Goto *lexemgoto = (Goto *)postfix.back();
		lexemgoto->setRow(lexemvar->getName());
	}
}

void initLabels(std::vector<Lexem *> &infix, int row) {
	for (int i = 1; i < (int)infix.size(); i++) {
		if (infix[i - 1] -> getLexType() == TYPE_VAR && infix[i] -> getLexType() == OPER) {
			if (infix[i] -> getType() == COLON) {
				labelsTable[infix[i - 1]->getName()] = row;
				delete infix[i - 1];
				delete infix[i];
				infix[i - 1] = nullptr;
				infix[i] = nullptr;
				return;
			}
		}
		if (infix[i - 1] -> getLexType() == OPER && infix[i - 1] -> getType() == FUNCTION) {
			if (!functionsTable.count(infix[i]->getName())) {
				functionsTable[infix[i]->getName()] = row;
				((Function *)infix[i])->setNumberArg(infix.size() - i - 3);
				delete infix[i];
				delete infix[i + 1];
				delete infix[infix.size() - 1];
				infix[infix.size() - 1] = nullptr;
				infix[i + 1] = nullptr;
				infix[i] = nullptr;
				return;
			}
		}
		if (infix.size() != 0) {
			if (functionsTable.count(infix[i - 1]->getName())) {
				Function *func = new Function(infix[i - 1]->getName());
				func->setRow(functionsTable[infix[i - 1]->getName()]);
				delete infix[i - 1];
				infix[i - 1] = func;
				recycle.push_back(func);
				i++;
			}
		}
	}
}

std::vector<Lexem *> buildPoliz(std::vector<Lexem *> infix) {
	std::vector<Lexem *> postfix;
	std::stack<Lexem *> opstack;
	int current;
	int LvalueFlag = 0;
	Oper *tmp;
	for (int i = 0; i < infix.size(); i++) {
		if (infix[i] == nullptr) {
			continue;
		}
		switch (infix[i]->getLexType()) {
		case FUNC:
			opstack.push(infix[i]);
			break;
		case TYPE_VAR:
			if (infix[i]->inLabelTable()) {
				joinGotoAndLabel(infix[i], postfix);
				break;
			}
		case ARRTYPE:
		case NUMBER:
			postfix.push_back(infix[i]);
			break;
		case OPER:
			current = infix[i]->getType();
			switch (current) {
			case THEN:
			case ENDIF:
				break;
			case GOTO:
				while (!opstack.empty()) {
					postfix.push_back(opstack.top());
					opstack.pop();
				}
				postfix.push_back(infix[i]);
				break;
			case LVALUE:
				LvalueFlag = 1;
				tmp = (Oper *)infix[i];
			case RVALUE:
			case LBRACKET:
				opstack.push(infix[i]);
				break;
			case RSQUBR:
			case RBRACKET:
				while (opstack.top()->getType() != LBRACKET and 
				opstack.top()->getType() != LVALUE and 
				opstack.top()->getType() != RVALUE) {
					postfix.push_back(opstack.top());
					opstack.pop();
				}
				if(opstack.top()->getType() == RVALUE) {
					postfix.push_back(opstack.top());
				}
				opstack.pop();
				break;
			default:
				while (!opstack.empty() && (((Oper *)opstack.top())->getPriority()) >= ((Oper *)infix[i])->getPriority()) {
					postfix.push_back(opstack.top());
					opstack.pop();
				}
				opstack.push(infix[i]);
				break;
			}
		}
	}
	Oper *ptr = new Oper(SYMBOLS[RVALUE]);
	recycle.push_back(ptr);
	if (opstack.empty() and LvalueFlag) {
		postfix.push_back(ptr);
	}
	while (!opstack.empty()) {
		if (opstack.top()->getType() == ASSIGN && LvalueFlag) {
			opstack.pop();
			postfix.push_back(tmp);
			break;
		} 
		if (LvalueFlag) {
			postfix.push_back(ptr);
			postfix.push_back(opstack.top());
		} else {
			postfix.push_back(opstack.top());
		}
		opstack.pop();
	}
	LvalueFlag = 0;
	return postfix;
}
