#pragma once
#ifndef _SUDOKUTYPES_H
#define _SUDOKUTYPES_H

 #include <array>

using namespace std;

struct ROWCOL {
	uint8_t row;
	uint8_t col;
};

struct SQUARE {
	array<char,3> name[3];
	char value;
    array<char, 10> allowableValues;
    array< array < ROWCOL, 3> ,9> units;
    array<ROWCOL,20> peers;
};

typedef array<array<SQUARE ,9> ,9> sudokuType; // 8748 bytes

#endif // _SUDOKUTYPES_H