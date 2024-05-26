#pragma once
#include <iostream>
using namespace std;

template<typename DT>
class Test {
	DT Value;
public:
	Test(DT v);
	void SetValue(DT v);
	DT GetValue();
};

template<typename TA, typename TB>
class Data {
	TA Value;
public:
	Data(TA v);
	void CopyData(TB v);
	TA GetData();
};
