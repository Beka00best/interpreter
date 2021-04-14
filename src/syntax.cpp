#include <syntax.h>
#include <bits/stdc++.h>
#include <const.h>
#include <lexem.h>

void initJumps(std::vector< std::vector<Lexem *>> infix) {
	std::stack<Goto *> stackIfElse, stackWhile;
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
					case ENDWHILE:
						if (stackIfElse.empty()) {
							perror("empty stackwhile wrong syntax: endwhile");
							exit(1);
						}
						((Goto *)infix[row][i]) -> setRow(stackWhile.top() -> getRow());
						stackWhile.top() -> setRow(row + 1);
						stackWhile.pop();
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
				i++;
			}
		}
	}
	// add repeated method handler
}

std::vector<Lexem *> buildPoliz(std::vector<Lexem *> infix) {
	std::vector<Lexem *> postfix;
	std::stack<Oper *> opstack;
	int current;
	for (int i = 0; i < infix.size(); i++) {
		if (infix[i] == nullptr) {
			continue;
		}
		switch (infix[i]->getLexType()) {
		case TYPE_VAR:
			if (infix[i]->inLabTable() == true) {
				joinGotoAndLabel(infix[i], postfix);
				break;
			}
		case NUMBER:
			postfix.push_back(infix[i]);
			break;
		case OPER:
			if(!opstack.empty()) {
				current = infix[i]->getType();
				switch (current) {
				case ENDIF:
				case ENDWHILE:
					postfix.push_back(infix[i]);
					break;
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
					if(opstack.top()->getType() == ASSIGN && infix[i]->getType() == ASSIGN) {
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
