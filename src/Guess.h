#pragma once
#ifndef _GUESS
#define _GUESS

#include <string>
#include <cstring>
using namespace std;
#include "RowCol.h"
#include "SudokuTypes.h"

class Sudoku;

class Guess
{
public:
	Guess(RowCol _square, string _guess, SUDOKUTYPE _puzzle, SUDOKUTYPE _allowableValues);

    Guess();
	Guess(const Guess&);
	Guess& operator=(const Guess& cpy) ;
	string toString();


    SUDOKUTYPE puzzle;
    SUDOKUTYPE allowableValues;
	RowCol square;
	string guess;
};

#endif // _GUESS

