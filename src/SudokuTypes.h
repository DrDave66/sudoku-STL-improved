#pragma once
#ifndef _SUDOKUTYPES_H
#define _SUDOKUTYPES_H

#include <array>
#include <tuple>

using namespace std;

typedef tuple<uint32_t, uint32_t> ROWCOL;

//struct SQUARE {
//	string name = "AB";
//	char value;
//    array<char,10> allowableValues;
//    array< array < ROWCOL, 3> ,9> units;
//    array<ROWCOL,20> peers;
//};
//
//typedef array<array<SQUARE ,9> ,9> sudokuType; // 8748 bytes

#endif // _SUDOKUTYPES_H