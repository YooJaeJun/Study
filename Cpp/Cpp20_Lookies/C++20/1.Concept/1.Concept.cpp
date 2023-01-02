#include <iostream>
using namespace std;
#include <list>
#include <algorithm>

template<typename T>
void TestTemplate(T number)
{
	cout << number << endl;
}

//template<typename T>
//concept integral = std::is_integral_v<T>;

// Concept
// 1) Requires Clause(��)
template<typename T>
requires std::integral<T>
void TestConcept1(T number)
{
	cout << number << endl;
}

// 2) Trailing Requires Clause (�ڿ� �ٴ�~)
template<typename T>
void TestConcept2(T number) requires std::integral<T>
{
	cout << number << endl;
}

// 3) Constrained Template Parameter (�����)
template<std::integral T>
void TestConcept3(T number)
{
	cout << number << endl;
}

// 4) Abbreviated Function Template
void TestConcept4(std::integral auto number)
{
	cout << number << endl;
}


class GameObject
{

};

class Knight : public GameObject
{

};

// ��� ����
// derived from : C# where�� ����
template<typename T>
requires std::derived_from<T, GameObject>
void TestObj(T* obj)
{

}

template<typename T>
concept MyConcept = !std::is_integral_v<T> && std::derived_from<T, GameObject>;


template<typename T>
concept Addable = requires(T a, T b)
{
	a + b;
};	// a + b�� �����ؾ� ��

template<typename T>
concept Equality = requires(T a, T b)
{
	{ a == b } -> std::convertible_to<bool>;
	{ a != b } -> std::convertible_to<bool>;
};

template<typename T>
concept Integral = std::is_integral_v<T>;

template<typename T>
concept SignedInt = Integral<T> && std::is_signed_v<T>;


int main()
{
	TestConcept4(10);
	// TestConcept4(10.3);

	// ������ Ÿ�ӿ� true, false ����
	constexpr bool check = _Is_any_of_v<int, short, float, long long>;


	list<int> li;
	// ����Ʈ�� ���� ������ �� ��
	// std::sort(li.begin(), li.end());
	// ���̺귯�� ���� �� ��Ȯ�ϰ� ���� �� �ִ�.
	// �ٸ� ������ ���α׷��� ���忡�� ����


	TestObj(new GameObject);
	TestObj(new Knight);
	// TestObj(new int);
}