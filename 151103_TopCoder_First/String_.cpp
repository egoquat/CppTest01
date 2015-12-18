#include "String_.h"

bool String_::MainSubstr01()
{
	string s = "abc";

	if ("abc" == s) cout << "equal" << endl;

	char c = s[1];

	s = "def" + s + "ghi";

	s = s.substr(3, 3);

	return true;
}

bool String_::MainCountString01(vector<string> s)
{
	map<string, int> m;

	for (int i = 0; i < s.size(); ++i)
	{
		m[s[i]]++;
	}

	cout << "------> Counting Result : " << s.size() << endl;

	map<string, int>::iterator it = m.begin();

	while (m.end() != it)
	{
		if (true == (*it).first.empty())
		{
			cout << "empty" << endl;
		}
		else
		{
			cout << (*it).first << " " << (*it).second << endl;
		}
		++it;
	}

	return true;
}

String_::String_()
{
}


String_::~String_()
{
}
