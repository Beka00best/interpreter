#ifndef LEXEM
#define LEXEM
#include <bits/stdc++.h>
#include <const.h>

extern std::map<std::string, int> labelsTable;

class Lexem {
public:
	TYPE_INFO type;
	Lexem();
	Lexem(TYPE_INFO t);
	virtual void print() {}
	virtual int getValue() const{}
	virtual int getType() {}
	virtual bool inLabelTable() {}
	virtual std::string getName() {}
	TYPE_INFO getLexType();
	virtual ~Lexem();
};

class Number : public Lexem {
	int value;
public:
	Number(int);
	int getType();
	int getValue() const;
	void print();
};

class Oper :  public Lexem {
	OPERATOR opertype;
public:
	Oper();
	Oper(OPERATOR opertype);
	Oper(std::string);
	int getType();
	int getPriority();
	int getValue(const Number &left, const Number &right);
	void print();
};

class Variable : public Lexem {
	std::string name;
public:
	Variable(std::string str);
	int getType();
	int getValue() const;
	bool inLabelTable();
	std::string getName();
	void setValue(int value_);
	void print();
};

class Goto : public Oper {
	int row;
	OPERATOR oper;
public:
	Goto();
	Goto(OPERATOR opertype);
	void setRow(int);
	void setRow(const std::string name);
	int getType();
	int getRow();
	void print();
};



extern std::vector<Lexem *> recycle;
extern Lexem *ptr;
void print_vector(std::vector<Lexem *> infix);
void print_vector_vector(std::vector<std::vector<Lexem *>> infix);
void clear_vector(std::vector<Lexem *> v);
void clear_lines(std::vector<std::vector<Lexem *>> infix);
void printMap();



#endif