#include <vector>
#include "Stack.h"

class StoneWall
{
public:

	int solution(vector<int> &H)
	{
		if (H.size() <= 1) return H.size();

		int cntBlock = 0;
		Stack<int> Heights;

		for (unsigned int i = 0; i < H.size(); ++i)
		{
			int curr = H[i];
			bool isSameH = false;

			while (Heights.IsEmpty() == false)
			{
				int t = *Heights.Top();
				if (t < curr)
				{
					break;
				}

				if (t == curr) isSameH = true;

				Heights.Pop();
			}

			if ((true == Heights.IsEmpty()
				|| *Heights.Top() < curr)
				&& false == isSameH)
			{
				cntBlock++;
				Heights.Push(curr);
			}

			/*int curr = H[i];
			bool isSameH = false;

			if ((true == Heights.IsEmpty()
				|| *Heights.Top() < curr))
			{
				Heights.Push(curr);
			}
			else
			{
				while (Heights.IsEmpty() == false)
				{
					int t = *Heights.Top();
					if (t <= curr)
					{
						if (t == curr) isSameH = true;
						break;
					}

					cntBlock++;
					Heights.Pop();
				}

				if (true != isSameH)
				{
					Heights.Push(curr);
				}
			}*/
		}

		cntBlock += Heights.Count();

		return cntBlock;
	}
};
