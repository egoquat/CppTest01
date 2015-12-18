#include ".\imsimain.h"
#include <iostream>

// using polymorphic 
// so access separate derived class that has a static variable
// polymorphic 을 이용한 각 Derived Class 별로 Static 내용에 접근
template<typename T>
struct StaticValue
{
	static int& val() {
		static int val_;
		return val_;
	}
};



struct B
{
	virtual void print_val() = 0;
};

struct D1: public B, StaticValue<D1>
{
	void print_val() 
	{ 
		std::cout << "Call D1 : " << val() << "\n"; 
	}
};

struct D2: public B, StaticValue<D2>
{
	void print_val() { 
		std::cout << "Call D2 : " << val() << "\n";
	}
};

void polymorphic(B& b)
{
	b.print_val();
}

int main(int argc, char *argv[])
{
	D1 d1, d1_too;
	D1::val() = 10;
	//d1.print_val();
	//d1_too.print_val();

	D2 d2;
	D2::val() = 20;

	d2.print_val();
	//polymorphic(d1);
	//polymorphic(d1_too);

	//polymorphic(d2);

	D1 d3;

	D1::val() = 30;

	polymorphic(d3);
	polymorphic(d1);
	polymorphic(d1_too);

	polymorphic(d2);


	return 1;
}

imsiMain::imsiMain(void)
{
}

imsiMain::~imsiMain(void)
{
}
