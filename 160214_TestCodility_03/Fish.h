#include <vector>
#include "Stack.h"

using namespace std;

class Fish
{
public:
	int solution(vector<int> &A, vector<int> &B) 
	{
		if (A.size() <= 1) return A.size();

		Stack<int> Flows;

		int live = 0, curr = 0;
		bool isFlow = false;
		for (unsigned int i = 0; i < A.size(); ++i)
		{
			curr = A[i];
			isFlow = (B[i] == 1);

			if (true == isFlow)
			{
				Flows.Push(curr);
			}
			else
			{
				while (false == Flows.IsEmpty())
				{
					if (*(Flows.Top()) > curr)
					{
						break;
					}
					else
					{
						Flows.Pop();
					}
				}

				if (true == Flows.IsEmpty())
				{
					++live;
				}
			}
		}

		live += Flows.Count();

		Flows.Clear();

		return live;
	}
};
