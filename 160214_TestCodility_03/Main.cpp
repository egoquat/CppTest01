#include <stdlib.h>
#include <time.h>

#include "NumberOfDiscIntersections.h"
#include "Brackets.h"
#include "Fish.h"
#include "Nesting.h"
#include "StoneWall.h"
#include "Dominator.h"
#include "EquiLeader.h"
#include "MaxDoubleSliceSum.h"
#include "MaxProfit.h"
#include "MaxSliceSum.h"
#include "MinPerimeterRectangle.h"
#include "Flags.h"
#include "Peaks.h"

typedef unsigned int uint;

int main()
{
	//_CrtSetBreakAlloc(146);

	/*const int N = 6;
	int A[] = { 1, 5, 2, 1, 4, 0 };
	NumberOfDiscIntersections numb;
	numb.solution(A, N);*/

	/*string S = "[()}";

	Brackets bracket;
	int Value = bracket.solution(S);

	S.clear();*/

	/*vector<int> fishes = { 4, 3, 2, 1, 5 };
	vector<int> UpDowns = { 0, 1, 0, 0, 0 };*/

	/*vector<int> fishes = { 0, 1 };
	vector<int> UpDowns = { 1, 1 };*/

	/*vector<int> fishes = { 0, 2, 3, 1, 0, 5 };
	vector<int> UpDowns = { 1, 1, 1, 1, 1, 0 };*/

	/*vector<int> fishes = { 5, 3, 2, 1, 4 };
	vector<int> UpDowns = { 1, 0, 1, 0, 1 };*/

	/*vector<int> fishes = { 5, 4, 3, 2, 1, 0 };
	vector<int> UpDowns = { 1, 0, 1, 1, 1, 0 };*/

	/*const int N = 100000;
	vector<int> fishes, UpDowns;

	fishes.reserve(N);
	UpDowns.reserve(N);

	srand(time(NULL));
	for (int i = 0; i < N; ++i)
	{
		fishes.push_back(rand() % 100000);

		if (i == N - 1)
		{
			UpDowns.push_back(0);
		}
		else
		{
			UpDowns.push_back(1);
		}
	}*/

	/*Fish fish;
		
	fish.solution(fishes, UpDowns);

	fishes.clear(); UpDowns.clear();*/

	/*string S = "())";
	Nesting nesting;
	nesting.solution(S);*/

	/*vector<int> H = { 8, 8
	, 5, 7, 9, 8, 7, 4, 8 };

	StoneWall stoneWall;
	stoneWall.solution(H);*/

	//vector<int> A = {3,4,3,2,3,-1,3,3};
	//vector<int> A = { 3, 4, 3, 2, 3, -1, 1, 8 };

	/*Dominator dominator;
	dominator.solution(A);*/

	/*vector<int> A = { 4, 3, 4, 4, 4, 2 };

	EquiLeader equiLeader;
	equiLeader.solution(A);*/

	//vector<int> A = { 3, 2, 6, -1, 4, 5, -1, 2 };
	//MaxDoubleSliceSum maxDoubleSlice;
	//maxDoubleSlice.solution(A);

	/*vector<int> A = { 23171, 21011, 21123, 21366, 21013, 21367 };
	MaxProfit maxProfit;
	maxProfit.solution(A);*/

	/*vector<int> A = { 3, 2, -6, 4, 0 };
	MaxSliceSum maxSliceSum;
	maxSliceSum.solution(A);*/

	/*const int N = 30;
	MinPerimeterRectangle minPerimeterRectangle;
	minPerimeterRectangle.solution(N);*/

	/*vector<int> A = { 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	Flags flags;
	flags.solution(A);*/

	/*vector<int> A = { 1, 2, 3, 4, 3, 4, 1, 2, 3, 4, 6, 2 };
	Peaks peaks;
	peaks.solution(A);*/
	
	int hex = 0xff;
	int decimal = 0;
	for (int i = 0; i < 31; ++i)
	{
		decimal += ((1 << i) & hex) ? (1 << i) : 0;
	}

	printf("%d", decimal);

	/*string MESSAGE = "C";
	string B;

	{
		char c = MESSAGE[0];
		B += ((1 << 0) & c) ? "1" : "0";

		for (uint b = 1; (1 << b) <= ((int)c); ++b)
		{
			B += ((1 << (b - 1)) & c) ? "1" : "0";
		}
	}*/

	_CrtDumpMemoryLeaks();

	return EXIT_SUCCESS;
}


          