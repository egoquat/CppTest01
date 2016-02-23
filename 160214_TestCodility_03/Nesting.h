#include <vector>
#include "Stack.h"

class Nesting
{
public :
	bool isNest(char c)
	{
		return ('(' == c) || (')' == c);
	}

	bool isCloseNest(char c)
	{
		return (')' == c);
	}

	bool isOpenNest(char c)
	{
		return ('(' == c);
	}

	int solution(string &S)
	{
		if (S.length() <= 1) return false;

		bool isNested = true;
		Stack<char> nests;

		for (unsigned int i = 0; i < S.length(); ++i)
		{
			char c = S[i];
			if (true == isNest(c))
			{
				if (true == isOpenNest(c))
				{
					nests.Push(c);
				}
				else
				{
					if (true == nests.IsEmpty())
					{
						isNested = false;
						break;
					}
					else
					{
						char t = *nests.Top();
						if (true == isOpenNest(t))
						{
							nests.Pop();
						}
						else
						{
							isNested = false;
							break;
						}
					}
				}
			}
		}

		isNested = isNested && (true == nests.IsEmpty()) ? true : false;

		nests.Clear();

		return isNested;
	}
};
