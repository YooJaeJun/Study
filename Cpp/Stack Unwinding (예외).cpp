// Stack Unwinding
// 예외가 발생되는 Scope 안에서 예외처리가 되지 못할 때
// 함수 호출 Stack을 풀면서 함수가 호출되었던 부분으로 돌아가 예외처리를 시도하는 것

#include <iostream>
using namespace std;
using std::runtime_error;

void func1() throw (runtime_error)
{
	throw runtime_error("Runtime Error int func1");
}
void func2() throw(runtime_error)
{
	func1();
}
void func3() throw(runtime_error)
{
	func2();
}

int main()
{
	try
	{
		func3();
	}
	catch (runtime_error& error)
	{
		cout << "Exception Generate : " << error.what() << endl;
		system("pause");
	}
	return 0;
}