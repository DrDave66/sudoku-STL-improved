#pragma once
#ifndef _SUDOKU
#define _SUDOKU
#include <array>
#include <typeinfo>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

#include "Guess.h"
#include "PrecisionTimeLapse.h"
#include "SudokuTypes.h"
#include "RowCol.h"

#define RC_r(x) (get<0>(x))
#define RC_c(x) (get<1>(x))

class Sudoku
{
public:
    Sudoku();
	Sudoku(string puzzle);
	void clearPuzzle();
	void createVectors(void);
	vector<string> crossProduct(string a, string b);
	vector<RowCol> crossProductRC (string a, string b);
    vector<RowCol> crossProductRC(vector<int16_t>, vector<int16_t>);
    
	bool setPuzzle(string p);
	//bool setValue(string square, string value);
    bool setValue(int16_t row, int16_t col, string value);
    bool setValue(RowCol rc, string value);
    
	void printPuzzle(void);
	void printPuzzle(string title);
	void printAllowableValues(void);
	void printAllowableValues(string title);
	bool solveOnes(void);
	string printableStringVector(vector<string> vec);
	string printableVectorVectorString(vector<vector<string> >);
	string printableStringSet(set<string> st);
	bool isPuzzleSolved(void); 
	string getPuzzleText(void);
	string getAllowableGuessesText(void);
	string getPackedPuzzle(void);
	void unpackPuzzle(string);
	bool removeGuess(RowCol, string);
	bool guessesRemain(void);
	Guess getGuess();
	bool popGuess();
	void pushGuess(const Guess);
	bool solvePuzzle();
	bool startGuessing();
	void printGuessList();
	void test();
//private:
    
    static const uint32_t numRows = 9;
    static const uint32_t numCols = 9;
    vector<int16_t> rows = {0,1,2,3,4,5,6,7,8};
    vector<int16_t> cols = {0,1,2,3,4,5,6,7,8};
    
	string digitsText = "123456789";
//	string rowsText = "012345678";
//	string colsText = "012345678";
    void printPeers(RowCol rc);

    //array<array<RowCol, numRows> , numCols> rcSquares;
    array<array<RowCol, 9> ,27> rcUnitList;
    array<array<array<array<RowCol, 9> ,3 > ,9> ,9> rcUnits;
    array<array<array<RowCol, 20> ,9> ,9> rcPeers;

    set<string> digitSet = { "1","2","3","4","5","6","7","8","9" };
    SUDOKUTYPE puzzle;
    SUDOKUTYPE allowableValues;
	array<Guess, 81> guessList; // ordered list of guesses
    uint16_t guessNumber;
    Guess newGuess;
};

#endif // _SUDOKU
