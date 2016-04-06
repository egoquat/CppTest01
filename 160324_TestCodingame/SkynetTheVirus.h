#include <stdlib.h>
#include <vector>

using namespace std;

class SkynetTheVirus
{
	typedef unsigned int uint;
	
	class Tree
	{
		const static int NULL_NODE = -1;
		const static uint MAX_UINT = 0xffffffff;

		static Tree* _root;
		static vector<int> _goals;
		static Tree** _nodes;
		static int _count;

	private:

		vector<int> _adjacents;

		int _nodeToGoal = NULL_NODE;
		uint _distanceToGoal = MAX_UINT;
		int _node = NULL_NODE;
		bool _isGoal = false;

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
				if (r == *iter)
				{
					isFound = true;
					break;
				}
			}

			if (true == isFound)
			{
				v.erase(iter);
			}
			return isFound;
		}

		template<typename T>
		static bool AddNotOverlap(vector<T> &v, const T t)
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

	private:

		static Tree* GetNode(int node)
		{
			return _nodes[node];
		}

	public:

		static void Init(const int N)
		{
			_nodes = new Tree*[N];
			
			for (int i = 0; i < N; ++i)
			{
				_nodes[i] = new Tree(i);
			}
		}

		static void ClearAll()
		{
			if (0 == _count) return;

			for (int i = 0; i < _count; ++i)
			{
				Tree* n = _nodes[i];
				delete n;
			}

			delete[] _nodes;
			_nodes = nullptr;

			_goals.clear();
		}

		static void AddLink(const int nodeA, const int nodeB)
		{
			Tree* N = GetNode(nodeA);
			N->AddAdjacent(nodeB);

			N = GetNode(nodeB);
			N->AddAdjacent(nodeA);
		}

		static void RemoveLink(const int nodeA, const int nodeB)
		{
			Tree* N = GetNode(nodeA);
			N->RemoveAdjacent(nodeB);

			N = GetNode(nodeB);
			N->RemoveAdjacent(nodeA);

			for (int i = 0; i < _count; ++i)
			{
				_nodes[i]->ClearToGoal();
			}

			for (uint i = 0; i < _goals.size(); ++i)
			{
				GetNode(_goals[i])->MappingPath();
			}
		}

		static void SetAsGoal(int g)
		{			
			Tree* goal = GetNode(g);
			goal->SetGoal();
			goal->MappingPath();
		}

		static void GetWayToGoal(int nodeStart, vector<int>& wayToGoal)
		{
			Tree* N = GetNode(nodeStart);
			wayToGoal.push_back(N->GetNodeIdx());

			while (N->IsGoal() == false)
			{
				N = GetNode(N->GetNodeToGoal());
				wayToGoal.push_back(N->GetNodeIdx());
			}
		}

		static int GetNextWayToGoal(int nodeStart)
		{
			return GetNode(nodeStart)->GetNodeToGoal();
		}

	public:
			bool IsGoal()
			{
				return _isGoal;
			}

			void SetGoal()
			{
				_isGoal = true;
				AddNotOverlap(_goals, _node);
			}

			int GetNodeIdx()
			{
				return _node;
			}

			int GetNodeToGoal()
			{
				return _nodeToGoal;
			}

			const vector<int> GetAdjacents()
			{
				return _adjacents;
			}

			void SetToGoal(const int nodeTo, const uint distance)
			{
				if (distance < _distanceToGoal)
				{
					_nodeToGoal = nodeTo;
					_distanceToGoal = distance;
				}
			}

			void ClearToGoal()
			{
				_nodeToGoal = NULL_NODE;
				_distanceToGoal = MAX_UINT;
			}

	private:

		void MappingPath()
		{
			static uint counting = 0;
			MappingPathR(_node, 0, counting);
		}

		void MappingPathR(const int from, const uint distance, uint& counting)
		{
			if (distance > _distanceToGoal )
			{
				return;
			}

			uint D = distance;

			SetToGoal(from, D++);
			counting++;

			for (uint i = 0; i < _adjacents.size(); ++i)
			{
				GetNode(_adjacents[i])->MappingPathR(_node, D, counting);
			}
		}

		void AddAdjacent(const int a)
		{
			AddNotOverlap(_adjacents, a);
		}

		void RemoveAdjacent(const int a)
		{
			Remove(_adjacents, a);
		}

		Tree(int node)
		{
			_node = node;
			_count++;
		}

		~Tree()
		{
			_count--;
		}
	};

	public:
	int main()
	{
		int N = 12; // the total number of nodes in the level, including the gateways
		int L = 23; // the number of links
		int E = 1; // the number of exit gateways
		//cin >> N >> L >> E; cin.ignore();

		Tree::Init(N);

		int A = 2;

		int Links[] = { 11, 6, 0, 9, 1, 2, 0, 1, 
						10, 1, 11, 5, 2, 3, 4, 5, 
						8, 9, 6, 7, 7, 8, 0, 6,
						3, 4, 0, 2, 11, 7, 0, 8, 
						0, 4, 9, 10, 0, 5, 0, 7, 
						0, 3, 0, 10, 5, 6 };

		int Gateways[] = { 0 };

		for (int i = 0; i < L; i++) {
			int N1 = Links[(i * 2)]; // N1 and N2 defines a link between these nodes
			int N2 = Links[(i * 2) + 1];
			//cin >> N1 >> N2; cin.ignore();

			Tree::AddLink(N1, N2);
		}

		for (int i = 0; i < E; i++) {
			int EI = Gateways[i]; // the index of a gateway node
			//cin >> EI; cin.ignore();

			Tree::SetAsGoal(EI);
		}

		vector<int> wayToGoal;

		int loop = 0;
		int SI = 11;
		// game loop
		while (1) {
			//cin >> SI; cin.ignore();// The index of the node on which the Skynet agent is positioned this turn

			// Write an action using cout. DON'T FORGET THE "<< endl"
			// To debug: cerr << "Debug messages..." << endl;

			if (-1 == SI)
			{
				break;
			}

			wayToGoal.clear();
			Tree::GetWayToGoal(SI, wayToGoal);

			if (wayToGoal.size() >= 2)
			{
				//int parent = wayToGoal[wayToGoal.size() - 2];
				//int child = wayToGoal[wayToGoal.size() - 1];

				int parent = wayToGoal[0];
				int child = wayToGoal[1];

				//cout << "0 1" << endl; // Example: 0 1 are the indices of the nodes you wish to sever the link between

				Tree::RemoveLink(parent, child);
			}

			SI = Tree::GetNextWayToGoal(SI);
		}

		Tree::ClearAll();

		return EXIT_SUCCESS;
	}
};

int SkynetTheVirus::Tree::_count = 0;
SkynetTheVirus::Tree* SkynetTheVirus::Tree::_root = nullptr;
SkynetTheVirus::Tree** SkynetTheVirus::Tree::_nodes = nullptr;
vector<int> SkynetTheVirus::Tree::_goals;

