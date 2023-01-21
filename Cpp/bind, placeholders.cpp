#include <iostream>
#include <functional>
using namespace std;

void print(const string& s)
{
	cout << s << endl;
}

int sum(const int a, const int b, const int c)
{
	return a + b + c;
}

int main()
{
	auto func1 = std::bind(print, std::placeholders::_1);
	func1("¤»¤»");

	auto func2 = std::bind(sum, std::placeholders::_1, std::placeholders::_1, std::placeholders::_2);
	cout << func2(1, 3, 7) << endl;
}
