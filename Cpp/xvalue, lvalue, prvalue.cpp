
// Category				Can be moved from (m)		Can't be moved from (M)
// Have identity		xvalue						lvalue						ㅡ glvalue (i)
// Have not identity	prvalue
//							|
//						 rvalue (m)

// xvalue
//	a.m의 m
//	a.*mp의 mp
//	a ? b : c에서 b와 c


#include <iostream>

namespace detail
{
	template <class T> struct value_category { static constexpr char const* value = "prvalue"; };
	template <class T> struct value_category<T&> { static constexpr char const* value = "lvalue"; };
	template <class T> struct value_category<T&&> { static constexpr char const* value = "xvalue"; };
}

#define PRINT(expr) std::cout << #expr << " is a " << ::detail::value_category<decltype((expr))>::value << '\n';

struct S { int i; };

int main()
{
	int&& r = 42;
	PRINT(4);				// prvalue
	PRINT(r);				// lvalue
	PRINT(std::move(r));	// xvalue

	PRINT(S{ 0 });			// prvalue
	PRINT(S{ 0 }.i);		// xvalue

	std::cout << '\n';
	S s;
	PRINT(s);				// lvalue
	PRINT(s.i);				// lvalue

	auto V = []() {};
	PRINT(V());				// prvalue

	auto RR = []()->int&& { return 3; };
	PRINT(RR());			// xvalue

	PRINT(static_cast<int&&>(7));	// xrvalue
}