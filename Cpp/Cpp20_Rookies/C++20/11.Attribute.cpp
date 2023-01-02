#include <iostream>
#include <vector>
using namespace std;

[[nodiscard]]
int Func()
{
	return 0;
}

class Knight
{
public:
	[[nodiscard("������ ������ ������")]]
	Knight(int hp) : _hp(hp) {}

private:
	int _hp = 100;
};

enum class [[nodiscard("ErrorCode ����ϼ���")]] ErrorCode
{
	none,
	warning,
	critical
};

struct Empty {};

struct NoUniqueAddress
{
	int d;

	[[no_unique_address]]
	Empty e;
};

int Sum(vector<int>& v)
{
	int ret = 0;
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i] < 0)
		{
			// ����ȭ
			[[likely]]
			ret = v[i];
		}
		else
		{
			ret += v[i];
		}
	}
	return ret;
}

ErrorCode GetError()
{
	return ErrorCode::critical;
}


int main()
{
	// [[noreturn]] C++11
	// �Լ��� ������ ���� �ʴ´�.
	// 
	// [[deprecated]] C++14
	// ���� �Լ� ��� ���� �� ��
	// 
	// [[nodiscard]] C++17
	// ���� ������ ��� ������ ����
	// 
	// [[nodiscard("����")]], �����ڿ��� �߰� C++20
	// 
	// [[likely]] [[unlikely]]
	// ���� ���� Ȯ�� ���� -> �����Ϸ� ����ȭ
	// 
	// [[no_unique_address]]
	// �ּ� ���� ��� ������ �� �ִ�.
	// 

	int num = Func();

	// Knight knight(100);
	Knight(100);

	ErrorCode error = GetError();


	NoUniqueAddress n1, n2, n3;
	cout << &n1.e << endl;
	cout << &n2.e << endl;
	cout << &n3.e << endl;
}