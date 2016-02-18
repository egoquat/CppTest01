#include <stdlib.h>

#include "NumberOfDiscIntersections.h"
#include "Brackets.h"

int main()
{
	/*const int N = 6;
	int A[] = { 1, 5, 2, 1, 4, 0 };
	NumberOfDiscIntersections numb;
	numb.solution(A, N);*/

	char S[5];
	sprintf(S, "we{(}");

	Brackets bracket;
	bracket.solution(S);

	return EXIT_SUCCESS;
}

