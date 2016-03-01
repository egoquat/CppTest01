#include <vector>
#include <algorithm>

class MaxDoubleSliceSum
{
public:
	int solution(vector<int>& A)
	{
		if (A.size() <= 3) return 0;

		int* firsts = new int[A.size()];
		int* seconds = new int[A.size()];

		memset(firsts, 0, sizeof(int) * A.size());
		memset(seconds, 0, sizeof(int) * A.size());
		int iInv = 0;
		for (unsigned int i = 1; i < A.size() - 1; ++i)
		{		
			firsts[i] = max(firsts[i - 1] + A[i], 0);
			iInv = A.size() - 1 - i;
			seconds[iInv] = max(seconds[iInv + 1] + A[iInv], 0);
		}

		int sumMax = 0;
		for (unsigned int i = 1; i < A.size() - 1; ++i)
		{
			sumMax = max(sumMax, firsts[i - 1] + seconds[i + 1]);
		}

		delete[] firsts;
		delete[] seconds;

		return sumMax;
	}
};
