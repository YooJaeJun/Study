#include <iostream>
#include <cassert>
using namespace std;

template <typename T>
class Queue
{
private:
	enum { maxSize = 10 };

private:
	struct Node
	{
		T item;
		Node* next;
	};
	Node* front;
	Node* rear;
	int size;

public:
	Queue()
		: front(nullptr), rear(nullptr), size(0)
	{}
	~Queue()
	{}
	bool IsEmpty() const
	{
		if (front)
			return false;
		return true;
	}
	void Push(const T& item)
	{
		Node* add = new Node;

		add->item = item;
		add->next = nullptr;
		size++;

		if (front == nullptr)
			front = add;
		else
			rear->next = add;

		rear = add;
	}
	T Pop()
	{
		if (IsEmpty())
			assert(false);

		T item = front->item;
		size--;

		Node* temp = front;
		front = front->next;
		delete temp;

		if (size == 0)
			rear = nullptr;

		return item;
	}
};

int main()
{
	Queue<int> q;
	q.Push(1);
	q.Push(5);
	q.Push(3);

	for (int i = 0; i < 3; i++)
	{
		cout << q.Pop() << " Á¦°Å\n";
	}
}
