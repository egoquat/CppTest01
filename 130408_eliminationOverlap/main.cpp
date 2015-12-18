#include <string>
#include <iostream>

using namespace std;

int main()
{
	string inputs;
	string adds = "12345";
	const int count = 4;
	string converts[count];

	cin >> inputs;
	int spot = 0;
	string words = "";
	
	for(int i = 0; i < inputs.size(); ++i)
	{
		char current = inputs[i];
		if(','==current) { words = ""; }
		else { words.append(current); }
	}

	cout << "append:";
	cout << converts[0].append(adds);
	cout << endl;

	cout << "assign:";
	cout << converts[1].assign(adds);
	cout << endl;

	cout << "replace:";
	cout << converts[2].replace(1,(inputs.size()<5+1)?inputs.size():5,adds);
	cout << endl;

	return EXIT_SUCCESS;
}
