#pragma once
#include <iostream>
using namespace std;

class Factorial
{
private:
	int _numFac;

	//@ get / set
public:
	void SetNumFactorial(int numFac);

private:
	void DoFactorialRecursive(int numFactorial, int& numSum);
	int DoFactorialLoop(int numFactorial);

public :
	int DoFactorialRecursive();
	int DoFactorialLoop();

public:
	Factorial();
	Factorial(int numFactorial);
	~Factorial(void);
};

