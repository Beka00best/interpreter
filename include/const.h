#ifndef CONST
#define CONST
#include <bits/stdc++.h>

enum TYPE_INFO {
	NUMBER,
	OPER,
	TYPE_VAR
};

enum OPERATOR {
	PRINT,
	IF, THEN,
	ELSE, ENDIF,
	WHILE, ENDWHILE,
	GOTO, COLON,
	LBRACKET, RBRACKET,
	ASSIGN,
	OR,
	AND,
	BITOR,
	XOR,
	BITAND,
	EQ, NEQ,
	SHL, SHR,
	LEQ, LT,
	GEQ, GT,
	PLUS, MINUS,
	MULTIPLY, DIV, MOD
};


extern int PRIORITY[]; 
extern std::string SYMBOLS[];
extern int OP_NUM;

#endif