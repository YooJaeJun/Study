#include <iostream>
using namespace std;

template <typename T>
class Queue
{
private:
	T* arr;
	int front = -1;
	int rear = -1;
	int capacity = 2;

public:
	int size = 0;

public:
	Queue()
	{
		arr = new T[capacity];
	}

	bool isFull()
	{
		return size == capacity;
	}

	bool isEmpty()
	{
		return size == 0;
	}

	void enqueue(T data)
	{
		if (isFull())
		{
			capacity *= 2;
			T* temp = new T[capacity];
			copy(arr, arr + size + 1, temp);
			delete[] arr;
			arr = new T[capacity];
			copy(temp, temp + size + 1, arr);
			cout << "²Ë Â÷¼­ ¿ë·® ´Ã¸². capacity " << capacity / 2 << " => " << capacity << '\n';
		}
		rear = (rear + 1) % capacity;
		arr[rear] = data;
		size++;
	}

	T dequeue()
	{
		if (isEmpty())
		{
			cout << "ºñ¾îÀÖ¾î¼­ »¬ ¼ö ¾øÀ½\n";
			exit(1);
		}
		front = (front + 1) % capacity;
		size--;
		return arr[front];
	}

	T peep()
	{
		if (isEmpty())
		{
			return nullptr;
		}
		size--;
		return arr[(front + 1) % capacity];
	}

	void test()
	{
		for (int i = 0; i < size; i++) cout << arr[i] << ' ';
		cout << '\n';
	}
};

int main()
{
	Queue<int> q;
	cout << "q size: " << q.size << "\n\n";

	for (int i = 0; i < 5; i++)
	{
		q.enqueue(i);
		q.test();
	}
	cout << "q size: " << q.size << "\n\n";

	while (!q.isEmpty())
	{
		cout << q.dequeue() << ' ';
	}
	cout << '\n';
	cout << "q size: " << q.size << "\n\n";
}