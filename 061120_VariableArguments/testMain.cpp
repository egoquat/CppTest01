
#include <stdio.h>
#include <stdarg.h>

int DoAverage(int first, ...)
{
	int count = 0, sum = 0, i = first;

	va_list marker;

	va_start(marker, first);

	while (i != -1)
	{
		sum += i;
		count++;
		i = va_arg(marker, int);
	}

	va_end(marker);

	return(sum ? (sum / count) : 0);
}

int main( void )
{
	 /* Call with 3 integers (-1 is used as terminator). */
   printf( "Average is: %d\n", DoAverage( 2, 3, 4, -1 ) );

   /* Call with 4 integers. */
   printf( "Average is: %d\n", DoAverage( 5, 7, 9, 11, -1 ) );

   /* Call with just -1 terminator. */
   printf( "Average is: %d\n", DoAverage( 10, 0, 5, -1 ) );
}


