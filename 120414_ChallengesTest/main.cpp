#include <stdio.h>
#include <windows.h>

int main()
{
	const int numLimitMax = 1000000, numLimitMin = 0, numOver = 1, MAXIMUMLOOPING = 1000;
	int numInput = -1;
	int numCalc = 0;
	int sequence = 0;

	while (numInput < numLimitMin || numInput > numLimitMax)
	{
		printf("Enter number within 0 - 1000000:");
		scanf("%d", &numInput);
	}

	numCalc = numInput;
	while (numCalc >= 0 && sequence++ < MAXIMUMLOOPING)
	{
		if(numOver == numCalc) break;
		if(numCalc%2==0)
		{
			numCalc = numCalc / 2;
		}
		else
		{
			numCalc = (numCalc * 3) + 1;
		}

		printf("\n%d", numCalc);
	}

	printf("\n");

	return 1;
}
