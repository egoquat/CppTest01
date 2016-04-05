#include <vector>

class Peaks
{
public:
	typedef unsigned int uint;

	int solution(vector<int> &A)
	{
		if (A.size() <= 2) return 0;
		int cntPeaks = 0;

		vector<uint> peaks;
		for (uint i = 1; i < A.size() - 1; ++i)
		{
			if (A[i - 1] < A[i] && A[i] > A[i + 1])
			{
				peaks.push_back(i);

			}
		}

		if (peaks.size() <= 0) return 0;
		uint s = A.size();

		for (uint i = 1; i < s; ++i)
		{
			if (s % i != 0) continue;
			uint dv = A.size() / i;

			uint cnt = 0;
			for (uint j = 0; j < peaks.size(); ++j)
			{
				int p = peaks[j];

				if ((cnt * i) * dv < p && p < ((cnt + 1) * i) * dv)
				{
					cnt++;
				}
			}
		}

		return cntPeaks;
	}
};

