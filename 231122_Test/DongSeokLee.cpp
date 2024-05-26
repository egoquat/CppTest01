#include "DongSeokLee.h"

template<typename T>
T myabs(T num)
{
	if (num < 0) num = -num;
	return num;
}

template<typename DT>
Test<DT>::Test(DT v)
{
	SetValue(v);
}

template<typename DT>
void Test<DT>::SetValue(DT v)
{
	Value = v;
}

template<typename DT>
DT Test<DT>::GetValue()
{
	return Value;
}

template<typename TA, typename TB>
Data<TA, TB>::Data(TA v)
{
	Value = v;
}

template<typename TA, typename TB>
void Data<TA, TB>::CopyData(TB v)
{
	Value = v;
}

template<typename TA, typename TB>
TA Data<TA, TB>::GetData()
{
	return Value;
}

int main()
{
	int a = -10;
	cout << a << "의 절대값=" << myabs(a) << endl;

	double b = -3.4;
	cout << b << "의 절대값=" << myabs(b) << endl;

	Test<int> obj1(10);
	obj1.SetValue(20);
	cout << " " << obj1.GetValue() << endl;

	Test<double> obj2(5.7);
	obj2.SetValue(6.1245);
	cout << " " << obj2.GetValue() << endl;

	int c = 10;
	Data<int, int&> obj3(10);
	cout << " " << obj3.GetData() << endl;

	obj3.CopyData(c);
	cout << " " << obj3.GetData() << endl;
	
	b = 3.4;
	Data<double, double&> obj4(1.5);
	cout << " " << obj4.GetData() << endl;

	obj4.CopyData(b);
	cout << " " << obj4.GetData() << endl;

	char ch; cin >> ch;
}
