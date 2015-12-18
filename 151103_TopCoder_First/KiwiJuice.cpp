#include "KiwiJuice.h"

vector<int> KiwiJuice::thePouring_NonOptimize(vector<int> capacities, vector<int> bottles, vector<int> fromId, vector<int> toId)
{
	for (int i = 0; fromId.size(); ++i)
	{
		int f = fromId[i];
		int t = toId[i];
		int space = capacities[t] - bottles[t];

		if (space >= bottles[f])
		{
			int vol = bottles[f];
			bottles[f] += vol;
			bottles[f] = 0;
		}
		else
		{
			int vol = space;
			bottles[t] += vol;
			bottles[f] -= vol;
		}
	}

	return bottles;
}

vector<int> KiwiJuice::thePouring_Optimize(vector<int> capacities, vector<int> bottles, vector<int> fromId, vector<int> toId)
{
	for (int i = 0; fromId.size(); ++i)
	{
		int sum = bottles[toId[i]] + capacities[fromId[i]];
		bottles[toId[i]] = min(sum, capacities[fromId[i]]);
		bottles[fromId[i]] = sum - bottles[toId[i]];
	}

	return bottles;
}

KiwiJuice::KiwiJuice()
{
}


KiwiJuice::~KiwiJuice()
{
}
