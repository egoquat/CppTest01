#pragma once

#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

typedef unsigned int uint;

class TheParanoidAndroid
{
public:

	const static int NULL_ = -1;
	const static uint MAX_UINT = 0xffffffff;
	class Path
	{
	private:
		template<typename T>
		static void AddNotOverlap(vector<T> V, T value)
		{
			typedef typename vector<T>::iterator iter_v;
			bool isFound = false;
			iter_v iter = V.begin();
			for (; iter != V.end(); ++iter)
			{
				if (*iter == value) { return; }
			}

			V.push_back(value);
		}

	private:
		static Path** _nodes;
		static uint _idxGoal;
		static int _width;
		static int _floor;
		static int _count;

	private:
		vector<uint> _adjacents;
		uint _idx = 0;
		uint _idxToGoal = 0;
		uint _costToGoal = MAX_UINT;
		bool _isBlock = false;
		bool _isGoal = false;

	public:
		int GetX() { return (_idx % _floor); }
		int GetY() { return (_idx / _width); }
		void AddAdjacent(const uint idxAdj)
		{
			if (idxAdj == _idx)
			{
				return;
			}

			AddNotOverlap(_adjacents, idxAdj);
		}

		void SetGoal()
		{
			_isGoal = true;
			_costToGoal = 0;
		}

		void SetBlock()
		{
			if (false == _isBlock)
			{
				Reset();
				_isBlock = true;

				Get(_idxGoal)->MappingPathFind();
			}
		}

	public:
		static Path* Get(unsigned int idx)
		{
			return _nodes[idx];
		}

		static void Init(	const int nbFloors,
							const int width,
							const int* elevators,
							const uint cntElevator,
							const int goalFloor,
							const int goalPos)
		{
			_count = width * nbFloors;
			_width = width;
			_floor = nbFloors;

			_nodes = new Path*[_count];
			int seqFloor = 0;

			for (int i = 0; i < _count; ++i)
			{
				_nodes[i] = new Path(i);

				if (0 != seqFloor)
				{
					_nodes[i]->AddAdjacent(i - 1);
				}

				if (0 < _floor - (seqFloor + 1))
				{
					_nodes[i]->AddAdjacent(i + 1);
				}

				if (0 == _count % _floor)
				{
					seqFloor = 0;
				}
				else
				{
					seqFloor++;
				}
			}

			for (uint i = 0; i < cntElevator; i = i + 2)
			{
				uint idx = (elevators[i] * _width) + elevators[i + 1];
				if (idx + _width < _count)
				{
					_nodes[idx + _width]->AddAdjacent(idx);
					_nodes[idx]->AddAdjacent(idx + _width);
				}
			}

			_idxGoal = (goalFloor * _width) + goalPos;
			Path* goal = Get(_idxGoal);
			goal->SetGoal();
			goal->MappingPathFind();
		}

		static void Reset()
		{
			for (int i = 0; i < _count; ++i)
			{
				_nodes[i]->ResetPath();
			}
		}

		static void Clear()
		{
			if (_count <= 0) return;

			for (int i = 0; i < _count; ++i)
			{
				delete _nodes[i];
			}

			delete[] _nodes;
			_nodes = nullptr;
			_count = NULL_;
		}

	private:
		void ResetPath()
		{
			_costToGoal = MAX_UINT;
		}

		void MappingPathFind()
		{
			static uint counting = 0;
			MappingPathFindR(NULL_, 0, counting);
		}

		void MappingPathFindR(const uint idxFrom, const uint distance, uint& counting)
		{
			if (true == _isBlock)
			{
				return;
			}

			if (_costToGoal <= distance)
			{
				return;
			}
			
			counting++;
			_costToGoal = distance + 1;
			_idxToGoal = idxFrom;

			for (uint i = 0; i < _adjacents.size(); ++i)
			{
				Get(_adjacents[i])->MappingPathFindR(_idx, _costToGoal, counting);
			}
		}

	public:
		Path(uint idx)
		{
			_idx = idx;
		}

		~Path()
		{
			_adjacents.clear();
		}
	};

public:
	int main()
	{
		int nbFloors = 1; // number of floors
		int width = 13; // width of the area
		int nbRounds = 100; // maximum number of rounds
		int exitFloor = 0; // floor on which the exit is found
		int exitPos = 0; // position of the exit on its floor
		int nbTotalClones = 10; // number of generated clones
		int nbAdditionalElevators = 0; // ignore (always zero)
		int nbElevators = 0; // number of elevators
		//cin >> nbFloors >> width >> nbRounds >> goalFloor >> goalPos >> nbTotalClones >> nbAdditionalElevators >> nbElevators; cin.ignore();

		//cerr << "nbFloors:" << nbFloors << "//width:" << width << "//nbRounds:" << nbRounds << "//goalFloor:" << goalFloor << endl;
		//cerr << "goalPos:" << goalPos << "//nbTotalClones:" << nbTotalClones << "//nbElevators:" << nbElevators << endl;

		int* elebators = nullptr;
		if (0 < nbElevators)
		{
			elebators = new int[nbElevators * 2];
		}

		for (int i = 0; i < nbElevators; i++) {
			int elevatorFloor = 0; // floor on which this elevator is found
			int elevatorPos = 0; // position of the elevator on its floor
			//cin >> elevatorFloor >> elevatorPos; cin.ignore();
			elebators[i * 2] = elevatorFloor;
			elebators[i * 2 + 1] = elevatorPos;

			//cerr << "EFloor:" << elevatorFloor << "//EPos:" << elevatorPos << endl;
		}

		Path::Init(width, nbFloors, elebators, nbElevators, exitFloor, exitPos );

		// game loop
		while (1) {
			int cloneFloor; // floor of the leading clone
			int clonePos; // position of the leading clone on its floor
			string direction; // direction of the leading clone: LEFT or RIGHT
			//cin >> cloneFloor >> clonePos >> direction; cin.ignore();

			// Write an action using cout. DON'T FORGET THE "<< endl"
			// To debug: cerr << "Debug messages..." << endl;

			//cout << "WAIT" << endl; // action: WAIT or BLOCK
		}
	}
};

typedef TheParanoidAndroid::Path Path;

Path** Path::_nodes = nullptr;
uint Path::_idxGoal = 0;
int Path::_width = -1;
int Path::_floor = -1;
int Path::_count = -1;

