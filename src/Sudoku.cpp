#include "Sudoku.h"
#define NOTIMING

Sudoku::Sudoku() {
	createVectors();
	clearPuzzle();
	srand((uint32_t)time(NULL));
}

Sudoku::Sudoku(string puzzle) {
	createVectors();
	setPuzzle(puzzle);
	srand((uint32_t)time(NULL));
}

vector<RowCol> Sudoku::crossProductRC(vector<int16_t> a, vector<int16_t> b) {
#define noPRINTCROSS
    static vector<RowCol> v;
    v.clear();
    RowCol rc;
    for(uint16_t aa : a) {
        for (uint16_t bb : b) {
            rc.set(aa,bb);
#ifdef PRINTCROSS
            printf("CPV %u %u\n", aa, bb);
#endif
            v.push_back(rc);
        }
    }
#ifdef PRINTCROSS
    cout << endl;
#endif
    return v;
}


void Sudoku::createVectors(void) {
//	// create vector of squares
#define noPRINTVECTORS
    
    uint32_t i;
    vector<RowCol> rcv;

    for (auto r:rows) {
        for (auto c:cols) {
            puzzle[r][c] = ".";
            allowableValues[r][c] = "123456789";
        }
    }
    // create unitlist array
	vector<RowCol> temp;
    int16_t ul = 0;
    array<RowCol,9> ts;
    vector<int16_t> v1;
    ul = 0;
  	// for each col across the rows
	for (uint16_t c : cols) {
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
	for (uint16_t r : rows) {
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
	vector<vector<int16_t> > sr;
    vector<vector<int16_t> > sc;
    sr.push_back(vector<int16_t> {0,1,2});
	sr.push_back(vector<int16_t> {3,4,5});
	sr.push_back(vector<int16_t> {6,7,8});
	sc.push_back(vector<int16_t> {0,1,2});
	sc.push_back(vector<int16_t> {3,4,5});
	sc.push_back(vector<int16_t> {6,7,8});
	for (vector<int16_t> r : sr) {
		for (vector<int16_t> c : sc) {
            i = 0;
            temp = crossProductRC(r,c);
            for (RowCol s : temp) {
                rcUnitList[ul][i] = s;
                i++;
            }
            ul++;
        }

	}
#ifdef PRINTVECTORS
    cout << endl << "UnitList" << endl;
    for(int j = 0 ; j < 27 ; j++) {
        for (i = 0 ; i < 9 ;i++) {
            cout << rcUnitList[j][i] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
#endif
//    // unit dictionary
    RowCol sq;
    uint32_t unum = 0;
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
#ifdef PRINTVECTORS
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
#endif
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
            RowCol rc(r,c);
            setValue(r,c,string(1,p[c+ r*9]));
        }
    }
	return true;
}

/**********************************************************
**********   Printing Functions ***************************
***********************************************************/
string Sudoku::printableStringVector(vector<string> vec) {
	string s;
	for (string v : vec) {
		s += v;
		s += " ";
	}
	return s;
}

string Sudoku::printableStringSet(set<string> st) {
	string s;
	for (string v : st) {
		s += v;
		s += " ";
	}
	return s;
}

string Sudoku::printableVectorVectorString(vector<vector<string> > vvs) {
	string s;
	for (vector<string> vs : vvs) {
		for (string v : vs) {
			s += v;
			s += " ";
		}
		s += "\n";
	}
	return s;
}

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
bool Sudoku::setValue(int16_t r, int16_t c, string value) {
#ifdef TIMING
	PrecisionTimeLapse ptl;
	ptl.start();
#endif 	
    size_t t;
    int16_t rr,cc;
    RowCol rc(r, c);
//   cout << "SVI  " << r << " " << c << " " << value << endl;
 //   cout << "SVRC " << rc << " " << value << endl;
    if (value == "." || value == "0") {
        //allowableValues[r][c] = digitsText;
        puzzle[r][c] = value;
        return true;
    } else {
        if (allowableValues[r][c].find(value) == string::npos)
            return false;
        allowableValues[r][c] = "";
        puzzle[r][c] = value;
    }
	string temp;

	for (RowCol p : rcPeers[r][c]) {
        rr = p.r();
        cc = p.c();
        
        temp = allowableValues[rr][cc];
        t = temp.find(value);
		if (t != string::npos) {
			temp.replace(t, 1, "");
            allowableValues[rr][cc] = temp;
		}
    }

#ifdef TIMING
	ptl.stop();
	cout << "setValue," << ptl.elapsedString() << endl;
#endif
	return true;
}

bool Sudoku::setValue(RowCol rc, string value) {
    return setValue(rc.r(), rc.c(), value);
    return true;
}

bool Sudoku::solveOnes(void) {
#ifdef TIMING	
	PrecisionTimeLapse ptl;
	ptl.start();
#endif	
	bool solvedSome = true;
    uint32_t iteration = 0;
    uint32_t maxIteration = 81;
	while (solvedSome == true && iteration < maxIteration) {
        iteration++;
		solvedSome = false;
		// find squares with only one available value
        for (auto r:rows){
            for (auto c:cols) {
                if (allowableValues[r][c].size() == 1) {
                    // and set the value
                    solvedSome = true;
                    setValue(r, c, allowableValues[r][c]);
                }
            }
        }
        // look through all units and see if any value appears only one time

        for(array<RowCol,9> ul : rcUnitList) {
            string allValues = "";
			for (RowCol rc : ul) {
                allValues += allowableValues[rc.r()][rc.c()];
			}
			for (char d : digitsText) {
				// if number appears once
				if (count(allValues.begin(), allValues.end(), d) == 1) {
					// find the square with the value in it
					for (RowCol u : ul) {
						if (count(allowableValues[u.r()][u.c()].begin(), allowableValues[u.r()][u.c()].end(), d) == 1) {
							solvedSome = true;
							setValue(u, string(1, d));
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
	set<string> unitSet;
	for (array<RowCol,9> ul : rcUnitList) {
		unitSet.clear();
        for(RowCol rc:ul) {
            unitSet.insert(puzzle[rc.r()][rc.c()]);
        }
        if (unitSet != digitSet)
            return false;
	}
    return true;
}

string Sudoku::getPuzzleText(void) {
	string retval;
    for (auto r:rows) {
        for (auto c:cols) {
            retval += puzzle[r][c];
        }
	}
	return retval;
}

string Sudoku::getAllowableGuessesText(void) {
    string retval;
    string delim = "|";
    for (auto r:rows) {
        for (auto c:cols) {
            if (allowableValues[r][c] != "") {
                retval += allowableValues[r][c];
            } else {
                retval += "0";
            }
            retval += delim;
        }
    }
    return retval;
}

string Sudoku::getPackedPuzzle(void) {
	string retval;
	retval = getPuzzleText() + "_" + getAllowableGuessesText();
	return retval;
}

void Sudoku::unpackPuzzle(string packed) {
	size_t us = packed.find('_');
	string puzzleString = packed.substr(0,us);
	string allowString = packed.substr(us+1);
	vector<string> allow;
    for (auto r:rows) {
        for (auto c:cols) {
            puzzle[r][c] = puzzleString.substr(c + 9*r,1);
        }
	}
	size_t vstart = 0;
	size_t vend = -1;
	string temp;
    for (auto r:rows) {
        for (auto c:cols) {
            vend = allowString.find('|',vstart);
            temp = allowString.substr(vstart, vend - vstart);
            if (temp == "0") {
                allowableValues[r][c] = "";
            } else {
                allowableValues[r][c] = temp;
            }
            vstart = vend+1;
        }
    }
}

bool Sudoku::removeGuess(RowCol rc, string value){
	bool retval = true;
    int16_t r=rc.r();
    int16_t c=rc.c();
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
	uint32_t minCount = 9;
	// iterate through squares and get lowest count > 1
	size_t len;
    for(auto r:rows) {
        for (auto c:cols) {
            len = allowableValues[r][c].size();
            if ( len > 1 ) {
                if (len < minCount)
                {
                    minCount = (uint32_t)len;
                }
            }
        }
	}
	vector<RowCol> subset;
    for(auto r:rows) {
        for (auto c:cols) {
            if (allowableValues[r][c].size() == minCount) {
                subset.push_back(RowCol(r,c));
            }
        }
    }
	// select random vector
	RowCol square = subset[rand() % subset.size()];
    string temp = allowableValues[square.r()][square.c()];
	char t = temp[rand() % temp.length()];
	//newGuess = Guess(square, string(1,t), puzzle, allowableValues);
	return Guess(square, string(1,t), puzzle, allowableValues);;
}

bool Sudoku::popGuess() {
    if(guessNumber == 0)
        return false;
    guessNumber--;
    Guess lastGuess;
    lastGuess = guessList[guessNumber];
    puzzle = lastGuess.puzzle;
    allowableValues = lastGuess.allowableValues;
    removeGuess(lastGuess.square, lastGuess.guess);
	return true;
}

void Sudoku::pushGuess(const Guess guess) {
	guessList[guessNumber] = guess;
    guessNumber++;
}

void Sudoku::printGuessList() {
    if (guessNumber == 0)
        cout << "Empty";
    else {
        for(int16_t i = 0 ; i < guessNumber ; i++) {
            cout << guessList[i].square << ":" << guessList[i].guess << " ";
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
			pushGuess(g);
			setValue(g.square, g.guess);
			solveOnes();
			if (isPuzzleSolved() == false && guessesRemain() == false) {
				popGuess();
			}
		}
		if (isPuzzleSolved() == false) {
			if (guessList.size() == 0) {
			}
			if(popGuess() == false) {
				return false;
			}
		}
			
	}
	return isPuzzleSolved();
}

//string Sudoku::RCToString(ROWCOL rc) {
//    static string retval = "";
//    retval = "";
//    retval += (char)('A' + RC_r(rc));
//    retval += (char)('1' + RC_c(rc));
//    return retval;
//}

//ROWCOL Sudoku::stringToRC(string rct) {
//    const char* pstr = rct.c_str();
//    return make_tuple((uint8_t)(pstr[0] - 'A'),(char)atoi(&pstr[1]) - 1);
//}

void Sudoku::test(void) {

 }

void Sudoku::printPeers(RowCol rc) {
    set<RowCol> src;
    for(RowCol p : rcPeers[rc.r()][rc.c()]) {
        src.insert(p);
    }
    
    cout << "Peers (" << rc << "): ";
    for(RowCol p : src) {
        cout << p << " ";
    }
    cout << endl;
    
}