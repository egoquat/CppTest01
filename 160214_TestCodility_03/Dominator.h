#include <vector>
#include <map>
#include <algorithm>

class Dominator
{
public:
	/*struct C
	{
		int d;
		unsigned int idx;
		unsigned int cnt;

		C(int d_, unsigned int idx_)
		{
			d = d_;
			idx = idx_;
			cnt = 1;
		}
	};

	int solution(vector<int>& A)
	{
		if (A.size() < 1) return -1;
		if (A.size() == 1) return A[0];
		int idxDominator = -1;

		vector<C> candidates;
		for (unsigned int i = 0; i < A.size(); ++i)
		{
			int curr = A[i];

			bool found = false;
			for (unsigned int j = 0; j < candidates.size(); ++j)
			{
				C& c = candidates[j];
				if (c.d == curr)
				{
					found = true;
					c.cnt++;
				}

				if (c.cnt >(A.size() / 2))
				{
					idxDominator = c.idx;
					break;
				}
			}

			if (false == found)
			{
				candidates.push_back(C(curr, i));
			}
		}

		return idxDominator;
	}*/


	struct C
	{
		unsigned int idx;
		int cnt;

		int Counting(unsigned int idx_)
		{
			idx = idx_;
			++cnt;
			return cnt;
		}
	};

	static bool compare(const C& a, const C& b)
	{
		return a.cnt > b.cnt;
	}

	int solution(vector<int>& A)
	{
		if (A.size() < 1) return -1;
		if (A.size() == 1) return 0;
		int idxDominator = -1;

		map<unsigned int, C> m;
		vector<C> candidates;
		unsigned int cntMax = 0;

		for (unsigned int i = 0; i < A.size(); ++i)
		{
			int curr = A[i];
			unsigned int cntCurr = m[curr].Counting(i);
			if (cntMax < cntCurr) cntMax = cntCurr;
		}

		//@ find dominator.
		if (cntMax > A.size() / 2)
		{
			for (map<unsigned int, C>::iterator iter = m.begin(); iter != m.end(); iter++)
			{
				candidates.push_back(iter->second);
			}
		
			sort(candidates.begin(), candidates.end(), compare);

			idxDominator = candidates[0].idx;
		}

		return idxDominator;
	}
};

