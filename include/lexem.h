#ifndef LEXEM
#define LEXEM
#include <bits/stdc++.h>
#include <const.h>

extern std::map<std::string, int> varTable;
extern std::map<std::string, int> labelsTable;
extern std::map<std::string, int *> arrayTable;
extern std::map<std::string, int> arraySizeTable;
extern std::map<std::string, int> functionsTable;
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

class Oper : public Lexem {
	OPERATOR opertype;
public:
	Oper();
	Oper(OPERATOR opertype);
	Oper(std::string);
	int getType();
	int getPriority();
	int getValue(Lexem *, Lexem *);
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

class Array : public Lexem {
	std::string arrayName;
	int index;
	std::vector<int>data;
public:
	Array();
	Array(std::string);
	void setSize(int);
	std::string getName();
	void setIndex(int);
	int getValue() const;
	void setValue(int);
	void print();
};

class Function : public Lexem {
	std::string functionName;
	int jumpRow;
	int numberArgument;
public:
	Function();
	Function(std::string);
	void setRow(int);
	void setNumberArg(int);
	int getRow();
	int getNumberArg();
	void print();
};

struct Space {
	std::map<std::string, int> varTable;
	std::map<std::string, int *> arrayTable;
	std::map<std::string, int> arraySizeTable;
};



extern std::stack<int> Global_suka_stack;
extern std::vector<Lexem *> recycle;
extern Lexem *ptr;
void print_vector(std::vector<Lexem *> infix);
void print_vector_vector(std::vector<std::vector<Lexem *>> infix);
void clear_vector(std::vector<Lexem *> v);
void clear_lines(std::vector<std::vector<Lexem *>> infix);
void printMap();
void print_arrs();
int findMain(std::vector<std::vector<Lexem *>> postfix);




#endif