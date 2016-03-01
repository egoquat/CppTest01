
#include <math.h>

class MinPerimeterRectangle
{
public:
	int solution(int N)
	{
		int minP = (1 << 30) - 1 + (1 << 30);
		int s = sqrt(N);

		for (int i = 1; i <= s; ++i)
		{
			if (N % i == 0)
			{
				int divisor = (N / i);
				int p = 2 * (i + divisor);
				if (p < minP)
				{
					minP = p;
				}
			}
		}

		return minP;
	}
};
