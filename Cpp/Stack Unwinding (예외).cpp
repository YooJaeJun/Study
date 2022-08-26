// Stack Unwinding
// ���ܰ� �߻��Ǵ� Scope �ȿ��� ����ó���� ���� ���� ��
// �Լ� ȣ�� Stack�� Ǯ�鼭 �Լ��� ȣ��Ǿ��� �κ����� ���ư� ����ó���� �õ��ϴ� ��

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