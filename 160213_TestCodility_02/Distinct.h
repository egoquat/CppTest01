#include <stdlib.h>

class Distinct
{
	static int compare(const void * a, const void * b)
	{
		return (*(int*)a - *(int*)b);
	}

public:
	int solution(int A[], int N)
	{
		if (0 >= N)
		{
			return 0;
		}

		if (1 == N)
		{
			return A[0];
		}

		qsort(A, N, sizeof(int), compare);

		const int TRUE = 1;
		const int FALSE = 0;

		int seq = 0, value = 0, valueDistinct = 0;
		int isFound = FALSE, isFinished = FALSE;
		for (int i = 0; i < N; ++i)
		{
			value = A[i];
			for (int j = i; j < N; ++j)
			{
				if (A[j] != value)
				{
					if (j - i <= 1)
					{
						valueDistinct = A[i];
						isFound = TRUE;
						break;
					}
					else
					{
						seq = j - 1;
						break;
					}
				}

				if (j >= (N - 1))
				{
					if (j == i)
					{
						isFound = TRUE;
						valueDistinct = A[i];
					}

					isFinished = TRUE;
					break;
				}
			}

			if (TRUE == isFound || TRUE == isFinished)
			{
				break;
			}

			i = seq;
		}

		return valueDistinct;
	}
};
