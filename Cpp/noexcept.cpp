#include <iostream>
#include <utility>
#include <vector>

// ǥ������ ���� ��� �� �ϳ��� �����ϸ�, noexcept�� false
//	1. ��� ǥ������ �ƴ� �Լ��� noexcept Ű���带 ������ ���� ���
//	2. ��Ÿ�� üũ�� �ʿ��� dynamic_cast ���� RTTI�� ���Ե� ���
//	3. typeid ǥ���Ŀ� ���Ե� Ÿ���� ��� ���迡 �ִ� Ŭ������ ����ü�� ���

void may_throw();
void no_throw() noexcept;
auto lmay_throw = [] {};
auto lno_throw = []() noexcept {};

class T
{
public:
	// ����� �Ҹ��� �������� �̵�������, �̵������� �Ͻ��� ���� ����
	// ������ ���������/���Կ����ڴ� noexcept�� �Ͻ��� ����
	~T() {}
};

class U
{
public:
	// ����� �Ҹ��� �������� �̵�������, �̵������� �Ͻ��� ���� ����
	// ������ ���������/���Կ����ڴ� noexcept(false)�� �Ͻ��� ����
	// vector<int> v�� ���������/���Կ����ڰ� noexcept�� �ƴϱ� ����
	~U() {}
	std::vector<int> v;
};

class V
{
public:
	// ���������/���Կ����ڴ� noexcept(false)�� �Ͻ��� ����
	// �̵�������/�̵������ڴ� noexcept�� �Ͻ��� ����
	// vector<int> v�� ���������/���Կ����ڰ� noexcept�� �ƴϱ� ����
	std::vector<int> v;
};

int main()
{
	T t;
	U u;
	V v;

	std::cout << std::boolalpha
		<< "Is may_throw() noexcept? " << noexcept(may_throw()) << '\n'
		<< "Is no_throw() noexcept? " << noexcept(no_throw()) << '\n'
		<< "Is lmay_throw() noexcept? " << noexcept(lmay_throw()) << '\n'
		<< "Is lno_throw() noexcept? " << noexcept(lno_throw()) << '\n'
		<< "Is ~T() noexcept? " << noexcept(std::declval<T>().~T()) << '\n'
		<< "Is T(rvalue T) noexcept? " << noexcept(T(std::declval<T>())) << '\n'
		<< "Is T(lvalue T) noexcept? " << noexcept(T(t)) << '\n'
		<< "Is U(rvalue U) noexcept? " << noexcept(U(std::declval<U>())) << '\n'
		<< "Is U(lvalue U) noexcept? " << noexcept(U(u)) << '\n'
		<< "Is V(rvalue V) noexcept? " << noexcept(V(std::declval<V>())) << '\n'
		<< "Is V(lvalue V) noexcept? " << noexcept(V(v)) << '\n';
}