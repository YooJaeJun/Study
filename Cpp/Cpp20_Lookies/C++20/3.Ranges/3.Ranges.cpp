#include <iostream>
using namespace std;
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <ranges>


// Ŀ����ȭ �� ��
template<std::ranges::input_range Range>
requires std::ranges::view<Range>
class ContainerView : public std::ranges::view_interface<ContainerView<Range>>
{
public:
	ContainerView() = default;
	constexpr ContainerView(Range r) : 
		_range(std::move(r)), _begin(std::begin(r)), _end(std::end(r))
	{}

	constexpr auto begin() const { return _begin; }
	constexpr auto end() const { return _end; }

private:
	Range _range;
	std::ranges::iterator_t<Range> _begin;
	std::ranges::iterator_t<Range> _end;
};

template<typename Range>
ContainerView(Range&& range) -> ContainerView<std::ranges::views::all_t<Range>>;


int main()
{
	// C# LINQ �����̶� ����ϴ�?

	vector<int> v1 = { 1,2,3,4,5,6,7,8,9,10 };

	vector<int> v2;
	//// ¦���� �����ؼ�
	//for (int n : v1)
	//	if (n % 2 == 0)
	//		v2.push_back(n);
	//// 2�� ��
	//for (int& n : v2)
	//	n = n * 2;

	// ����
	// std::for_each();
	// std::find_if();
	// std::any_of();

	auto results = v1 | std::views::filter([](int n) { return n % 2 == 0; })
		| std::views::transform([](int n) { return n * 2; });

	//for (auto n : results)
	//	cout << n << " ";


	// Range : ��ȸ�� �� �ִ� ������ �׷� (ex. STL Container)
	// View : Range�� ���ؼ� ������ �� �ִ� ����

	// std::views::all;
	// std::ranges::filter_view / std::view::filter (���� �����ϴ� �� ����)


	auto results2 = v1 | std::views::filter([](int n) { return n % 2 == 0; })
		| std::views::transform([](int n) { return n * 2; })
		| std::views::take(3);

	for (auto n : results2)
		cout << n << " ";
	cout << '\n';

	std::ranges::sort(v1);

	struct Knight
	{
		std::string name;
		int id;
	};

	vector<Knight> knights =
	{
		{"YJJ", 1},
		{"b", 2},
		{"c", 3},
		{"d", 4},
	};

	std::ranges::sort(knights, {}, &Knight::name);
	std::ranges::sort(knights, std::ranges::greater(), &Knight::name);
	std::ranges::sort(knights, {}, &Knight::id);
	std::ranges::sort(knights, std::ranges::greater(), &Knight::id);

	map<string, int> m =
	{
		{"YJJ", 1},
		{"asdf", 2},
		{"zxcv", 3},
		{"qwer", 4},
	};

	for (const auto& name : std::views::keys(m) | std::views::reverse)
		cout << name << endl;
	cout << '\n';



	// 0~100 ������ ���� �� �Ҽ��� 5���� ���ڸ� �����϶�?

	auto isPrime = [](int num)
	{
		if (num <= 1)
			return false;
		for (int n = 2; n * n <= num; n++)
			if (num % n == 0)
				return false;
		return true;
	};

	// std::views::iota(a, b) : a���� �����ؼ� 1�� ����, b���� �������
	for (int n : std::views::iota(0, 100) | std::views::filter(isPrime) | std::views::take(5))
	{
		cout << n << '\n';
	}
	
	// ��� �� �� �� ��
	// Ŀ���� �� (std::ranges::view_interface)
	std::vector<int> myVec{ 1,2,3,4,5 };
	auto myView = ContainerView(myVec);

	for (auto n : myView)
		cout << n << endl;
}