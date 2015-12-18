//#include <stdio.h>
//
//void ReverseStringRecursive(char *inputs, char *outputs, int sequence, int length)
//{
//	if(0 > sequence) return;
//
//	outputs[length-sequence] = inputs[sequence];
//	ReverseStringRecursive(inputs, outputs, sequence-1, length);
//}
//
//int main()
//{
//	const int lengthInput = 256;
//	char inputs[lengthInput] = {0,};
//	scanf("%[^\n]", inputs);
//	printf("\n");
//
//	int length = 0;
//	for(int i = 0; i < lengthInput; ++i)
//	{
//		char current = inputs[i];
//		if(NULL == current) { break; }
//		length++;
//	}
//
//	char *reverse = new char[length + 1];
//	bool reversing = true; 
//	int sequence = 0;
//	reverse[length] = NULL;
//
//	/*while(1)
//	{
//		int seq = sequence++;
//		reverse[seq] = inputs[length-seq-1];
//		if(seq == length) break;
//	}
//	reverse[length] = NULL;*/
//
//	ReverseStringRecursive(inputs, reverse, length-1, length-1);
//
//	printf(reverse);
//
//	return EXIT_SUCCESS;
//}

#include <string>
#include <iostream>

using namespace std;
int main()
{
	string x;
	bool first = true;
	while(cin >> x)
	{
		string y(x.rbegin(), x.rend());
		if(first) first = false;
		else cout << " ";
		cout << y;
	}
	cout << endl;

	return EXIT_SUCCESS;
}
