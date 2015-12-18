#include <stdio.h>

int main2()
{
	const int lengthInput = 256;
	char inputs[lengthInput] = {0,};
	scanf("%[^\n]", inputs);
	printf("\n");
	
	int length = 0;
	for(int i = 0; i < lengthInput; ++i)
	{
		char current = inputs[i];
		if(NULL == current) { break; }
		length++;
	}
	
	char *reverse = new char[length + 1];
	bool reversing = true; 
	int sequence = 0;
	while(1)
	{
		int seq = sequence++;
		reverse[seq] = inputs[length-seq-1];
		if(seq == length) break;
	}
	reverse[length] = NULL;

	printf(reverse);

	return 0;
}

