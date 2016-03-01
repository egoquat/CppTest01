#include <vector>
#include <map>
#include <algorithm>

class EquiLeader
{
public:
	struct C
	{
		int value;
		unsigned int cnt;

		int Counting(int value_)
		{
			value = value_;
			++cnt;
			return cnt;
		}

		void Set(C other)
		{
			value = other.value; cnt = other.cnt;
		}
	};

	static int compare(const void* a, const void* b)
	{
		return ((C*)b)->cnt > ((C*)a)->cnt;
	}

	int solution(vector<int>& A)
	{
		int cntEqui = 0;
		if (A.size() <= 1) return cntEqui;

		map<int, C> candidates;
		unsigned int i = 0;
		int curr = 0;

		for (i = 0; i < A.size(); ++i)
		{
			curr = A[i];
			candidates[curr].Counting(curr);
		}

		C* sorting = new C[candidates.size()];

		i = 0;
		for (map<int, C>::iterator iter = candidates.begin(); iter != candidates.end(); ++iter)
		{
			sorting[i++] = iter->second;
		}

		qsort(sorting, candidates.size(), sizeof(C), compare);
		
		C& L = sorting[0];
		if (L.cnt > A.size() / 2)
		{
			unsigned int cntRight = L.cnt;
			unsigned int cntLeft = 0;
			int leader = L.value;

			for (i = 0; i < A.size(); ++i)
			{
				curr = A[i];
				if (curr == leader)
				{
					cntRight--; cntLeft++;
				}

				if (((A.size() - (i + 1)) / 2 < cntRight)
					&& ((i + 1) / 2 < cntLeft))
				{
					cntEqui++;
				}
			}
		}
	
		delete[] sorting;
		candidates.clear();

		return cntEqui;
	}
};