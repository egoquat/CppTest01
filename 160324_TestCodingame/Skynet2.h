// https://www.codingame.com/ide/puzzle/skynet-revolution-episode-2 test.

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

#define NULL_NODE -1
#define MAX_UINT 0xffffffff

using namespace std;

typedef unsigned int uint;

class Node
{
private:
	template<typename T>
	static bool Remove(vector<T>& v, const T r)
	{
		if (v.size() <= 0) return false;
		bool isFound = false;
		typedef typename vector<T>::iterator iter_v;
		iter_v iter = v.begin();
		for (; iter != v.end(); ++iter)
		{
			if (r == *iter) { isFound = true; break; }
		}
		if (true == isFound) { v.erase(iter); }
		return isFound;
	}

	template<typename T>
	static bool AddNotOverlap(vector<T>& v, const T t)
	{
		typedef typename vector<T>::iterator iter_v;

		iter_v iter = std::find(v.begin(), v.end(), t);
		if (v.end() == iter)
		{
			v.push_back(t);
			return true;
		}

		return false;
	}

	template<typename T>
	static bool Contains(vector<T>& v, const T t)
	{
		typedef typename vector<T>::iterator iter_v;

		iter_v iter = std::find(v.begin(), v.end(), t);
		return iter != v.end();
	}

	static Node* Root;
	static vector<int> Goals;
	static vector<int> NodesHasMultiGoal;
	static vector<Node*> Nodes;
	static uint CntNode;
	static int CntTest;

	uint _distanceToGoal = MAX_UINT;
	vector<int> _adjs;
	vector<int> _adjsGoal;

public:
	int _idx = NULL_NODE;
	int _nodeToGoal = NULL_NODE;
	bool _isGoal = false;
	bool _isActive = true;

private:
	static Node* GetNode(int node)
	{
		return Nodes[node];
	}

public:
	static void Init(const int N)
	{
		Nodes.reserve(N);

		for (int i = 0; i < N; ++i)
		{
			Nodes.push_back(new Node(i));
		}
	}

	static void ClearAll()
	{
		if (0 == CntNode) return;

		for (uint i = 0; i < CntNode; ++i)
		{
			Node* n = Nodes[i];
			delete n;
		}

		Nodes.clear();
		Goals.clear();
	}

	static void AddLink(const int nodeA, const int nodeB)
	{
		Node* N = GetNode(nodeA);
		N->AddAdj(nodeB);

		N = GetNode(nodeB);
		N->AddAdj(nodeA);
	}

	static void RemoveLink(const int nodeA, const int nodeB)
	{
		Node* N = GetNode(nodeA);
		N->RemoveAdj(nodeB);
		N = GetNode(nodeB);
		N->RemoveAdj(nodeA);

		//for (uint i = 0; i < CntNode; ++i)
		//	Nodes[i]->Reset();

		//for (uint i = 0; i < Goals.size(); ++i)
		//	GetNode(Goals[i])->MapDist();

		SetMapToGoal();
	}

	static void SetAsGoal(int g)
	{
		Node* goal = GetNode(g);
		goal->SetGoal();
		goal->MapDist();
	}

	static void SetMapToGoal()
	{
		NodesHasMultiGoal.clear();
		for (uint i = 0; i < Goals.size(); ++i)
		{
			GetNode(Goals[i])->MapFromGoal();
		}

		for (uint i = 0; i < CntNode; ++i)
		{
			Node* n = Nodes[i];

			if (n->_adjsGoal.size() >= 2)
			{
				AddNotOverlap(NodesHasMultiGoal, n->_idx);
			}
		}
	}

	struct Dist
	{
		Node* _node;
		int _dist;
		int _cntAdjGoal;
		Dist(Node* node, int dist, int cntAdjGoal)
		{
			_node = node; _dist = dist; _cntAdjGoal = cntAdjGoal;
		}
	};

	static bool CompareDegree(Dist& a, Dist& b)
	{
		if (a._cntAdjGoal == NULL_NODE && b._cntAdjGoal == NULL_NODE)
		{
			return a._dist < b._dist;
		}
		else
		{
			//return a._cntAdjGoal < b._cntAdjGoal;
			return (a._dist - a._cntAdjGoal) < (b._dist - b._cntAdjGoal);
		}

	}

	static void GetWayToGoal(int nodeAgent, vector<int>& wayToGoal_out)
	{
		vector<int> wayToGoal;
		Node* agent = GetNode(nodeAgent);
		wayToGoal.push_back(agent->_idx);

		while (agent->_isGoal == false)
		{
			agent = GetNode(agent->_nodeToGoal);
			wayToGoal.push_back(agent->_idx);
		}

		if (3 == wayToGoal.size() && 1 <= NodesHasMultiGoal.size())
		{
			vector<Dist> dists;
			for (int i = 0; i < NodesHasMultiGoal.size(); ++i)
			{
				int cntAdjGoal = 0;
				Node* nodeTarget = GetNode(NodesHasMultiGoal[i]);
				int dist = GetDistAgent(agent, nodeTarget, cntAdjGoal);
				//cerr << ">>>>> add dist:" << dist << "/" << "/nodeAgent:" << nodeAgent << "/target:" << nodeTarget->_idx << "/cntAdjGoal:" << cntAdjGoal << endl;
				dists.push_back(Dist(nodeTarget, dist, cntAdjGoal));
			}

			Node* resolve = GetNode(NodesHasMultiGoal[0]);
			if (dists.size() >= 2)
			{
				std::sort(dists.begin(), dists.end(), CompareDegree);
				//for (int i = 0; i < dists.size(); ++i)
				//{
				//	cerr << ">>>>> i:" << i << "/dist:" << dists[i]._dist << "/idx:" << dists[i]._node->_idx << "/cntAdjGoal:" << dists[i]._cntAdjGoal << endl;
				//}
				resolve = dists[0]._node;
			}

			Node* check = GetNode(wayToGoal[1]);
			if (1 >= check->_adjsGoal.size())
			{
				AddNotOverlap(wayToGoal_out, resolve->_idx);
				AddNotOverlap(wayToGoal_out, resolve->_adjsGoal[0]);
				//cerr << ">>>>>>> MultiGoal resolve : " << resolve->_idx << "/" << resolve->_adjsGoal[0] << endl;
				return;
			}
		}

		wayToGoal_out = wayToGoal;
		//cerr << ">> Way To Goal" << endl;
	}

	static int GetNextWayToGoal(int nodeStart)
	{
		return GetNode(nodeStart)->_nodeToGoal;
	}

	static int GetDistAgent(Node* agent, Node* to, int& cntAdjGoal_out)
	{
		int dist = 0, distReturn = NULL_NODE;
		vector<Node*> path; vector<Node*> pathResult;
		GetDistAgentRecurse(agent, to, dist, path, distReturn, pathResult);
		int cntAdjGoal = 0;
		if (pathResult.size() >= 1)
		{
			for (int i = 0; i < pathResult.size(); ++i)
			{
				Node* iter = pathResult[i];
				if (iter->IsAdjsGoalAny() == true) { cntAdjGoal++; }
			}

			cntAdjGoal_out = cntAdjGoal;
		}

		return pathResult.size();
	}

	static void GetDistAgentRecurse(Node* from, Node* find, int dist, vector<Node*> path, int& dist_out, vector<Node*>& path_out)
	{
		dist++;

		vector<Node*> pathUse = path;
		pathUse.push_back(from);

		CntTest++;
		//cerr << ">> call GetDistAgentRecurse :" << CntTest << endl;

		for (int i = 0; i < from->_adjs.size(); ++i)
		{
			Node* iter = GetNode(from->_adjs[i]);
			if (iter->_isActive == false || true == Contains(pathUse, iter) || true == iter->_isGoal)
				continue;

			if (iter == find && (dist_out == NULL_NODE || (dist_out != NULL_NODE && dist_out > dist)))
			{
				dist_out = dist;
				pathUse.push_back(iter);
				path_out = pathUse;
				//cerr << ">> found : " << find->_idx << "/dist_out:" << dist << "/count:" << pathUse.size() << endl;
				return;
			}

			GetDistAgentRecurse(iter, find, dist, pathUse, dist_out, path_out);
		}
	}

public:
	bool IsAdjsGoalAny() { return _adjsGoal.size() >= 1; }

	int GetCntGoalAdj()
	{
		int countGoal = 0;
		for (int i = 0; i < _adjs.size(); ++i)
		{
			Node* adj = Nodes[_adjs[i]];
			countGoal = countGoal + (true == adj->_isGoal ? 1 : 0);
		}
		return 2 <= countGoal;
	}

	bool AddAdjGoal(int idxGoal)
	{
		if (_isGoal) return false;
		AddNotOverlap(_adjsGoal, idxGoal);
		//if (_adjsGoal.size() >= 2)
		//{
		//	cerr << ">>> Has MultiGoal : " << _idx << "/Count:" << _adjsGoal.size() << endl;
		//}
		return true;
	}

	void SetGoal()
	{
		_isGoal = true;
		_distanceToGoal = 0;
		AddNotOverlap(Goals, _idx);
	}

	void Reset()
	{
		_nodeToGoal = NULL_NODE;

		if (true == _isGoal)
		{
			_distanceToGoal = 0;
		}
		else
		{
			_distanceToGoal = MAX_UINT;
		}
	}

private:
	void MapDist()
	{
		static uint counting = 0;
		MapDistRecurse(_idx, 0, counting);
	}

	void MapDistRecurse(const int from, const uint distance, uint& counting)
	{
		if (distance > _distanceToGoal)
		{
			return;
		}

		uint D = distance;

		if (D < _distanceToGoal)
		{
			_distanceToGoal = D;
			//cerr << " " << _idx << " D:" << _distanceToGoal << endl;
		}

		D = D + 1;
		counting = counting + 1;

		for (uint i = 0; i < _adjs.size(); ++i)
		{
			if (_adjs[i] == from) continue;
			GetNode(_adjs[i])->MapDistRecurse(_idx, D, counting);
		}
	}

	void MapFromGoal()
	{
		if (false == _isGoal) return;

		static uint counting = 0;
		MapFromGoalRecurse(_idx, _distanceToGoal, counting);

		for (int i = 0; i < _adjs.size(); ++i)
		{
			Node* adj = GetNode(_adjs[i]);
			bool isAdded = adj->AddAdjGoal(_idx);
		}
	}

	void MapFromGoalRecurse(const int from, const uint distance, uint& counting)
	{
		if (distance > _distanceToGoal) return;

		_nodeToGoal = from;

		uint dist = distance;
		dist = dist + 1;
		counting = counting + 1;

		for (uint i = 0; i < _adjs.size(); ++i)
		{
			Node* adj = GetNode(_adjs[i]);
			if (adj->_isActive == false) continue;

			if (false == adj->_isGoal)
			{
				adj->MapFromGoalRecurse(_idx, dist, counting);
			}
		}
	}

	void AddAdj(const int a)
	{
		AddNotOverlap(_adjs, a);
	}

	void RemoveAdj(const int a)
	{
		Remove(_adjs, a); Remove(_adjsGoal, a);
	}

	Node(int node)
	{
		_idx = node;
		CntNode++;
	}

	~Node()
	{
		CntNode--;
	}
};

Node* Node::Root = nullptr;
vector<Node*> Node::Nodes;
vector<int> Node::Goals;
vector<int> Node::NodesHasMultiGoal;
uint Node::CntNode = 0;
int Node::CntTest = 0;

int main()
{
	int N; // the total number of nodes in the level, including the gateways
	int L; // the number of links
	int E; // the number of exit gateways
	cin >> N >> L >> E; cin.ignore();

	Node::Init(N);

	cerr << std::to_string(N) << " " << std::to_string(L) << " " << std::to_string(E) << endl;

	for (int i = 0; i < L; i++) {
		int N1; // N1 and N2 defines a link between these nodes
		int N2;
		cin >> N1 >> N2; cin.ignore();

		Node::AddLink(N1, N2);
	}

	for (int i = 0; i < E; i++) {
		int EI; // the index of a gateway node
		cin >> EI; cin.ignore();
		Node::SetAsGoal(EI);
	}

	Node::SetMapToGoal();

	vector<int> wayToGoal;

	// game loop
	while (1)
	{
		int SI;
		cin >> SI; cin.ignore();

		wayToGoal.clear();
		Node::GetWayToGoal(SI, wayToGoal);
		if (wayToGoal.size() >= 2)
		{
			int parent = wayToGoal[wayToGoal.size() - 2];
			int child = wayToGoal[wayToGoal.size() - 1];

			//cerr << "wayToGoal: " << parent << " " << child << endl;
			cout << parent << " " << child << endl;

			Node::RemoveLink(parent, child);
		}
	}

	Node::ClearAll();
}