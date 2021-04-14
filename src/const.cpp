#include <const.h>
#include <bits/stdc++.h>

int PRIORITY[] = {
	-1,
	-1, -1,
	-1, -1,
	-1, -1,
	-1, -1,
	-1, -1,
	0,
	1,
	2,
	3,
	4,
	5,
	6, 6,
	8, 8,
	7, 7,
	7, 7,
	9, 9,
	10, 10, 10
};

std::string SYMBOLS[] = {
	"print",
	"if", "then",
	"else", "endif",
	"while", "endwhile",
	"goto", ":",
	"(", ")", 
	"=",
	"or",
	"and",
	"|",
	"^",
	"&",
	"==", "!=",
	"<<", ">>",
	"<=", "<",
	">=", ">",
	"+", "-", 
	"*", "/", "%"
};

int OP_NUM = sizeof(SYMBOLS) / sizeof(std::string);