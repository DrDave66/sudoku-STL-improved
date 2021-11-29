#pragma once
#ifndef _GUESS
#define _GUESS

#include <string>
#include <cstring>
using namespace std;
#include "RowCol.h"

class Sudoku;

class Guess
{
public:
	Guess(string _puzzleString, RowCol _square, string _guess);
	Guess(Sudoku* s, string _square, string _guess);
    Guess();
	Guess(const Guess&);
	Guess& operator=(const Guess& cpy) ;
	string toString();


	string puzzleString;
	RowCol square;
	string guess;
};

#endif // _GUESS

