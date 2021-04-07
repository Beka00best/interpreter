#ifndef LEXEM
#define LEXEM
#include <bits/stdc++.h>
#include <const.h>

extern std::map<std::string, int> labelsTable;

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
	Oper(OPERATOR opertype);
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
	std::string getName();
	void setValue(int value_);
	void print();
};

class Goto : public Oper {
	int row;
public:
	Goto(OPERATOR opertype);
	void setRow(int);
	int getRow();
	void print();
};



extern std::vector<Lexem *> recycle;
extern Lexem *ptr;
void print_vector(std::vector<Lexem *> infix);
void clear_vector(std::vector<Lexem *> v);



#endif