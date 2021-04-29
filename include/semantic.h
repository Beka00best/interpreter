#ifndef SEMANTIC
#define SEMANTIC
#include <bits/stdc++.h>
#include <lexem.h>

int assignOper(Lexem *l, Lexem *r);
int evaluatePoliz(std::vector<std::vector<Lexem *>> postfix, int row, int *mainval);
#endif