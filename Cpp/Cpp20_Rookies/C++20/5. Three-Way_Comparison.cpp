#include <iostream>
using namespace std;

// Spaceship Operator <=>

struct MyInt
{
	MyInt(int value) : _value(value) {}

	// < <= > >= == !=

	// 특수본 - 우선순위 더 높음
	bool operator<(const MyInt& rhs) const { return _value < rhs._value; }

	// auto operator<=>(const MyInt& rhs) const { return _value <=> rhs._value; }
	auto operator<=>(const MyInt& rhs) const = default;

	int _value;
};

struct Strong
{
	std::strong_ordering operator<=>(const Strong&) const = default;
};
struct Weak
{
	std::weak_ordering operator<=>(const Weak&) const = default;
};
struct Partial
{
	std::partial_ordering operator<=>(const Partial&) const = default;
};

struct Test
{
	auto operator<=>(const Test&) const = default;
	Strong s;
	Weak w;
	Partial p;
};

int main()
{
	MyInt a{ 1 };
	MyInt b{ 2 };

	bool test = a < b;
	bool test2 = a > b;
	bool test3 = a <= b;


	// strong ordering
	// weak ordering
	// partial ordering

	// 비교 (Relational, Equivalence, Comparable)
	// - 6종 비교 연산 지원 ==, !=, <, <=, >, >= (Relational)
	// - 모든 Equivalent한 값들은 서로 구분되지 않고 완전 똑같다 (Equivalence)
	// ex) 대소문자 구별 안 하는 문자열 비교 rookiss Rookiss
	// - a < b, a == b, a > b 중 하나는 참이다 (Comparable)
	// ex) float 비교할 때, b가 Nan(not a number) 면 3연산이 다 true가 아님

	// Strong Ordering : Relational (o), Equivalence(o), Comparable(o)
	// Weak Ordering : Relational (o), Comparable(o)
	// Partial Ordering : Relational (o)


	Test t1;
	Test t2;

	t1 <=> t2;

	int a1 = 100;
	int b1 = 200;

	auto ret = (a1 <=> b1);

	if (ret < 0)
		cout << "a < b" << endl;
	else if (ret == 0)
		cout << "a == b" << endl;
	else
		cout << "a > b" << endl;
}