#include <stdio.h>

int main()
{
	const int lengthofword = 20;
	char szWords[lengthofword] = {0, };

	printf_s("Enter Alphabet(ex:AAABBGFFFF)(less 20) : ");
	scanf_s("%s", szWords, lengthofword);

	int countWord = lengthofword, countAlphabetWord = 0;
	int countNagative = 0;

	const int countasc = 128;
	int countAscs[countasc] = {0,};

	for(int i =0;i < lengthofword; ++i)
	{
		char *pivot = &szWords[i];
		if(NULL == *pivot ) { countWord = i; break;}
		int ascNum = *pivot;
		if(	ascNum <= 'z' && ascNum >= 'a' || ascNum <= 'Z' && ascNum >= 'A')
		{
			countAlphabetWord++;
			countAscs[ascNum]++;
		}
		else
		{
			countNagative++;
		}
	}

	//if (countNagative > 0) { printf_s("Alphabet word only acceptable."); return 0; }

	const int sizeOutput= 128;
	char output[sizeOutput] = {0,};
	int ibuf = 0;
	bool isOutput[countasc] = {false,};

	for(int i = 0; i<countWord; ++i)
	{
		int current = szWords[i];
		if(	current <= 'z' && current >= 'a' || current <= 'Z' && current >= 'A')
		{
			if(false == isOutput[current])
			{
				isOutput[current] = true;
				ibuf += sprintf_s(output + ibuf, sizeOutput - ibuf, "%d%c", countAscs[current], (char)current);
			}
		}
	}

	printf_s("\nWords:%s/countWord:%d/countPositive:%d/countNagative:%d\n", 
		szWords, countWord, countAlphabetWord, countNagative );
	printf_s("%s\n", output);

	return 0;
}