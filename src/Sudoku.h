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
#include "sudokuTypes.h"

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
	vector<ROWCOL> crossProductRC (string a, string b);
    vector<ROWCOL> crossProductRC(vector<int16_t>, vector<int16_t>);
    
	bool setPuzzle(string p);
	//bool setValue(string square, string value);
    bool setValue(int16_t row, int16_t col, string value);
    bool setValue(ROWCOL rc, string value);
    
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
	bool removeGuess(string, string);
	bool guessesRemain(void);
	Guess getGuess();
	bool popGuess();
	void pushGuess(Guess const*);
	bool solvePuzzle();
	bool startGuessing();
	void printGuessList();
	void test();
//private:
    static string RCToString(ROWCOL);
    static ROWCOL stringToRC(string);
    
    static const uint32_t numRows = 9;
    static const uint32_t numCols = 9;
    vector<int16_t> rows = {0,1,2,3,4,5,6,7,8};
    vector<int16_t> cols = {0,1,2,3,4,5,6,7,8};
    
	string digitsText = "123456789";
//	string rowsText = "012345678";
//	string colsText = "012345678";
    

    array<array<ROWCOL, numRows> , numCols> rcSquares;

    array<array<ROWCOL, 9>, 27> rcUnitList;
    

    array<array<array<array<ROWCOL, 9> ,3 > ,9> ,9> rcUnits;
    
    array<array<array<ROWCOL, 20> ,9> ,9> rcPeers;
    set<string> digitSet = { "1","2","3","4","5","6","7","8","9" };
    
    array<array<string, 9> ,9> puzzle;
    array<array<string, 9> ,9> allowableValues;
	array<Guess, 81> guessList; // ordered list of guesses
    uint8_t guessNumber;
    
	Guess newGuess;
};

#endif // _SUDOKU
