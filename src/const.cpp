#include <const.h>
#include <bits/stdc++.h>

int PRIORITY[] = {
	-5, -5,
	-4, -4,
	-3, -3,
	-2, -2,
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