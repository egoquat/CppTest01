#include <string.h>
#include <stdlib.h>

class MaxCounters
{
public:
	struct Results
	{
		int* C;
		int L;
	};

public:
	struct Results solution(int N, int A[], int M) {
		struct Results result;
		result.C = (int*)malloc(sizeof(int) * N);
		result.L = N;

		memset(result.C, 0, sizeof(int) * N);
		
		int maxCount = 0, count = 0, idx = 0, maxCountToSet = 0;
		for (int i = 0; i < M; ++i)
		{
			int number = A[i];

			if (number > N + 1 || number < 1)
			{
				continue;
			}

			if (N >= number)
			{
				count = ++(result.C[number - 1]);
				if (count > maxCount)
				{
					maxCount = count;
				}
			}
			else
			{
				maxCountToSet = maxCount;
			}
		}

		for (int i = 0; i < N; ++i)
		{
			int count = result.C[i];
			result.C[i] = (count < maxCountToSet)?maxCountToSet:count;
		}

		return result;
	}
};

