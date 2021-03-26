#ifndef LEXICAL
#define LEXICAL
#include <lexem.h>
#include <bits/stdc++.h>

std::string to_str(char ch);
void do_digit(std::vector<Lexem *> &infix, std::string codeline, int &i);
bool is_oper(std::string oper);
bool is_symbol(char ch);
void do_name(std::vector<Lexem *> &infix, std::string codeline, int &i);
void do_oper(std::vector<Lexem *> &infix, std::string codeline, int &i);

std::vector<Lexem *> parseLexem(std::string codeline);



#endif
