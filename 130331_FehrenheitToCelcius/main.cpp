#include <stdio.h>

int maintest()
{
	const int lengthInOut = 32;
	char szInput[lengthInOut] = {0,};

	printf("Input FehrenHeit or Celsius (nF/nC): ");
	scanf("%s", szInput);
	
	bool fToc = false, validateFC = false;
	int countBuf = 0;
	int temperature = 0;
	for(int i=0; i<lengthInOut; ++i)
	{
		char current = szInput[i];

		if(!('0' <= current && '9' >= current 
			|| 'F'== current 
			|| 'f'== current 
			|| 'C' == current
			|| 'c' == current))
		{
			printf("Input words are only acceptable to 0~9 and F or C."); return 0;
		}

		if(current == 'F' || current == 'f')
		{
			fToc = true; validateFC = true;
			break;
		}

		if (current == 'C' || current == 'c')
		{
			fToc = false; validateFC = true;
			break;
		}
		//temperature = temperature + (pow (10.0f, countBuf) * ((int)current - (int)'0'));
		temperature = (temperature * 10) + ((int)current - (int)'0');
		countBuf++;
	}

	if(1 > countBuf) { printf("Length of inputs must be 1 more. Too short word."); return 0; }
	if(false == validateFC) { printf("Last word must be 'F' or 'C' as Fehrenheit or Celcius"); return 0; }
	
	int converted = 0;
	if(true == fToc)
	{
		converted = (temperature - 30) / 2;
		printf("%dF/%dC\n", temperature, converted);
	}
	else
	{
		converted = (temperature * 2) + 30;
		printf("%dC/%dF\n", temperature, converted);
	}

	return 0;
}

