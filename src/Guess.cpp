#include "Guess.h"

Guess::Guess(RowCol _square, string _guess,SUDOKUTYPE _puzzle, SUDOKUTYPE _allowableValues) {
    puzzle = _puzzle;
    allowableValues = _allowableValues;
    square = _square;
	guess = _guess;
}

Guess::Guess() {
    for(int16_t r = 0 ; r < 9 ; r++) {
        for(int16_t c = 0 ; c < 9 ; c++) {
            puzzle[r][c] = "";
            allowableValues[r][c] = "";
        }
        
    }
	square = RowCol();
	guess = "";
}
Guess::Guess(const Guess& g) {
    puzzle = g.puzzle;
    allowableValues = g.allowableValues;
	square = g.square;
	guess = g.guess;
}

Guess& Guess::operator=(const Guess& cpy) {
    puzzle = cpy.puzzle;
    allowableValues = cpy.allowableValues;
	square = cpy.square;
	guess = cpy.guess;
	return *this;
}

string Guess::toString() {
	//char ss[1000];
    cout <<" Square: " << square << " Guess: " << guess << endl;
//    sprintf(ss,"Square: %s, Guess: %s, Puzzle Text: %s\n",square.toString().c_str(), guess.c_str(), puzzleString.c_str());
	string retval;
	return retval;
}