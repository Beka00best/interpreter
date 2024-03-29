#ifndef CONST
#define CONST
#include <bits/stdc++.h>

enum TYPE_INFO {
	NUMBER,
	OPER,
	TYPE_VAR,
	ARRTYPE,
	FUNC
};

enum OPERATOR {
	FUNCTION, ENDFUNCTION,
	RETURN,
	LSQUBR, RSQUBR,
	SIZE,
	PRINT,
	IF, THEN,
	ELSE, ENDIF,
	WHILE, ENDWHILE,
	GOTO, COLON,
	LBRACKET, RBRACKET,
	OR,
	AND,
	BITOR,
	XOR,
	BITAND,
	EQ, NEQ,
	ASSIGN,
	SHL, SHR,
	LEQ, LT,
	GEQ, GT,
	PLUS, MINUS,
	MULTIPLY, DIV, MOD,
	LVALUE, RVALUE
};


extern int PRIORITY[]; 
extern std::string SYMBOLS[];
extern int OP_NUM;
extern int Index;
extern bool returnFlag;

#endif