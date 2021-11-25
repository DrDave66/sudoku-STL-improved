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

	bool setPuzzle(string p);
	bool setValue(string square, string value);
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
    array<uint32_t, 9> rows = {0,1,2,3,4,5,6,7,8};
    array<uint32_t, 9> cols = {0,1,2,3,4,5,6,7,8};
    
	string digitsText = "123456789";
	string rowsText = "ABCDEFGHI";
	string colsText = "123456789";
    
    array<array<string, numRows> ,numCols> squares;
    array<array<string, 9>, 27> unitlist;
    
    array<array<array<array<string, 9> ,3 > ,9> ,9> newUnits;
	
    map<string, vector<vector<string> > > units; // square, squares in unit
	
    map<string, vector<string> > peers; // square, squares in peers
    set<string> digitSet = { "1","2","3","4","5","6","7","8","9" };
    
   	map<string, string> puzzle; // unit, value
	map<string, string> allowableValues; // square, string of allowable values
	vector<Guess> guessList; // ordered list of guesses
	Guess newGuess;
};

#endif // _SUDOKU
