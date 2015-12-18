#include "Factorial.h"

void Factorial::SetNumFactorial(int numFac)
{
	_numFac = numFac;
}

void Factorial::DoFactorialRecursive(int numFactorial, int& numSum)
{
	if (1 >= numFactorial) return;
	numSum = numSum * (numFactorial);
	DoFactorialRecursive(numFactorial - 1, numSum);
}

int Factorial::DoFactorialLoop(int numFactorial)
{
	if (0>=numFactorial) return -1;

	int numIter = numFactorial;
	int numSum = 1;
	while(numIter > 1)
	{
		numSum *= (numIter--);
	}
	return numSum;
}

int Factorial::DoFactorialRecursive()
{
	int numSum = 1;
	DoFactorialRecursive(_numFac, numSum);
	return numSum;
}

int Factorial::DoFactorialLoop()
{
	return DoFactorialLoop(_numFac);
}

Factorial::Factorial()
{
	
}

Factorial::Factorial(int numFactorial)
{
	SetNumFactorial(numFactorial);
}

Factorial::~Factorial(void)
{
}

int main ()
{
	int numInput = -1;
	Factorial factorial = Factorial();

	while (true)
	{
		while (numInput <= 0)
		{
			cout << "Input Number Factorial(Number should be positive) : ";
			cin >> numInput;
		}

		factorial.SetNumFactorial(numInput);

		int numResultFacRecursively = factorial.DoFactorialRecursive();
		int numResultFacLooply = factorial.DoFactorialLoop();
		cout << "Factorial Recursively(" << numInput << "): " << numResultFacRecursively << endl;
		cout << "Factorial Looply(" << numInput << "): " << numResultFacLooply << endl;

		numInput = -1;
	}

	return 0;
}

