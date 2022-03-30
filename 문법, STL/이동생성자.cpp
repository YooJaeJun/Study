//#include <coroutine>
#include <iostream>
#include <stdexcept>
#include <thread>
#include <chrono>
#include <vector>
using namespace std::chrono_literals;

int main()
{
	const size_t alloc_size = 1 << 20;
	auto start = std::chrono::steady_clock::now();
	{//case 1 copy
		std::vector<int> v[20];
		v[0].resize(alloc_size);
		for (int i = 1; i != 20; ++i) {
			v[i] = v[i - 1];
		}
	}
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "case 1 copy elapsed time: " << elapsed_seconds.count() << "s\n";
	start = std::chrono::steady_clock::now();
	{//case 2 move
		std::vector<int> v[20];
		v[0].resize(alloc_size);
		for (int i = 1; i != 20; ++i) {
			v[i] = std::move(v[i - 1]);
		}
	}
	end = std::chrono::steady_clock::now();
	elapsed_seconds = end - start;
	std::cout << "case 2 move elapsed time: " << elapsed_seconds.count() << "s\n";

}