
#include "Puzzles.h"
#include <stdio.h>
#include <stdlib.h>


Puzzles::Puzzles() {
	numPuzzles = 0; 
	filename = "";
} 

Puzzles::Puzzles(string fname) { 
	loadFromFile(fname);
}

uint32_t Puzzles::loadFromFile(string fname) {
//	cout << "parameter " << fname << "\n";
	filename = fname;
	fstream file;
	file.open(filename, ios::in);
	if (file.is_open()) {
		puzzles.clear();
		string str;
		while (getline(file, str)) {
			puzzles.push_back(str);
		}
	} else {
		printf("File %s does not exist\n", fname.c_str());
		filename = "";
		numPuzzles = 0;
	}
	numPuzzles = (uint32_t)puzzles.size();
	return numPuzzles;
}

uint32_t Puzzles::getNumberOfPuzzles(void) {
	return numPuzzles;
}

string Puzzles::getPuzzle(uint32_t num) {
	return puzzles[num];
}

