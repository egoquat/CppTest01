// https://www.codingame.com/ide/puzzle/skynet-revolution-episode-2 test. 

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// First cntRelate.
// Resolve double decision.

typedef unsigned int uint;

class Node
{
	const static int NULL_NODE = -1;
	const static uint MAX_UINT = 0xffffffff;

	static Node* Root;
	static vector<int> Goals;
	static vector<int> NodesHasMultiGoal;
	static vector<Node*> Nodes;
	static uint CntNode;

private:
	int _idx = NULL_NODE;

	uint _distanceToGoal = MAX_UINT;
	uint _weight = 0;
	uint _weightToGoal = 0;
	int _nodeToGoal = NULL_NODE;
	bool _isGoal = false;

	vector<int> _adjs;
	vector<int> _adjsGoal;
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

private:
	static Node* GetNode(int node)
	{
		return Nodes[node];
	}

	static void MappingWeight()
	{
		for (uint i = 0; i < CntNode; ++i)
		{
			Node* N = Nodes[i];

			if (false == N->IsGoal() && 1 == N->GetDistance())
			{
				const vector<int>& Adj01 = N->GetAdjs();
				for (uint a = 0; a < Adj01.size(); ++a)
				{
					Node* NAdj = GetNode(Adj01[a]);

					if (1 >= NAdj->GetDistance())
					{
						N->AdditionWeight();
					}
				}
			}
		}
	}

	static void MappingMulti()
	{
		for (uint i = 0; i < CntNode; ++i)
		{
			Node* n = Nodes[i];
			if (n->_adjsGoal.size() >= 2)
			{
				AddNotOverlap(NodesHasMultiGoal, n->GetIdx());
			}
		}
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

		for (uint i = 0; i < CntNode; ++i)
		{
			Nodes[i]->Reset();
		}

		for (uint i = 0; i < Goals.size(); ++i)
		{
			GetNode(Goals[i])->MappingDist();
		}

		SetMappingToGoal();
	}

	static void SetAsGoal(int g)
	{
		Node* goal = GetNode(g);
		goal->SetGoal();
		goal->MappingDist();
	}

	static void SetMappingToGoal()
	{
		MappingWeight();
		NodesHasMultiGoal.clear();
		for (uint i = 0; i < Goals.size(); ++i)
		{
			GetNode(Goals[i])->MappingToGoal();
		}
		MappingMulti();
	}

	struct Dist
	{
		Node* _node;
		int _dist;
		int _cntRelate;
		Dist(Node* node, int dist, int cntRelate)
		{
			_node = node; _dist = dist; _cntRelate = cntRelate;
		}
	};

	static bool CompareDegree(Dist& a, Dist& b)
	{
		//@TEST 01
		//if (a._cntRelate == b._cntRelate)
		//{
		//	return a._dist < b._dist;
		//}

		//return a._cntRelate > b._cntRelate;

		//@TEST 02
		if (a._cntRelate == NULL_NODE && b._cntRelate == NULL_NODE)
		{
			//return a._dist > b._dist;
			return a._dist < b._dist;
		}
		else
		{
			return a._cntRelate > b._cntRelate;
		}
	}

	static void GetWayToGoal(int nodeStart, vector<int>& wayToGoal_out)
	{
		vector<int> wayToGoal;
		Node* N = GetNode(nodeStart);
		wayToGoal.push_back(N->GetIdx());

		while (N->IsGoal() == false)
		{
			N = GetNode(N->GetNodeToGoal());
			wayToGoal.push_back(N->GetIdx());
		}

		static const bool USE_PREDICT = true;
		bool isResolved = false;
		if (true == USE_PREDICT && 3 == wayToGoal.size() && 1 <= NodesHasMultiGoal.size())
		{
			vector<Dist> dists;
			for (int i = 0; i < NodesHasMultiGoal.size(); ++i)
			{
				int cntRelate = NULL_NODE;
				Node* nodeTarget = GetNode(NodesHasMultiGoal[i]);
				int dist = GetDistByRelate(N, nodeTarget, cntRelate);
				//cerr << ">>>>> add dist :" << i << "/cntRelate" << cntRelate << endl;
				dists.push_back(Dist(nodeTarget, dist, cntRelate));
			}

			Node* resolve = GetNode(NodesHasMultiGoal[0]);
			if (dists.size() >= 2)
			{
				std::sort(dists.begin(), dists.end(), CompareDegree);
				for (int i = 0; i < dists.size(); ++i)
				{
					cerr << ">>>>> dists(" << dists.size() << ")/idx:" << i << "/dist:" << dists[i]._dist << "/cntRelate:" << dists[i]._cntRelate << endl;
				}
				resolve = dists[0]._node;
			}

			Node* check = GetNode(wayToGoal[1]);
			if (1 >= check->_adjsGoal.size())
			{
				AddNotOverlap(wayToGoal_out, resolve->GetIdx());
				AddNotOverlap(wayToGoal_out, resolve->_adjsGoal[0]);
				isResolved = true;
				//cerr << ">>>>>>> MultiGoal resolve : " << resolve->GetIdx() << "/" << resolve->_adjsGoal[0] << endl;
			}
		}

		if (false == isResolved)
		{
			wayToGoal_out = wayToGoal;
			//cerr << ">> Way To Goal" << endl;
		}

		//wayToGoal_out = wayToGoal;
	}

	static int GetNextWayToGoal(int nodeStart)
	{
		return GetNode(nodeStart)->GetNodeToGoal();
	}

	static void GetDistByRelateR(Node* from, Node* find, int dist, vector<Node*> path, int& dist_out, vector<Node*>& path_out)
	{
		if (from->_adjs.size() <= 0 || dist_out != NULL_NODE)
		{
			return;
		}

		dist++;

		vector<Node*> pathUse = path;
		pathUse.push_back(from);

		for (int i = 0; i < from->_adjs.size(); ++i)
		{
			if (dist_out != NULL_NODE)
				return;

			Node* iter = GetNode(from->_adjs[i]);
			if (true == Contains(pathUse, iter) || true == iter->_isGoal)
				continue;

			if (iter == find)
			{
				dist_out = dist;
				pathUse.push_back(iter);
				path_out = pathUse;
				cerr << ">>>>>>>>>> found : " << find->_idx << "/dist_out:" << dist << "/count:" << pathUse.size() << endl;
				//return;
			}

			GetDistByRelateR(iter, find, dist, pathUse, dist_out, path_out);
		}
	}

	static int GetDistByRelate(Node* from, Node* to, int& cntRelate_out)
	{
		int dist = 0, distReturn = NULL_NODE;
		vector<Node*> path; vector<Node*> pathResult;
		GetDistByRelateR(from, to, dist, path, distReturn, pathResult);
		int cntRelate = 0;
		if (pathResult.size() >= 1)
		{
			for (int i = 0; i < pathResult.size(); ++i)
			{
				Node* iter = pathResult[i];
				if (iter->IsAdjsGoalAny() == true) { cntRelate++; }
			}

			cntRelate_out = cntRelate;
		}

		//cerr << ">>>>>>>>>> GetDistByRelate vector:" << pathResult.size() << "/dist:" << dist << "/cntRelate:" << cntRelate << endl;
		//return distReturn;
		return pathResult.size();
	}

public:
	bool IsGoal() { return _isGoal; }
	uint GetDistance() { return _distanceToGoal; }
	bool IsAdjsGoalAny() { return _adjsGoal.size() >= 1; }
	int GetIdx() { return _idx; }
	int GetNodeToGoal() { return _nodeToGoal; }
	const vector<int>& GetAdjs() { return _adjs; }
	uint GetWeightToGoal() { return _weight; }
	void SubstractWeight() { _weight--; }

	int GetCntGoalAdj()
	{
		int countGoal = 0;
		for (int i = 0; i < _adjs.size(); ++i)
		{
			Node* adj = Nodes[_adjs[i]];
			countGoal = countGoal + (true == adj->IsGoal() ? 1 : 0);
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
		_weight = 0;
		_weightToGoal = 0;
		_distanceToGoal = 0;
		AddNotOverlap(Goals, _idx);
	}

	void SetDistance(const uint distance)
	{
		if (distance < _distanceToGoal)
		{
			_distanceToGoal = distance;
		}
	}

	void SetToGoal(const uint weightToGoal, const int node)
	{
		_nodeToGoal = node;
		_weightToGoal = weightToGoal;
	}

	void SetNodeToGoal(const uint distance, const uint weight, const int node)
	{
		if (true == _isGoal)
		{
			return;
		}
		else
		{
			if (NULL_NODE == _nodeToGoal)
			{
				SetToGoal(weight, node);
			}
			else
			{
				if (distance < _distanceToGoal)
				{
					SetToGoal(weight, node);
				}
				else if (distance == _distanceToGoal)
				{
					if (weight >= _weightToGoal)
					{
						SetToGoal(weight, node);
					}
				}
			}
		}
	}

	void AdditionWeight()
	{
		if (true == _isGoal)
			return;

		bool isExist = false;

		for (uint i = 0; i < _adjs.size(); ++i)
		{
			//isExist = Contains(Goals, _adjs[i]);
			isExist = true == Nodes[_adjs[i]]->IsGoal();
			if (true == isExist)
			{
				break;
			}
		}

		if (true == isExist)
		{
			_weight++;
		}
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

		_weight = 0;
		_weightToGoal = 0;
	}

private:
	void MappingDist()
	{
		static uint counting = 0;
		MappingDistR(_idx, 0, counting);
	}

	void MappingToGoal()
	{
		if (false == _isGoal) return;

		static uint counting = 0;
		MappingToGoalR(_idx, _distanceToGoal, _weight, counting);

		for (int i = 0; i < _adjs.size(); ++i)
		{
			Node* adj = GetNode(_adjs[i]);
			bool isAdded = adj->AddAdjGoal(_idx);
		}

		//AddNotOverlap(NodesHasMultiGoal, adj->GetIdx());
	}

	void MappingDistR(const int from, const uint distance, uint& counting)
	{
		if (distance > _distanceToGoal)
		{
			return;
		}

		uint D = distance;

		SetDistance(D);

		D = D + 1;
		counting = counting + 1;

		for (uint i = 0; i < _adjs.size(); ++i)
		{
			GetNode(_adjs[i])->MappingDistR(_idx, D, counting);
		}
	}

	void MappingToGoalR(const int from,
		const uint distance,
		const uint weight,
		uint& counting)
	{
		if (distance > _distanceToGoal)
		{
			return;
		}

		SetNodeToGoal(distance, weight, from);

		uint D = distance;
		D = D + 1;
		counting = counting + 1;

		for (uint i = 0; i < _adjs.size(); ++i)
		{
			Node* A = GetNode(_adjs[i]);

			if (false == A->IsGoal())
			{
				A->MappingToGoalR(_idx, D, _weight, counting);
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
uint Node::CntNode = 0;
Node* Node::Root = nullptr;
vector<Node*> Node::Nodes;
vector<int> Node::Goals;
vector<int> Node::NodesHasMultiGoal;

int main()
{
	int N; // the total number of nodes in the level, including the gateways
	int L; // the number of links
	int E; // the number of exit gateways
	cin >> N >> L >> E; cin.ignore();

	Node::Init(N);

	cerr << std::to_string(N) << " " << std::to_string(L) << " " << std::to_string(E) << endl;

	//string output = "";

	for (int i = 0; i < L; i++) {
		int N1; // N1 and N2 defines a link between these nodes
		int N2;
		cin >> N1 >> N2; cin.ignore();

		//cerr << std::to_string(N1) << " " << std::to_string(N2) << endl;
		//output += std::to_string(N1) + ", " + std::to_string(N2) + ", ";

		Node::AddLink(N1, N2);
	}

	//cerr << "AddLink(" << std::to_string(L) << "): "  << output << endl;
	//output = "";

	for (int i = 0; i < E; i++) {
		int EI; // the index of a gateway node
		cin >> EI; cin.ignore();
		//output += std::to_string(EI) + ", ";
		Node::SetAsGoal(EI);
	}

	Node::SetMappingToGoal();
	//cerr << "SetAsGoal(" << std::to_string(E) << "): " << output << endl;

	vector<int> wayToGoal;

	// game loop
	while (1)
	{
		int SI; // The index of the node on which the Skynet agent is positioned this turn
		cin >> SI; cin.ignore();

		// To debug: cerr << "Debug messages..." << endl;
		//cerr << "SI: " << SI << endl;

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

		//cout << "0 1" << endl; // Example: 0 1 are the indices of the nodes you wish to sever the link between
	}

	Node::ClearAll();
}