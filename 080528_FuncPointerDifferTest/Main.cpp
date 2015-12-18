#include ".\main.h"

CMain::CMain(void)
{
}

CMain::~CMain(void)
{
}

int		g_i;

void		Func1(int i_1)
{
	g_i = i_1;
}

void		Func2(int i_1)
{
	g_i = i_1;
}

#include <stdio.h>

void main()
{
	if (Func1 == Func2)
	{
		printf( "Equal Two functions.\n" );
	}
	else
	{
		printf("Differ Two functions.\n");
	}

	return;
}
