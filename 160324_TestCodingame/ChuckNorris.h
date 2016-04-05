#include <string>
#include <map>

using namespace std;

class ChuckNorris
{
public:
	typedef unsigned int uint;

	string ToBinary(const string& M)
	{
		string B, W;

		for (uint i = 0; i < M.size(); ++i)
		{
			uint c = (uint)M[i];

			W = "";

			while (c > 0)
			{
				W = to_string(c % 2) + W;

				c = c / 2;
			}

			for (uint z = 0; z < 7 - W.size(); ++z)
			{
				W = "0" + W;
			}

			B += W;
		}

		return B;
	}

	int main(string MESSAGE)
	{
		// Write an action using cout. DON'T FORGET THE "<< endl"
		// To debug: cerr << "Debug messages..." << endl;
		string B = ToBinary(MESSAGE);

		//cerr << "B:" << B << endl;

		map<char, string> convert;
		convert['0'] = "00";
		convert['1'] = "0";

		char last = B[0];
		char cnt = 1;

		string output;

		for (uint i = 1; i <= B.size(); ++i)
		{
			char curr = (1 < B.size()) ? B[i] : (('0' == B[i - 1]) ? '1' : '0');

			if (last == curr)
			{
				cnt++;
			}
			else
			{
				output += convert[curr] + " ";
				while (cnt-- > 0)
				{
					output += "0";
				}

				if (i < B.size())
				{
					output += " ";
				}

				cnt = 1;
			}

			last = curr;
		}

		//cout << output << endl;
	}
};
