#pragma once
#include <vector>
#include <algorithm>

using namespace::std;


class KiwiJuice
{
public:
	vector<int> thePouring_NonOptimize(vector<int> capacities, vector<int> bottles, vector<int> fromId, vector<int> toId);
	vector<int> thePouring_Optimize(vector<int> capacities, vector<int> bottles, vector<int> fromId, vector<int> toId);

public: 
	KiwiJuice();
	~KiwiJuice();
};

