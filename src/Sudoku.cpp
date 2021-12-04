#include "Sudoku.h"
#define NOTIMING

Sudoku::Sudoku() {
	createVectors();
	clearPuzzle();
    allValues.resize(81*10);
	srand((uint32_t)time(NULL));
}

Sudoku::Sudoku(string puzzle) {
	createVectors();
	setPuzzle(puzzle);
    allValues.resize(81*10);
	srand((uint32_t)time(NULL));
}

vector<RowCol> Sudoku::crossProductRC(vector<uint8_t> a, vector<uint8_t> b) {
#define noPRINTCROSS
    static vector<RowCol> v;
    v.clear();
    RowCol rc;
    for(uint8_t aa : a) {
        for (uint8_t bb : b) {
            rc.set(aa,bb);
            v.push_back(rc);
        }
    }
    return v;
}

void Sudoku::createVectors(void) {
//	// create vector of squares
#define noPRINTVECTORS
    
	uint8_t i;
    vector<RowCol> rcv;

    for (auto r:rows) {
        for (auto c:cols) {
            puzzle[r][c] = ".";
            allowableValues[r][c] = "123456789";
        }
    }
    // create unitlist array
	vector<RowCol> temp;
	uint8_t ul = 0;
    array<RowCol,9> ts;
    vector<uint8_t> v1;
    ul = 0;
  	// for each col across the rows
	for (auto c : cols) {
        v1.clear();
        v1.push_back(c);
		temp = crossProductRC(rows, v1);
        i = 0;
        for (RowCol s : temp) {
            rcUnitList[ul][i] = s;
            i++;
        }
        ul++;
	}
// for each row across the cols
	for (auto r : rows) {
        v1.clear();
        v1.push_back(r);
		temp = crossProductRC(v1, rows);
        i = 0;
        for (RowCol s : temp) {
            rcUnitList[ul][i] = s;
            i++;
        }
        ul++;
    }
    // for each 9x9 square
	vector<vector<uint8_t> > sr;
    vector<vector<uint8_t> > sc;
    sr.push_back(vector<uint8_t> {0,1,2});
	sr.push_back(vector<uint8_t> {3,4,5});
	sr.push_back(vector<uint8_t> {6,7,8});
	sc.push_back(vector<uint8_t> {0,1,2});
	sc.push_back(vector<uint8_t> {3,4,5});
	sc.push_back(vector<uint8_t> {6,7,8});
	for (vector<uint8_t> r : sr) {
		for (vector<uint8_t> c : sc) {
            i = 0;
            temp = crossProductRC(r,c);
            for (RowCol s : temp) {
                rcUnitList[ul][i] = s;
                i++;
            }
            ul++;
        }

	}

//    // unit dictionary
    RowCol sq;
	uint8_t unum = 0;
    for(auto r : rows) {
        for (auto c : cols) {
            unum = 0;
            sq.set(r,c);
            for (array<RowCol,9> ul : rcUnitList){
                for(i = 0 ; i < 9 ; i++) {
                    if (ul[i] == sq) {
                        rcUnits[r][c][unum] = ul;
                        unum++;
                    }
                }
            }
        }
    }

    //////	// make peer dictionary
    int pnum = 0;
    set<RowCol> peerSet;
    for(auto r : rows) {
        for (auto c : cols) {
            pnum = 0;
            peerSet.clear();
            sq.set(r,c);
            for(array<RowCol,9> ul : rcUnits[r][c]) {
                for(RowCol u : ul) {
                    if (u != sq) {
                        peerSet.insert((const RowCol)u);
                    }
                }
            }
            for(RowCol ps : peerSet) {
                rcPeers[r][c][pnum] = ps;
                pnum++;
            }
        }
    }

#ifdef PRINTVECTORS
    cout << endl << "UnitList" << endl;
    for(uint8_t j = 0 ; j < 27 ; j++) {
        for (i = 0 ; i < 9 ;i++) {
            cout << rcUnitList[j][i] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
    cout << endl << endl;
    for (auto r : rows) {
        for (auto c : cols) {
            sq.set(r,c);
            cout << "New Unit Dict: " << sq << " " << endl;
            for ( int unum = 0 ; unum < 3 ; unum++) {
                for (i = 0 ; i < 9 ; i++) {
                    cout << rcUnits[r][c][unum][i] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
    }
    for (auto r:rows) {
        for(auto c:cols) {
            sq.set(r,c);
            printPeers(sq);
        }
    }
#endif
}

void Sudoku::clearPuzzle(void) {
    for(auto r:rows) {
        for(auto c:cols) {
            puzzle[r][c] = ".";
            allowableValues[r][c] = digitsText;
        }
    }
}

bool Sudoku::setPuzzle(string p) {
    if(p.size() != 81)
        return false;
    clearPuzzle();
    for(auto r:rows) {
        for(auto c:cols) {
            //RowCol rc(r,c);
            setValue(r,c,p[c+ r*9]);
        }
    }
	return true;
}

/**********************************************************
**********   Printing Functions ***************************
***********************************************************/

void Sudoku::printPuzzle(string title) {
	cout << endl << title;
	printPuzzle();
}

void Sudoku::printPuzzle(void) {
	string header = "     1   2   3    4   5   6    7   8   9";
	string top = "  =========================================";
	string row_sep = "  || --------- || --------- || --------- ||";
	string col_sep = "||";
	string num_sep = "|";
	cout << endl << header << endl;
	cout << top << endl;
	uint32_t col_num = -1;
	uint32_t row_num = -1;
	string index;
	for (auto r : rows) {
		cout << (char)('A' + r) << " " << col_sep;
		for (auto c : cols) {
			if (puzzle[r][c] == "0") {
				cout << " .";
			}
			else {
				cout << " " << puzzle[r][c];
			}
			if (col_num > 0 && (col_num - 1) % 3 == 0) {
				cout << " " << col_sep;
			}
			else {
				cout << " " << num_sep;
			}
			col_num++;
		}
		row_num++;
		cout << endl;
		if (row_num == 8) {
			cout << top << endl;
		}
		else if ((row_num + 1) % 3 == 0) {
			cout << row_sep << endl;
		}
    }
}

void Sudoku::printAllowableValues(void) {
	string header = "         1           2           3            4           5           6            7           8           9";
	string top = "  =================================================================================================================";
	string row_sep = "  || --------------------------------- || --------------------------------- || --------------------------------- ||";
	string col_sep = "||";
	string num_sep = "|";
	cout << endl << header << endl;
	cout << top << endl;
	uint32_t col_num = -1;
	uint32_t row_num = -1;
	string index;
	for (auto r : rows) {
		cout << (char)('A' + r) << " " << col_sep;
		for (auto c : cols) {
			if (puzzle[r][c] == "0") {
				cout << "  ";
			}
			else {
				cout << " " << setw(9) << allowableValues[r][c];
			}
			if (col_num > 0 && (col_num - 1) % 3 == 0) {
				cout << " " << col_sep;
			}
			else {
				cout << " " << num_sep;
			}
			col_num++;
		}
		row_num++;
		cout << endl;
		if (row_num == 8) {
			cout << top << endl;
		}
		else if ((row_num + 1) % 3 == 0) {
			cout << row_sep << endl;
		}

	}
}

void Sudoku::printAllowableValues(string title) {
	cout << endl << title;
	printAllowableValues();
}

/**********************************************************
 **********   Solving Functions ***************************
***********************************************************/

bool Sudoku::setValue(uint8_t r, uint8_t c, char value) {
#ifdef TIMING
	PrecisionTimeLapse ptl;
	ptl.start();
#endif 	
    size_t t;
	uint8_t rr,cc;
    if (value == '.' || value == '0') {
        puzzle[r][c] = value;
        return true;
    } else {
        if (allowableValues[r][c].find(value) == string::npos)
            return false;
        allowableValues[r][c] = "";
        puzzle[r][c] = value;
    }
	for (RowCol p : rcPeers[r][c]) {
        rr = p.row;
        cc = p.col;
        t = allowableValues[rr][cc].find(value);
		if (t != string::npos)
			allowableValues[rr][cc].replace(t, 1, "");
    }
#ifdef TIMING
	ptl.stop();
	cout << "setValue," << ptl.elapsedString() << endl;
#endif
	return true;
}

bool Sudoku::setValue(RowCol rc, char value) {
    return setValue(rc.row, rc.col, value);
}

bool Sudoku::solveOnes(void) {
#ifdef TIMING	
	PrecisionTimeLapse ptl;
	ptl.start();
#endif	
	bool solvedSome = true;
<<<<<<< HEAD
    string allValues;
    allValues.resize(81*10);
	while (solvedSome == true ) {
=======

	while (solvedSome == true) {
>>>>>>> 262095d (aaa)
		solvedSome = false;
		// find squares with only one available value
        for (auto r:rows){
            for (auto c:cols) {
                if (allowableValues[r][c].size() == 1) {
                    // and set the value
                    solvedSome = true;
                    setValue(r, c, allowableValues[r][c][0]);
                }
            }
        }
		// look through all units and see if any value appears only one time
        for(array<RowCol,9> ul : rcUnitList) {
            allValues.clear();
			for (RowCol rc : ul) {
                allValues += allowableValues[rc.row][rc.col];;
			}
			for (char d : digitsText) {
				// if number appears once
				if (count(allValues.begin(), allValues.end(), d) == 1) {
					// find the square with the value in it
					for (RowCol u : ul) {
						if (count(allowableValues[u.row][u.col].begin(), allowableValues[u.row][u.col].end(), d) == 1) {
							solvedSome = true;
							setValue(u, d);
                          break;
						}
					}
				}
			}
		}
	}
#ifdef TIMING
	ptl.stop();
	cout << "solveOnes,"  << ptl.elapsedString() << endl;
#endif
	return solvedSome;
}

bool Sudoku::isPuzzleSolved(void) {
//	// a puzzle is solved if each unit in unitlist contains values of 1-9
	char str[10];
	str[9] = '\0';
	uint8_t i;
	for (array<RowCol, 9> ul : rcUnitList) {
		i = 0;
		for (RowCol rc : ul) {
			str[i] = puzzle[ul[i].row][ul[i].col][0];
			i++;
		}
		str[i] = '\0';
<<<<<<< Updated upstream
		for (uint8_t j = 0; j < 9; j++) {
			if (strchr(str, digits[j]) == NULL)
=======
		for (i = 0; i < 9; i++) {
			if (strchr(str, digits[i]) == NULL)
>>>>>>> Stashed changes
				return false;
		}
	}
    return true;
//    char str[10];
//    str[9] = '\0';
//    uint8_t i;
//    for (array<RowCol, 9> ul : rcUnitList) {
//        i = 0;
//        for (RowCol rc : ul) {
//            str[i] = puzzle[ul[i].row][ul[i].col][0];
//            i++;
//        }
//        str[i] = '\0';
//        for (uint8_t j = 0; j < 9; j++) {
//            if (strchr(str, digits[i]) == NULL)
//                return false;
//        }
//    }
//    return true;
}

bool Sudoku::removeGuess(RowCol rc, char value){
	bool retval = true;
    int16_t r=rc.row;
    int16_t c=rc.col;
	string temp = allowableValues[r][c];
	if (temp.find(value) == string::npos)
		retval = false;
	else {
		temp = allowableValues[r][c];
		size_t t = temp.find(value);
		if (t != string::npos) {
			temp.replace(t, 1, "");
			allowableValues[r][c] = temp;
			retval = true;
		} else {
			retval = false;
		}
	}
	return retval;
}

bool Sudoku::guessesRemain(void) {
    for(auto r:rows) {
        for (auto c:cols) {
            if(allowableValues[r][c].length() > 1)
                return true;
        }
	}
	return false;
}

Guess Sudoku::getGuess() { // returns square, value
	// guess is returned as square,value in an array
	uint8_t minCount = 9;
	// iterate through squares and get lowest count > 1
	size_t len;
    for(auto r:rows) {
        for (auto c:cols) {
            len = allowableValues[r][c].size();
            if ( len > 1 ) {
                if (len < minCount)
                {
                    minCount = (uint8_t)len;
                }
            }
        }
	}
	vector<RowCol> subset;
    for(auto r:rows) {
        for (auto c:cols) {
            if ((uint8_t)allowableValues[r][c].size() == minCount) {
                subset.push_back(RowCol(r,c));
            }
        }
    }
	// select random vector
	RowCol square = subset[rand() % subset.size()];
    string temp = allowableValues[square.row][square.col];
	char t = temp[rand() % temp.length()];
	//newGuess = Guess(square, string(1,t), puzzle, allowableValues);
	return Guess(square, t, puzzle, allowableValues);
}

bool Sudoku::popGuess() {
    if(guessNumber == 0)
        return false;
    Guess lastGuess;
    lastGuess = guessList[guessNumber-1];
    puzzle = lastGuess.puzzle;
    allowableValues = lastGuess.allowableValues;
    removeGuess(lastGuess.square, lastGuess.guess);
    guessNumber--;
    cout << "pop " << lastGuess.square << ":" << (char)lastGuess.guess << " -- ";
    printGuessList();
	return true;
}

void Sudoku::pushGuess(const Guess guess) {
	guessList[guessNumber] = guess;
    cout << "push " << guess.square << ":" << (char)guess.guess << " -- ";
    printGuessList();
    guessNumber++;

}

void Sudoku::printGuessList() {
    if (guessNumber == 0)
        cout << "Empty";
    else {
        cout << guessNumber << " ";
        for(uint8_t i = 0 ; i < guessNumber ; i++) {
            cout << guessList[i].square.toString() << ":" << guessList[i].guess << " ";
        }
    }
	cout << endl << flush;
}

bool Sudoku::solvePuzzle() {
	solveOnes();
	if (isPuzzleSolved())
		return true;
	else 
		startGuessing();
	return isPuzzleSolved();
}

bool Sudoku::startGuessing() {
	guessNumber = 0;
	while(!isPuzzleSolved()) {
		while (guessesRemain()) {
			Guess g = getGuess();
            guessNumber++;
			pushGuess(g);
			setValue(g.square, g.guess);
			solveOnes();
			if (isPuzzleSolved() == false && guessesRemain() == false) {
				popGuess();
			}
		}
 		if (isPuzzleSolved() == false) {
			if(popGuess() == false) {
				return false;
			}
		}
			
	}

	return isPuzzleSolved();
}

void Sudoku::test(void) {

 }
