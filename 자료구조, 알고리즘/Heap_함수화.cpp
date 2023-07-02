#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class MaxHeap
{
public:
	void Push(const int x)
	{
		int i = ++size;

		while ((i != 1) && (x > Parent(i)))
		{
			heap[i] = Parent(i);
			Up(i);
		}

		heap[i] = x;
	}
	int Pop()
	{
		int parent = 1;
		int child = 2;
		const int ret = heap[1];
		const int end = heap[size];
		size--;

		while (child <= size)
		{
			if (IsRightBigger(child))
				child++;

			if (end >= heap[child])
				break;

			Down(parent, child);
		}
		heap[parent] = end;
		return ret;
	}
	int Parent(const int i) const
	{
		return heap[i / 2];
	}
	bool IsRightBigger(int child) const
	{
		return (child < size) && (heap[child] < heap[child + 1]);
	}
	void Up(int& i) const
	{
		i /= 2;
	}
	void Down(int& parent, int& child)
	{
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	bool Empty() const
	{
		return size == 0;
	}
	void Print(const int x) const
	{
		cout << x << '\n';
	}

private:
	int heap[100'001] = { 0, };
	int size = 0;
};

int main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	MaxHeap heap;
	int n;
	cin >> n;
	int input;

	while (n--)
	{
		cin >> input;
		if (input == 0)
		{
			if (heap.Empty())
				cout << 0 << '\n';
			else
				heap.Print(heap.Pop());
		}
		else
			heap.Push(input);
	}


	return 0;
}