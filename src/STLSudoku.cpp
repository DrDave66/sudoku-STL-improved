// vcSudoku.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Puzzles.h"
#include "Sudoku.h"
#include "PrecisionTimeLapse.h"
#include "SudokuTypes.h"
// solved with ones/peers
string grid1 =   "..3.2.6..9..3.5..1..18.64....81.29..7.......8..67.82....26.95..8..2.3..9..5.1.3..";
string grid3 =   "8.2.5.7.1..7.8246..1.9.....6....18325.......91843....6.....4.2..9561.3..3.8.9.6.7";
// not solved with ones/peers
string easy505 = "1..92....524.1...........7..5...81.2.........4.27...9..6...........3.945....71..6";
string grid2 =   "4.....8.5.3..........7......2.....6.....8.4......1.......6.3.7.5..2.....1.4......";
string hard1 =   ".....6....59.....82....8....45........3........6..3.54...325..6..................";
string easy506 = ".43.8.25.6.............1.949....4.7....6.8....1.2....382.5.............5.34.9.71.";

// solved puzzles
string solved1 = "431829765276513984598467312389251647642378591157946238964785123723194856815632479";
string solved2 = "687942351591376284342158769465239178138567942279814635853791426924683517716425893";
string solved3 = "523846917961537428487219653154693782632478195798152346879324561316985274245761839";
string solved4 = "152483679697152348438976251314765892869241735275398164786524913941837526523619487";
#define SHORTMAIN

#ifdef SHORTMAIN
int main() {
    Sudoku s(solved1);

    s.printPuzzle();
    s.printAllowableValues();
    s.solveOnes();
    s.printPuzzle();
    s.printAllowableValues();
}

#else
int main()
{

	Puzzles p;
	Puzzles pf("../sudoku-puzzles/1000P.txt");
	cout << pf.getNumberOfPuzzles() << " puzzles loaded" << endl;
	if (pf.getNumberOfPuzzles() == 0)
		return 1;
	Sudoku s;
	PrecisionTimeLapse total;
	PrecisionTimeLapse ptl;
	int solved = 0;
	double minTime = 100000.0;
	double maxTime = 0.0;
	double sumTime =  0.0;
	double time;
	total.start();
    malloc
	for (uint32_t i = 0; i < pf.getNumberOfPuzzles(); i++) {
#ifdef PRINTING
        cout << i+1 << " ";
#endif
		s.setPuzzle(pf.getPuzzle(i));
		ptl.start();
		s.solvePuzzle();
		ptl.stop();
		if (s.isPuzzleSolved() == true)
		{
   			solved += 1;
#ifdef PRINTING
			cout << "SOLVED\n";
#endif
			//s.printPuzzle();
		}
		else {
#ifdef PRINTING
			cout << "NOTSOLVED \n";
#endif
		}
		time = ptl.elapsed();

		minTime = min(minTime, time);
		maxTime = max(maxTime, time);
		sumTime += time;
		//cout << time << " " << sumTime << "  ";
		//cout << "Total time: " << ptl.elapsedString() << " solved " << solved << " out of " << i+1 << endl;
        if(i % 1000 == 0)
            cout << i << endl;
		
	}
	total.stop();
    //cout << " Total time: " << total.elapsed() << " seconds" << endl;
    cout << "Solved " << solved << " out of " << pf.getNumberOfPuzzles() << " puzzles\n";
	cout << "Min time: " << minTime*1000.0 << " ms, Max time: " << maxTime*1000.0 << " ms, Average Time: " << (double)sumTime / (double)solved * 1000 << " ms, Total: " << total.elapsedString(SEC) << " sec" << endl;

}

#endif

// time for 10000P.txt - Min time: 0.2968 ms, Max time: 1.1741 ms, Average Time: 0.468564 ms, Total: 8.292689 sec
// for 5000P.txt -       Min time: 0.3026 ms, Max time: 1.0865 ms, Average Time: 0.466454 ms, Total: 4.142156 sec

// mac release
//blank constructor
//parameter ../../../../SudokuPuzzles/5000P.txt
//5000 puzzles loaded
//Solved 5000 out of 5000 puzzles
//Min time: 0.111575 ms, Max time: 19.5198 ms, Average Time: 0.163679 ms, Total: 1.376686 sec
//Program ended with exit code: 0

// mac debug
//blank constructor
//parameter ../../../../SudokuPuzzles/5000P.txt
//5000 puzzles loaded
//Solved 5000 out of 5000 puzzles
//Min time: 0.466408 ms, Max time: 88.6324 ms, Average Time: 0.572413 ms, Total: 4.465807 sec
//Program ended with exit code: 0

// 	    1   2   3    4   5   6    7   8   9
//   =========================================
// A || . | 4 | 3 || . | 8 | . || 2 | 5 | . ||
// B || 6 | . | . || . | . | . || . | . | . ||
// C || . | . | . || . | . | 1 || . | 9 | 4 ||
//   || --------- || --------- || --------- ||
// D || 9 | . | . || . | . | 4 || . | 7 | . ||
// E || . | . | . || 6 | . | 8 || . | . | . ||
// F || . | 1 | . || 2 | . | . || . | . | 3 ||
//   || --------- || --------- || --------- ||
// G || 8 | 2 | . || 5 | . | . || . | . | . ||
// H || . | . | . || . | . | . || . | . | 5 ||
// I || . | 3 | 4 || . | 9 | . || 7 | 1 | . ||
//   =========================================

//      1   2   3    4   5   6    7   8   9
//   =========================================
// A || 1 | 4 | 3 || 9 | 8 | 6 || 2 | 5 | 7 ||
// B || 6 | 7 | 9 || 4 | 2 | 5 || 3 | 8 | 1 ||
// C || 2 | 8 | 5 || 7 | 3 | 1 || 6 | 9 | 4 ||
//   || --------- || --------- || --------- ||
// D || 9 | 6 | 2 || 3 | 5 | 4 || 1 | 7 | 8 ||
// E || 3 | 5 | 7 || 6 | 1 | 8 || 9 | 4 | 2 ||
// F || 4 | 1 | 8 || 2 | 7 | 9 || 5 | 6 | 3 ||
//   || --------- || --------- || --------- ||
// G || 8 | 2 | 1 || 5 | 6 | 7 || 4 | 3 | 9 ||
// H || 7 | 9 | 6 || 1 | 4 | 3 || 8 | 2 | 5 ||
// I || 5 | 3 | 4 || 8 | 9 | 2 || 7 | 1 | 6 ||
//   =========================================
// Puzzle 6, Solved = True, Time = 0.2327 ms


// solved with ones/peers
// grid1 = '003020600900305001001806400008102900700000008006708200002609500800203009005010300'
// grid3 = "802050701007082460010900000600001832500000009184300006000004020095610300308090607"


// not solved with ones/peers
// easy505 = "1..92....524.1...........7..5...81.2.........4.27...9..6...........3.945....71..6"
// grid2 = '4.....8.5.3..........7......2.....6.....8.4......1.......6.3.7.5..2.....1.4......'
// hard1 = '.....6....59.....82....8....45........3........6..3.54...325..6..................'
