#include <stdlib.h>

#include "NumberOfDiscIntersections.h"
#include "Brackets.h"

int main()
{
	//_CrtSetBreakAlloc(146);

	/*const int N = 6;
	int A[] = { 1, 5, 2, 1, 4, 0 };
	NumberOfDiscIntersections numb;
	numb.solution(A, N);*/

	string S = "[()}";

	Brackets bracket;
	int Value = bracket.solution(S);

	S.clear();

	_CrtDumpMemoryLeaks();

	return EXIT_SUCCESS;
}


          