#include <stdlib.h>
#include <time.h>

#include "NumberOfDiscIntersections.h"
#include "Brackets.h"
#include "Fish.h"
#include "Nesting.h"
#include "StoneWall.h"
#include "Dominator.h"
#include "EquiLeader.h"

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

	vector<int> A = { 4, 3, 4, 4, 4, 2 };

	EquiLeader equiLeader;
	equiLeader.solution(A);

	_CrtDumpMemoryLeaks();

	return EXIT_SUCCESS;
}


          