#include "TestMain.h"
#include "windows.h"
#include <iostream>
#include "time.h"

TestMain::TestMain()
{
}

TestMain::~TestMain()
{
}

int main()
{
	LARGE_INTEGER		lCurrentTick;
	LARGE_INTEGER		lTickPerSecond;

	LONGLONG			llTickPerSecond = 0;
	LONGLONG			llCurrentTick = 0;
	LONGLONG			llPreTick = 0;

	unsigned int		iSummarySecond = 0;
	float				fSummarySecond = 0.0f;

	QueryPerformanceFrequency(&lTickPerSecond);

	llTickPerSecond = lTickPerSecond.QuadPart;

	printf("TickPerSecond:%lu \n", lTickPerSecond);

	while (1)
	{
		QueryPerformanceCounter(&lCurrentTick);
		llCurrentTick = lCurrentTick.QuadPart;

		if (llPreTick != 0)
		{
			fSummarySecond += (float)(llCurrentTick - llPreTick)
				/ (float)llTickPerSecond;
			if (fSummarySecond > 1.0f)
			{
				fSummarySecond = 0.0f;

				++iSummarySecond;

				printf("Second:%d \n", iSummarySecond);
			}
		}

		llPreTick = llCurrentTick;
	}
}