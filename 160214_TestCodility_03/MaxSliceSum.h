#include <vector>

class MaxSliceSum
{
public:
	int solution(vector<int> &A)
	{
		if (A.size() < 0) return 0;
		if (A.size() == 1) return A[0];

		int maxSum = A[0], maxScope = A[0];
		for (unsigned int i = 1; i < A.size(); ++i)
		{
			maxScope = max(A[i], maxScope + A[i]);
			maxSum = max(maxSum, maxScope);
		}

		return maxSum;
	}
};
