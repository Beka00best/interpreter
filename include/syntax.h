#ifndef SYNTAX
#define SYNTAX
#include <lexem.h>
#include <bits/stdc++.h>

void initLabels(std::vector<Lexem *> &infix, int row);
std::vector<Lexem *> buildPoliz(std::vector<Lexem *> infix);
void initJumps(std::vector< std::vector<Lexem *>> infix);
void joinGotoAndLabel(Lexem *lexemvar, std::vector<Lexem *> &postfix);

#endif