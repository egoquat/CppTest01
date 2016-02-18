#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int TRUE = 1, FALSE = 0;

class NumberOfDiscIntersections
{
public:

	typedef struct
	{
		long long b;
		int isStart;

		void Set(long long b_, int isStart_)
		{
			b = b_;
			isStart = isStart_;
		}
	}Bound;

	static int Compare(const void* a, const void* b)
	{
		Bound* b1 = (Bound*)a;
		Bound* b2 = (Bound*)b;

		if (b1->b == b2->b)
		{
			if (b1->isStart == b2->isStart)
			{
				return 0;
			}
			else if (TRUE == b1->isStart)
			{
				return -1;
			}

			return 1;
		}
		else
		{
			return (b1->b - b2->b > 0)?1:-1;
		}
	}

	int solution(int A[], int N)
	{
		if (N < 2) return FALSE;

		Bound* bounds = (Bound*)malloc(sizeof(Bound) * N * 2);
		int seq = 0;
		for (int i = 0; i < N; ++i)
		{
			bounds[seq++].Set((long long)i - (long long)A[i], TRUE);
			bounds[seq++].Set((long long)i + (long long)A[i], FALSE);
		}

		qsort(bounds, N * 2, sizeof(Bound), Compare);

		int cntIntersect = 0, cnt = 0;
		for (int i = 0; i < N * 2; ++i)
		{
			Bound b = bounds[i];

			if (TRUE == b.isStart)
			{
				cnt++;
			}
			else
			{
				cnt--;
				cntIntersect += cnt;
			}
		}

		free(bounds);

		return cntIntersect;
	}
};