#include <iostream>
#include <chrono>
using namespace std;
#define int int64_t

void solution()
{
	const int n = 100'000'000;
	int a = 1;
	chrono::system_clock::time_point startTime = chrono::system_clock::now();
	for (auto i = 0; i < n; i++)
	{
		a /= 2;
	};
	chrono::system_clock::time_point endTime = chrono::system_clock::now();

	chrono::nanoseconds nano = endTime - startTime;

	cout << "소요시간: " << nano.count() / 1'000'000'000 << "." << nano.count() % 1'000'000'000 << "초\n";
}

int32_t main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t = 1;
	// cin >> t;
	for (int i = 0; i != t; i++) solution();
	return 0;
}