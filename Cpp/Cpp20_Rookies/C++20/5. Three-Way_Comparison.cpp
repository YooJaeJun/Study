#include <iostream>
using namespace std;

// Spaceship Operator <=>

struct MyInt
{
	MyInt(int value) : _value(value) {}

	// < <= > >= == !=

	// Ư���� - �켱���� �� ����
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

	// �� (Relational, Equivalence, Comparable)
	// - 6�� �� ���� ���� ==, !=, <, <=, >, >= (Relational)
	// - ��� Equivalent�� ������ ���� ���е��� �ʰ� ���� �Ȱ��� (Equivalence)
	// ex) ��ҹ��� ���� �� �ϴ� ���ڿ� �� rookiss Rookiss
	// - a < b, a == b, a > b �� �ϳ��� ���̴� (Comparable)
	// ex) float ���� ��, b�� Nan(not a number) �� 3������ �� true�� �ƴ�

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