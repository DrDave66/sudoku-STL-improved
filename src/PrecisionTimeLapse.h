#pragma once
#ifndef _PRECISIONTIMELAPSE
#define _PRECISIONTIMELAPSE

#include <chrono>
#include <string>

using namespace std;
using namespace std::chrono; 

enum TIME_UNIT {
	SEC = 1, 
	MILLISEC = 1000,
	MICROSEC = 1000000,
	NANOSEC = 1000000000
} ;

class PrecisionTimeLapse  
{
	private:
		high_resolution_clock::time_point begin;
		high_resolution_clock::time_point end;
		duration<double> time_lapse;
	public:
		PrecisionTimeLapse();
		void start();
		void stop();
		double elapsed();
		string elapsedString();
		string elapsedString(TIME_UNIT);
};
#endif

