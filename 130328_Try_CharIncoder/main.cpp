#include <stdio.h>

int main()
{
	const int lengthofword = 20;
	char szWords[lengthofword] = {'A','A','A','B','B','G','F','F','F','F',};

	int countWord = lengthofword, countAlphabetWord = 0;

	const int countasc = 128;
	int countAscs[countasc] = {0,};

	for(int i = 0; i < lengthofword; ++i)
	{
		char *pivot = &szWords[i];
		if(NULL == *pivot) {countWord = i; break;}
		int ascNum = *pivot;
		if(ascNum <= 'z' && ascNum >= 'a' || ascNum <= 'Z' && ascNum >= 'A')
		{
			countAlphabetWord++;
			countAscs[ascNum]++;
		}
	}

	const int sizeOutput = 128;
	char output[sizeOutput] = {0,};
	int ibuf = 0;
	bool isOutput[countasc] = {false,};

	for(int i = 0; i < countWord; ++i)
	{
		int current = szWords[i];
		if(current <= 'z' && current >= 'a' || current <= 'Z' && current >= 'A')
		{
			if(false == isOutput[current])
			{
				isOutput[current] = true;
				ibuf += sprintf(output + ibuf, "%d%c", countAscs[current], (char)current);
			}
		}
	}

	printf(output);

	return 0;
}