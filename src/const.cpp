#include <const.h>
#include <bits/stdc++.h>

int PRIORITY[] = {
	-1, -1,
	-1,
	-2, -1,
	-1,
	-3,
	-1, -1,
	-1, -1,
	-1, -1,
	-1, -1,
	-1, -1,
	1,
	2,
	3,
	4,
	5,
	6, 6,
	-3,
	8, 8,
	7, 7,
	7, 7,
	9, 9,
	10, 10, 10,
	-2, -1
};

std::string SYMBOLS[] = {
	"function", "endfunction",
	"return",
	"[", "]",
	"size",
	"print",
	"if", "then",
	"else", "endif",
	"while", "endwhile",
	"goto", ":",
	"(", ")", 
	"or",
	"and",
	"|",
	"^",
	"&",
	"==", "!=",
	"=",
	"<<", ">>",
	"<=", "<",
	">=", ">",
	"+", "-", 
	"*", "/", "%",
	"LVALUE", "RVALUE"
};

int OP_NUM = sizeof(SYMBOLS) / sizeof(std::string);