#include <stdio.h>
#include <vector>

class MinAvgTwoSlice
{
public:
	int solution(int A[], int N)
	{
		int idxMin = 0, sum = 0;
		float avrMin = 1e6f, avr = 0.f;
		for (int i = 1; i < N; ++i)
		{
			sum = 0;
			for (int j = 0; j <= i; ++j)
			{
				sum = sum + A[i - j];
				if (j > 0)
				{
					avr = (float)sum / ((float)j + 1.0f);
					if (avr < avrMin)
					{
						avrMin = avr;
						idxMin = i - j;
					}
				}
			}
		}

		char* output = new char[1024];
		int ibuff = 0;
		
		for (int i = 0; i < N; ++i)
		{
			ibuff += sprintf_s(output + ibuff, 1024 - ibuff, "%d,", A[i]);
		}

		ibuff += sprintf_s(output + ibuff, 1024 - ibuff, "//%d\n", idxMin);

		printf(output);

		return idxMin;
	}
};
