#include ".\imsimain.h"

#include "windows.h"
#include <iostream>

int main ()
{
	typedef struct STRUCTTEST
	{
		union
		{
			struct 
			{
				float fx, fy, fz;
			};

			float fParameter[3];
		};
	}StructTest;

	StructTest structTest;

	structTest.fx = 1.0f;
	structTest.fy = 2.0f;
	structTest.fz = 3.0f;
	
	printf("sizeof bool		: %d \n", sizeof(bool));
	printf("sizeof BOOL		: %d \n", sizeof(BOOL));
	printf("sizeof byte		: %d \n", sizeof(byte));
	printf("sizeof BYTE		: %d \n", sizeof(BYTE));
	printf("sizeof char		: %d \n", sizeof(char));
	printf("sizeof CHAR		: %d \n", sizeof(CHAR));
	printf("sizeof short		: %d \n", sizeof(short));
	printf("sizeof int		: %d \n", sizeof(int));
	printf("sizeof INT64		: %d \n", sizeof(INT64));
	printf("sizeof long		: %d \n", sizeof(long));
	printf("sizeof float		: %d \n", sizeof(float));
	printf("sizeof double	: %d \n",sizeof(double));
	printf("sizeof LONGLONG	: %d \n", sizeof(LONGLONG));
	printf("sizeof STRUCTTEST	: %d \n", sizeof(STRUCTTEST));
				   
	printf("struct Test.fx		: %f \n",  structTest.fx);
	printf("struct Test.fy		: %f \n",  structTest.fy);
	printf("struct Test.fz		: %f \n",  structTest.fz);
				   
	printf("struct Test.fParameter[0]		: %f \n",  structTest.fParameter[0]);
	printf("struct Test.fParameter[1]		: %f \n",  structTest.fParameter[1]);
	printf("struct Test.fParameter[2]		: %f \n",  structTest.fParameter[2]);

	return EXIT_SUCCESS;
}

imsiMain::imsiMain(void)
{
}

imsiMain::~imsiMain(void)
{
}
