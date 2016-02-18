#include <stdlib.h>

using namespace std;

class MissingInteger
{
private:
	static int compare(const void* a, const void* b)
	{
		return (*(int*)a - *(int*)b);
	}

public:

	int solution(int A[], int N) {
		if (1 == N)
		{
			return A[0] + 1;
		}

		const int TRUE = 1;
		const int FALSE = 0;
		int isFoundMissing = FALSE;

		qsort(A, N, sizeof(int), compare);

		int missingValue = 0;
		int first = 0, second = 0, gab = 0;

		for (int i = 1; i < N; ++i)
		{
			first = A[i - 1];
			second = A[i];

			gab = second - first;

			if (0 == gab)
			{
				continue;
			}

			if (1 != gab)
			{
				if (1 == i)
				{
					if (2 < N && A[i + 1] - 1 == second)
					{
						missingValue = second - 1;
						isFoundMissing = TRUE;
					}
					else
					{
						missingValue = first + 1;
						isFoundMissing = TRUE;
					}
				}
				else
				{
					missingValue = first + 1;
					isFoundMissing = TRUE;
				}
			}

			if (TRUE == isFoundMissing)
			{
				break;
			}
		}

		return missingValue;
	}
};
