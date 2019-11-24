
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
#define NONE -1
#define MAXTRY 1000000

class River
{
	int _numStart;
	int _numCurr;
	int _numSeq;

public:
	int NumCurr() { return _numCurr; }
	int NumSeq() { return _numSeq; }
	int NumNext()
	{
		if (0 == _numCurr)
			return 0;

		if (1 == _numCurr)
			return 2;

		//cerr << "NumNext Start:" << _numCurr << "Seq:" << _numSeq << endl;

		int numIter = _numCurr;
		int numSum = 0;
		while (numIter > 0)
		{
			numSum = numSum + (numIter % 10);
			numIter = numIter / 10;
		}

		//cerr << "numSum:" << numSum << endl;

		_numCurr = _numCurr + numSum;
		_numSeq++;
		return _numCurr;
	}

	void NumNextToTarget(int numTarget)
	{
		if (_numCurr >= numTarget)
			return;

		while (_numCurr < numTarget)
		{
			NumNext();
		}
	}

	void Init(int num)
	{
		_numStart = num;
		_numSeq = 1;
		_numCurr = num;
	}
};

class R
{
public:
	static River R1;
	static River R2;

	static int FindMeet(int r1, int r2)
	{
		cerr << "r1:" << r1 << "/r2:" << r2 << endl;

		R1.Init(r1); R2.Init(r2);

		while (R1.NumCurr() != R2.NumCurr())
		{
			River* r1 = nullptr;
			River* r2 = nullptr;

			if (R1.NumCurr() > R2.NumCurr())
			{
				r1 = &R2; r2 = &R1;
			}
			else
			{
				r1 = &R1; r2 = &R2;
			}
			r1->NumNextToTarget(r2->NumCurr());
		}

		//return R1.NumSeq();
		return R1.NumCurr();
	}
};

River R::R1; River R::R2;

int main()
{
	long long r1;
	cin >> r1; cin.ignore();
	long long r2;
	cin >> r2; cin.ignore();

	int numMet = R::FindMeet((int)r1, (int)r2);
	cerr << "MetNum:" << numMet << endl;

	// Write an action using cout. DON'T FORGET THE "<< endl"
	// To debug: cerr << "Debug messages..." << endl;

	cout << numMet << endl;
}
