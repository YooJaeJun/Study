#include <iostream>
#include <utility>
#include <vector>

// 표현식이 다음 경우 중 하나라도 포함하면, noexcept는 false
//	1. 상수 표현식이 아닌 함수가 noexcept 키워드를 가지지 않을 경우
//	2. 런타임 체크가 필요한 dynamic_cast 등의 RTTI가 포함된 경우
//	3. typeid 표현식에 포함된 타입이 상속 관계에 있는 클래스나 구조체일 경우

void may_throw();
void no_throw() noexcept;
auto lmay_throw = [] {};
auto lno_throw = []() noexcept {};

class T
{
public:
	// 명시적 소멸자 선언으로 이동생성자, 이동연산자 암시적 생성 금지
	// 하지만 복사생성자/대입연산자는 noexcept로 암시적 생성
	~T() {}
};

class U
{
public:
	// 명시적 소멸자 선언으로 이동생성자, 이동연산자 암시적 생성 금지
	// 하지만 복사생성자/대입연산자는 noexcept(false)로 암시적 생성
	// vector<int> v의 복사생성자/대입연산자가 noexcept가 아니기 때문
	~U() {}
	std::vector<int> v;
};

class V
{
public:
	// 복사생성자/대입연산자는 noexcept(false)로 암시적 생성
	// 이동생성자/이동연산자는 noexcept로 암시적 생성
	// vector<int> v의 복사생성자/대입연산자가 noexcept가 아니기 때문
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