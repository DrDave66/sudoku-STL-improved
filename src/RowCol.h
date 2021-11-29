//
//  RowCol.hpp
//  sudoku-STL
//
//  Created by Dave Landis on 11/28/21.
//  Copyright © 2021 Dave Landis. All rights reserved.
//
#pragma once
#ifndef RowCol_hpp
#define RowCol_hpp
#include <cstdint>
#include <string>
#include <iostream>

using namespace std;

class RowCol {
public:
    RowCol() {};
    RowCol(int16_t r, int16_t );
    RowCol(const RowCol&);

    RowCol& operator=(const RowCol cpy);

    inline uint16_t r() { return row; };
    inline uint16_t c() { return col; };
    void set(int16_t r, int16_t c);
    string toString();
    friend ostream& operator<< (ostream& stream, const RowCol&);
//    inline bool operator == (const RowCol& rhs) { return (rhs.row == row && rhs.col == col);}
//    inline bool operator != (const RowCol& rhs) { return (rhs.row != row && rhs.col != col);}

    int16_t row;
    int16_t col;
};
inline bool operator == (const RowCol& lhs, const RowCol& rhs) { return (lhs.row == rhs.row && lhs.col == rhs.col);}
inline bool operator != (const RowCol& lhs, const RowCol& rhs) { return !(lhs == rhs);}
inline bool operator < (const RowCol& lhs,const RowCol& rhs) {if (lhs.row == rhs.row) return lhs.col < rhs.col; else return lhs.row < rhs.row;}
inline bool operator > (const RowCol& lhs,const RowCol& rhs) { return rhs < lhs;}
inline bool operator <= (const RowCol& lhs,const RowCol& rhs) { return !(lhs > rhs);}
inline bool operator >= (const RowCol& lhs,const RowCol& rhs) { return !(lhs < rhs);}
#endif /* RowCol_hpp */
