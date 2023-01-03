#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <cassert>

template<typename T>
class Stack
{
private:
	int size_;
	int capacity_;
	int* data_;

public:
	Stack()
	{
		size_ = 0;
		capacity_ = 2;
		data_ = new T[capacity_];
	}
	Stack(int size)
	{
		size_ = size;
		capacity_ = size_ * 2 + 1;
		data_ = new T[capacity_];
	}
	~Stack()
	{
		Clear();
	}
	void Push(T value)
	{
		if (capacity_ <= size_)
		{
			capacity_ *= 2;

			int* temp = new T[size_];
			for (int i = 0; i < size_; i++)
			{
				temp[i] = data_[i];
			}
			
			Clear();

			data_ = new T[capacity_];
			
			for (int i = 0; i < size_; i++)
			{
				data_[i] = temp[i];
			}

			delete[] temp;
		}

		data_[size_] = value;
		size_++;
	}
	T Pop()
	{
		if (size_ == 0)
		{
			std::cout << "Stack이 비었습니다.\n";
			assert(false);
		}

		data_[size_] = 0;
		size_--;
		return Top();
	}
	void Clear()
	{
		delete[] data_;
	}
	bool Empty() const { return size_ == 0; }
	T Top() const { return data_[size_]; }
};

void Solution()
{
	Stack<int> st;
	st.Push(11);
	st.Push(22);
	st.Push(33);
	st.Push(44);
	st.Push(55);

	while (!st.Empty())
	{
		std::cout << st.Pop() << ' ';
	}
	st.Push(66);
	st.Push(77);
	while (!st.Empty())
	{
		std::cout << st.Pop() << ' ';
	}
}

int main()
{
	Solution();
	_CrtDumpMemoryLeaks();
	return 0;
}