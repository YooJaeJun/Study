#include <Turboc.h>
#include <vector>
#include <iostream>
using namespace std;

class yyjvector {
public:
	size_t size() const { return size_; }
	size_t capacity() const { return capacity_; }
	void push_back(const int& elem) {
		if (size() == capacity()) {
			size_t new_capacity = capacity() == 0 ? 1 : capacity() + capacity() / 2;
			int* new_data = new int[new_capacity];
			for (int i = 0; i != capacity(); ++i) {
				new_data[i] = std::move(data[i]);
			}
			for (int i = 0; i != capacity(); ++i) {
				data[i].~int();
			}
			if (data != nullptr) {
				delete[] data;
			}
			data = new_data;
			capacity_ = new_capacity;
		}
		data[size()] = elem;
		size_++;
	}

private:
	int* data = nullptr;
	size_t capacity_ = 0;
	size_t size_ = 0;
};