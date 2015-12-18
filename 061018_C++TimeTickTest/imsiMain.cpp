#include ".\imsimain.h"

#include <iostream>

//#include <time.h>

#include "windows.h"

int main()
{
	LARGE_INTEGER	CurrentTicks;
	LARGE_INTEGER	CurrentTicksPerSecond;

	unsigned long	llCurrentTicks[100];
	unsigned long	llTicksPerSecond;


	unsigned int	uiElapsedTicks = 0;
	float			fCurrentSecond[102];
	float			fImsiSecond;

	QueryPerformanceFrequency( &CurrentTicksPerSecond );
	llTicksPerSecond		= (unsigned long)(CurrentTicksPerSecond.QuadPart);
	int i = 0;
	for (; i < 100; ++i)
	{
		QueryPerformanceCounter( &CurrentTicks );

		llCurrentTicks[i]		= CurrentTicks.QuadPart;

		uiElapsedTicks = (unsigned int)(llCurrentTicks[i] - llCurrentTicks[i-1]);
		fImsiSecond = (float)uiElapsedTicks / (float)llTicksPerSecond;
		fCurrentSecond[i] = fImsiSecond;

		printf ( "%d. Gap_Ticks=%ul, TicksPerSecond=%ul, Gap_ms=%10.6f \n",
			i , uiElapsedTicks, llTicksPerSecond, fCurrentSecond[i] );
	}

	uiElapsedTicks = (unsigned int)(llCurrentTicks[i] - llCurrentTicks[0]);
	fImsiSecond = (float)uiElapsedTicks / (float)llTicksPerSecond;

	printf ( "Min_Max Gap : %10.6f\n", fImsiSecond);

	/*char FileName[MAX_PATH];
	HANDLE Rfpt; 
	DWORD RWSize; 

	strcpy( FileName, "aaa.txt" );

	Rfpt = CreateFile( FileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );

	if( Rfpt == INVALID_HANDLE_VALUE ) 
	{ 
		MessageBox( NULL, "파일 읽기 오류", "Error", MB_OK ); 
		return E_FAIL; 
	} */

	/*imsiMain::iTemp = 4;

	char sBuffer[MAX_PATH];

	sprintf( sBuffer, "StaticTemp : %d", imsiMain::iTemp );

	printf("%s", sBuffer);*/

	return EXIT_SUCCESS;
}

int imsiMain::iTemp;

imsiMain::imsiMain(void)
{
}

imsiMain::~imsiMain(void)
{
}

