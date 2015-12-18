#include ".\imsimain.h"

#include <iostream>
#include <windows.h>

//int main()
//{
//	FILE *fImsi = fopen("testImsi2.txt", "wb");
//
//	for (int i = 0; i < 100; i++)
//	{
//		fprintf(fImsi, "%d \n", i);
//	}
//	fclose(fImsi);
//
//	return 0;
//}

#include <stdio.h>

void plus(void (*)(void));
void func();

int main()
{
	void (*pFunc)(void);
	pFunc = func;
	plus(pFunc); 

	return 0;
} 

void plus(void (*p)(void))
{
	p();
}

void func()
{
	printf("Call func\n");
}

imsiMain::imsiMain(void)
{
}

imsiMain::~imsiMain(void)
{
}
