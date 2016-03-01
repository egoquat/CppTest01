#include <vector>

class MaxProfit
{
public:
	int solution(vector<int>& A)
	{
		if (A.size() <= 1) return 0;
		if (A.size() == 2) return A[1] - A[0];

		int profitMax = -1 << 31, stockMin = 200000;

		for (unsigned int i = 1; i < A.size(); ++i)
		{
			int stock = A[i - 1];
			if (stock < stockMin)
			{
				stockMin = stock;
			}

			int profit = A[i] - stockMin;
			if (profit > profitMax)
			{
				profitMax = profit;
			}
		}

		return max(profitMax, 0);
	}
};