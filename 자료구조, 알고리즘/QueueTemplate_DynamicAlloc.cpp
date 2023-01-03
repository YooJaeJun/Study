#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <cassert>

template<typename T>
class Queue
{
private:
	int front_;
	int rear_;
	int count_;
	int capacity_;
	T* data_;

public:
	Queue()
	{
		front_ = 0;
		rear_ = 1;
		count_ = 0;
		capacity_ = 2;
		data_ = new T[capacity_];
	}
	~Queue()
	{
		Clear();
	}
	void Push(T value)
	{
		if (Full())
		{
			T* temp = new T[capacity_];
			for (int i = front_; i < capacity_; i++)
			{
				temp[i] = data_[i];
			}

			Clear();

			capacity_ *= 2;
			data_ = new T[capacity_];

			for (int i = 0; i < capacity_ / 2; i++)
			{
				data_[i] = temp[i];
			}
			delete[] temp;
		}

		rear_ = (rear_ + 1) % capacity_;
		data_[rear_] = value;
		count_++;
	}
	T Pop()
	{
		if (Empty())
		{
			std::cout << "Queue가 비어있습니다.";
			assert(false);
		}
		
		int ret = data_[front_];
		front_ = (front_ + 1) % capacity_;
		count_--;
		return ret;
	}
	T Front() const { return data_[front_]; }
	void Clear()
	{
		delete[] data_;
	}
	bool Empty() const { return count_ == 0; }
	bool Full() const { return count_ == capacity_; }
};

void Solution()
{
	Queue<int> q;
	q.Push(11);
	q.Push(22);
	q.Push(33);
	q.Push(44);
	q.Push(55);

	q.Pop();

	while (!q.Empty())
	{
		std::cout << q.Pop() << ' ';
	}
}

int main()
{
	Solution();
	_CrtDumpMemoryLeaks();
	return 0;
}