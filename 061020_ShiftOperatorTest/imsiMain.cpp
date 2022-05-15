
//@ Memory leak checker
#define CHECK_MEMORYLEAK

#ifdef CHECK_MEMORYLEAK

#define CRTDBG_MAP_ALLOC 
#include <stdlib.h> 
#include <crtdbg.h>

#ifdef _DEBUG
#define new new( _NORMAL_BLOCK, __FILE__, __LINE__ )
#endif // _DEBUG

#endif // CHECK_MEMORYLEAK
// //@ Memory leak checker

#include "windows.h"
#include <iostream>
#include <string.h>

using namespace std;

#define		LEFT	<<
#define		RIGHT	>>

int main(int argc, char *argv[])
{
#ifdef CHECK_MEMORYLEAK
 	   _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//	_CrtSetBreakAlloc(151);
#endif // CHECK_MEMORYLEAK

	int				baseNumber = 0;
	int				operatorType = 0;
	int				shiftNumber = 0;
	int				resultNumber = 0;

	char*			szTempBuffer = new char[MAX_PATH];

	//while (true)
	//{
	//	printf("\nWrite Any Number:");
	//	scanf("%d", &baseNumber);

	//	printf("\n 1.<<  2.>>");
	//	printf("\n Select Operator:");
	//	scanf("%d", &operatorType);

	//	printf("\n Write Shift Number :", shiftNumber);
	//	scanf("%d", &shiftNumber);

	//	if (operatorType == 1)
	//	{
	//		resultNumber = baseNumber LEFT shiftNumber;// - baseNumber;

	//	}
	//	else
	//	{
	//		resultNumber = baseNumber RIGHT shiftNumber;// + baseNumber;
	//	}

	//	sprintf(szTempBuffer, "\nResult Number:%d\n", resultNumber);

	//	printf(szTempBuffer);

	//	memset(szTempBuffer, 0, sizeof(char) * MAX_PATH);

	//	printf("Again?(1:Yes/2:No):");

	//	int inputNumber = 1;
	//	scanf("%d", &inputNumber);

	//	if (1 != inputNumber)
	//	{
	//		break;
	//	}
	//}

	delete[] szTempBuffer; 

	return EXIT_SUCCESS;
}
