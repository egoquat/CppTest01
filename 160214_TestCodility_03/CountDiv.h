
class CountDiv
{
public:
	int solution(int A, int B, int K)
	{
		int cntDiv = 0;
		if (0 == K)
		{
			return 0;
		}
		
		if (1 == K)
		{
			cntDiv = B - A;
			return cntDiv + 1;
		}
		else
		{
			cntDiv = (B / K) - ((A - 1) / K);
			if (0 == A)
			{
				++cntDiv;
			}
			return cntDiv;
		}
	}
};
