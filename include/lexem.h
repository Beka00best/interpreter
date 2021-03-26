#ifndef LEXEM
#define LEXEM
#include <bits/stdc++.h>
#include <const.h>

class Lexem {
protected:
	TYPE_INFO type;
public:
	Lexem();
	Lexem(TYPE_INFO t);
	virtual void print() {}
	int virtual getValue() const{}
	TYPE_INFO getLexType();
	virtual ~Lexem();
};

class Number : public Lexem {
	int value;
public:
	Number(int);
	int getValue() const;
	void print();
};

class Oper : public Lexem {
	OPERATOR opertype;
public:
	Oper();
	Oper(std::string);
	OPERATOR getType();
	int getPriority();
	int getValue(const Number &left, const Number &right);
	void print();
};

class Variable : public Lexem {
	std::string name;
public:
	Variable(std::string str);
	int getValue() const;
	void setValue(int value_);
	void print();
};

extern std::vector<Lexem *> recycle;
extern Lexem *ptr;
void print_vector(std::vector<Lexem *> infix);
void clear_vector(std::vector<Lexem *> v);



#endif