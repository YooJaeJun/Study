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
	[[nodiscard("생성자 버리지 마세요")]]
	Knight(int hp) : _hp(hp) {}

private:
	int _hp = 100;
};

enum class [[nodiscard("ErrorCode 사용하세요")]] ErrorCode
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
			// 최적화
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
	// 함수가 리턴을 하지 않는다.
	// 
	// [[deprecated]] C++14
	// 구식 함수 사용 권장 안 함
	// 
	// [[nodiscard]] C++17
	// 값이 버려질 경우 컴파일 에러
	// 
	// [[nodiscard("사유")]], 생성자에도 추가 C++20
	// 
	// [[likely]] [[unlikely]]
	// 여기 들어올 확률 높다 -> 컴파일러 최적화
	// 
	// [[no_unique_address]]
	// 주소 공용 사용 가능할 수 있다.
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