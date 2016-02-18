#include <stdio.h>
#include <stdlib.h>

int main()
{
	const int lengthofword = 20;
	char szWords[lengthofword] = {0,};

	scanf("%s", szWords);

	int countWord = lengthofword, countAlphabetWord = 0;

	const int countasc = 128;
	int countAscs[countasc] = {0,};
	for(int i = 0; i < lengthofword; ++i)
	{
		char current = szWords[i];
		if(NULL == current) break;

		if (	current >= 'a' && current <= 'z' 
			||	current >= 'A' && current <= 'Z' )
		{
			countAscs[current]++;
		}
	}

	char output[256] = {0,};
	char previousWord = -1;
	int ibuf = 0;

	for(int i = 0; i < countWord; ++i)
	{
		int current = szWords[i];
		if (	current != previousWord && 
			(	current >= 'a' && current <= 'z' 
			||	current >= 'A' && current <= 'Z' ))
		{
			ibuf += sprintf(output + ibuf, "%d%c", countAscs[current], (char)current);
			previousWord = current;
		}
	}

	printf(output);

	return EXIT_SUCCESS;
}
