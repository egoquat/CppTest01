#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "MissingInteger.h"

static void shuffle(int A[], int N)
{
	for (int i = 0; i < N; ++i)
	{
		int iran = rand() % N;
		int value = A[i];
		A[i] = A[iran];
		A[iran] = value;
	}
}

int main()
{
	MissingInteger missingInteger;
	
	srand((unsigned)time(NULL));

	const int N = 10;

	int A[N];
	int num = -100;
	int numMissing = (rand() % (N - 1)) + 1;

	for (int i = 0; i < N; ++i)
	{
		if (i == numMissing)
		{
			num = num + 2;
		}
		else
		{
			++num;
		}

		A[i] = num;
	}

	shuffle(A, N);

	int missingValue = missingInteger.solution(A, N);

	printf("missingValue(%d)", missingValue);

	return EXIT_SUCCESS;
}
