#include <map>
#include <list>
#include <vector>

using namespace std;
class GenomicRangeQuery
{
private:

public:
	vector<int> solution(string &S, vector<int> &P, vector<int> &Q)
	{
		map<char, int> genomToInt;
		genomToInt['A'] = 1;
		genomToInt['C'] = 2;
		genomToInt['G'] = 3;
		genomToInt['T'] = 4;
		map<int, char> intToGenom;
		genomToInt[1] = 'A';
		genomToInt[2] = 'C';
		genomToInt[3] = 'G';
		genomToInt[4] = 'T';

		list<int> sequences;
		vector<int> counting;
		counting.reserve(P.size());

		for (int i = 0; i < P.size(); ++i)
		{
			int from = P[i];
			int to = Q[i];

			sequences.clear();
			for (int j = from; j <= to; ++j)
			{
				sequences.push_back(genomToInt[S[j]]);
			}

			sequences.sort();
			counting.push_back(sequences.front());
		}

		return counting;
	}
};
