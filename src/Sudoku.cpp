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

vector<ROWCOL> Sudoku::crossProductRC(vector<int16_t> a, vector<int16_t> b) {
#define NOPRINTCROSS
    static vector<ROWCOL> v;
    v.clear();
    ROWCOL rc;
    for(uint16_t aa : a) {
        for (uint16_t bb : b) {
            rc = make_tuple(aa, bb);
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
	// create vector of squares
    
    uint32_t i;
    vector<ROWCOL> rcv;
    
    rcv = crossProductRC(rows, cols);
    for(auto r:rows) {
        for(auto c:cols) {
            rcSquares[r][c] = rcv[r + c*9];
        }
    }
//    cout << "squares:" << endl;
//    for(auto r:rows) {
//        for(auto c:cols) {
//            cout << RCToString(rcSquares[r][c]) << " ";
//        }
//        cout << endl;
//    }
//    cout << endl;
    
    // create unitlist array
	vector<ROWCOL> temp;
    int16_t ul = 0;
    array<ROWCOL,9> ts;
    vector<int16_t> v1;
    ul = 0;
  	// for each col across the rows
	for (uint16_t c : cols) {
        v1.clear();
        v1.push_back(c);
		temp = crossProductRC(rows, v1);
        i = 0;
        for (ROWCOL s : temp) {
            rcUnitList[ul][i] = s;
            i++;
        }
        ul++;
	}
    cout << endl << endl;
// for each row across the cols
	for (uint16_t r : rows) {
        v1.clear();
        v1.push_back(r);
		temp = crossProductRC(v1, rows);
        i = 0;
        for (ROWCOL s : temp) {
            rcUnitList[ul][i] = s;
            i++;
        }
        ul++;
    }

    cout << endl << endl;
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
                for (ROWCOL s : temp) {
                    rcUnitList[ul][i] = s;
                    i++;
                }
                ul++;
        }

	}
//    cout << endl << "UnitList" << endl;
//    for(int j = 0 ; j < 27 ; j++) {
//        for (i = 0 ; i < 9 ;i++) {
//            cout << RCToString(rcUnitList[j][i]) << " ";
//        }
//        cout << endl;
//    }
//    cout << endl << endl;

//    // unit dictionary
    ROWCOL sq;
    uint32_t unum = 0;
    for(auto r : rows) {
        for (auto c : cols) {
            unum = 0;
            sq = rcSquares[r][c];
            for (array<ROWCOL,9> ul : rcUnitList){
                for(i = 0 ; i < 9 ; i++) {
                    if (ul[i] == sq) {
                        rcUnits[r][c][unum] = ul;
                        unum++;

                    }
                }
            }
        }
    }
//    cout << endl << endl;
//    for (auto r : rows) {
//        for (auto c : cols) {
//            sq = rcSquares[r][c];
//            cout << "New Unit Dict: " << RCToString(sq) << " " << endl;
//            for ( int unum = 0 ; unum < 3 ; unum++) {
//                for (i = 0 ; i < 9 ; i++) {
//                    cout << RCToString(rcUnits[r][c][unum][i]) << " ";
//                }
//                cout << endl;
//            }
//            cout << endl;
//        }
//    }
////	// make peer dictionary
    int pnum = 0;
    set<ROWCOL> peerSet;
    for(auto r : rows) {
        for (auto c : cols) {
            pnum = 0;
            peerSet.clear();
            sq = rcSquares[r][c];
            for(array<ROWCOL,9> ul : rcUnits[r][c]) {
                for(ROWCOL u : ul) {
                    if (u != sq) {
                        peerSet.insert(u);
                    }
                }
            }
            for(ROWCOL ps : peerSet) {
                //peers[sq][pnum] = ps;
                rcPeers[r][c][pnum] = ps;
                pnum++;
            }
        }
    }
    cout << endl << endl << "New Peer dictionary" << endl;
    for(int16_t r : rows) {
        for (int16_t c: cols) {
            sq = rcSquares[r][c];
            cout << "New Peer : " << RCToString(sq) << ": ";
            for(ROWCOL p : rcPeers[r][c]) {
                cout << RCToString(p) << " ";
            }
            cout << endl;
        }
    }
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
            setValue(r,c,string(1,p[c+ r*9]));
            ROWCOL rc = make_tuple(r,c);
            cout << "set " << RCToString(rc) << " to " << string(1,p[c+ r*9]) << endl;
            printPuzzle();
            printAllowableValues();
            
            
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
    uint16_t rr,cc;
    ROWCOL rc = make_tuple(r, c);
    cout << "SVI  " << r << " " << c << " " << value << endl;
    cout << "SVRC " << RC_r(rc) << " " << RC_c(rc) << " " << value << endl;
    if (value == "." || value == "0") {
        allowableValues[r][c] = digitsText;
        puzzle[r][c] = value;
        return true;
    } else {
        if (allowableValues[r][c].find(value) == string::npos)
            return false;
        allowableValues[r][c] = "";
        puzzle[r][c] = value;
    }
	string temp;

	for (ROWCOL p : rcPeers[r][c]) {
        rr = RC_r(p);
        cc = RC_c(p);
        
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

bool Sudoku::setValue(ROWCOL rc, string value) {
    return setValue(RC_r(rc),RC_c(rc),value);
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

        for(array<ROWCOL,9> ul : rcUnitList) {
            string allValues = "";
			for (ROWCOL rc : ul) {
                allValues += allowableValues[RC_r(rc)][RC_c(rc)];
			}
			for (char d : digitsText) {
				// if number appears once
				if (count(allValues.begin(), allValues.end(), d) == 1) {
					// find the square with the value in it
					for (ROWCOL u : ul) {
						if (count(allowableValues[RC_r(u)][RC_c(u)].begin(), allowableValues[RC_r(u)][RC_c(u)].end(), d) == 1) {
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
//	set<string> unitSet;
//	for (vector<string> ul : unitlist) {
//		unitSet.clear();
//		for (string u : ul) {
//			unitSet.insert(puzzle[u]);
//		}
//		if (unitSet != digitSet)
//			return false;
//	}
//	
    return true;
}

string Sudoku::getPuzzleText(void) {
	string retval;
//	for (string s : squares) {
//		retval += puzzle[s];
//	}
	return retval;
}

string Sudoku::getAllowableGuessesText(void) {
	string retval;
//	string delim = "|";
//	for (string s : squares) {
//		if (allowableValues[s] != "") {
//			retval += allowableValues[s];
//		} else {
//			retval += "0";
//		}
//		retval += delim;
//	}
	return retval;
}

string Sudoku::getPackedPuzzle(void) {
	string retval;
	retval = getPuzzleText() + "_" + getAllowableGuessesText();
	return retval;
}

void Sudoku::unpackPuzzle(string packed) {
//	size_t us = packed.find('_');
//	string puzzleString = packed.substr(0,us);
//	string allowString = packed.substr(us+1);
//	vector<string> allow;
//	for ( int i = 0 ; i < 81 ; i++) {
//		puzzle[squares[i]] = puzzleString.substr(i,1);
//	}
//	size_t vstart = 0;
//	size_t vend = -1;
//	string temp;
//	for( int i = 0 ; i < 81 ; i++) {
//		vend = allowString.find('|',vstart);
//		temp = allowString.substr(vstart, vend - vstart);
//		if (temp == "0") {
//			allowableValues[squares[i]] = "";
//		} else {
//			allowableValues[squares[i]] = temp;
//		}
//		vstart = vend+1;
//	}
}

bool Sudoku::removeGuess(string square, string value){
	bool retval = true;
//	string temp = allowableValues[square];
//	if (temp.find(value) == string::npos)
//		retval = false;
//	else {
//		temp = allowableValues[square];
//		size_t t = temp.find(value);
//		if (t != string::npos) {
//			temp.replace(t, 1, "");
//			allowableValues[square] = temp;
//			retval = true;
//		} else {
//			retval = false;
//		}
//	}
	return retval;
}

bool Sudoku::guessesRemain(void) {
//	for (string s : squares) {
//		if(allowableValues[s].length() > 1)
//            return true;
//	}
	return false;
}

Guess Sudoku::getGuess() { // returns square, value
//	// guess is returned as square,value in an array
//	uint32_t minCount = 9;
//	// iterate through squares and get lowest count > 1
//	size_t len;
//	for (string s : squares) {
//		len = allowableValues[s].size();
//		if ( len > 1 ) {
//			if (len < minCount) 
//			{
//				minCount = (uint32_t)len;
//			}
//		}
//	}
//	vector<string> subset;
//	for (string s : squares) {
//		if (allowableValues[s].size() == minCount) {
//			subset.push_back(s);
//		}
//	}
//	// select random vector
//	string square = subset[rand() % subset.size()];
//	char t = allowableValues[square][rand() % allowableValues[square].size()];
//	string pt = getPackedPuzzle();
//	newGuess = Guess(pt, square, string(1,t));
	return Guess();
}

bool Sudoku::popGuess() {
//	Guess lastGuess = guessList.back();
//	if (lastGuess.puzzleString.length() == 0 || lastGuess.square.length() == 0 || lastGuess.guess.length() == 0 )
//		return false;
//	else {
//		unpackPuzzle(lastGuess.puzzleString);
//		removeGuess(lastGuess.square, lastGuess.guess);
//		guessList.pop_back();
//	}
	return true;
}

void Sudoku::pushGuess(Guess const *guess) {
//	Guess g;
//	g.guess = guess->guess;
//	g.square = guess->square;
//	g.puzzleString = string(guess->puzzleString);
//	guessList.push_back(g);
}

void Sudoku::printGuessList() {
	for (Guess& g : guessList) {
		cout << g.square << ":" << g.guess << " ";
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
//	guessList.clear();
//	while(!isPuzzleSolved()) {
//		while (guessesRemain()) {
//			Guess g = getGuess();
//			pushGuess(&g);
//			setValue(g.square, g.guess);
//			solveOnes();
//			if (isPuzzleSolved() == false && guessesRemain() == false) {
//				popGuess();
//			}
//		}
//		if (isPuzzleSolved() == false) {
//			if (guessList.size() == 0) {
//			}
//			if(popGuess() == false) {
//				return false;
//			}
//		}
//			
//	}
	return isPuzzleSolved();
}

string Sudoku::RCToString(ROWCOL rc) {
    static string retval = "";
    retval = "";
    retval += (char)('A' + RC_r(rc));
    retval += (char)('1' + RC_c(rc));
    return retval;
}

//ROWCOL Sudoku::stringToRC(string rct) {
//    const char* pstr = rct.c_str();
//    return make_tuple((uint8_t)(pstr[0] - 'A'),(char)atoi(&pstr[1]) - 1);
//}

 void Sudoku::test(void) {

 }
