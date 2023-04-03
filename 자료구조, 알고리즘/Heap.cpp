#include <iostream>
using namespace std;

const int MAX = 10;

template<typename T>
class MaxHeap
{
public:
	void Insert(T item)
	{
		size++;
		int i = size;

		while (i != 1/*��Ʈ��尡 �ƴϰ�*/ && item > heap[i / 2]/*�θ𺸴�ũ��*/)
		{
			heap[i] = heap[i / 2];
			i /= 2;
		}
		heap[i] = item;
	}

	T Delete()
	{
		T ret = heap[1];
		T last = heap[size];
		size--;

		int parent = 1;
		int child = 2;

		while (child <= size)
		{
			if (child < size && heap[child] < heap[child + 1])	// ����or������ �ڽ� �� ū �� ����
				child++;

			if (last >= heap[child])	// �ڽĺ��� ������ ��尡 �� ũ�� ����
				break;

			heap[parent] = heap[child];
			parent = child;
			child *= 2;
		}

		heap[parent] = last;

		return ret;
	}

	void Sort()
	{
		MaxHeap temp;

		for (int i=1; i<=size; i++)
			temp.Insert(heap[i]);

		for (int i = size; i >= 0; i--)
			heap[i] = temp.Delete();
	}

	void Print() const
	{
		for (int i = 1; i <= size; i++)
			cout << heap[i] << ' ';
		cout << endl;
	}

private:
	T heap[MAX + 1];	// 1���� root���
	int size = 0;
};


template<typename T>
class MinHeap
{
public:
	void Insert(T item)
	{
		size++;
		int i = size;

		while (i != 1 && heap[i / 2] > item)
		{
			heap[i] = heap[i / 2];
			i /= 2;
		}
		heap[i] = item;
	}

	T Delete()
	{
		T ret = heap[1];
		T last = heap[size];
		size--;

		int parent = 1;
		int child = 2;

		while (child <= size)
		{
			if (child < size && heap[child] > heap[child + 1])
				child++;

			if (last <= heap[child])
				break;

			heap[parent] = heap[child];
			parent = child;
			child *= 2;
		}

		heap[parent] = last;

		return ret;
	}

	void Sort()
	{
		MinHeap temp;

		for (int i = 1; i <= size; i++)
			temp.Insert(heap[i]);

		//for (int i = size; i >= 0; i--)
		//	heap[i] = temp.Delete();
		for (int i = 1; i <= size; i++)
			heap[i] = temp.Delete();
	}

	void Print() const
	{
		for (int i = 1; i <= size; i++)
			cout << heap[i] << ' ';
		cout << endl;
	}

private:
	T heap[MAX + 1];
	int size = 0;
};


int main()
{
	MinHeap<int> h;
	h.Insert(1);
	h.Insert(5);
	h.Insert(3);
	h.Insert(4);
	h.Insert(7);
	h.Insert(2);
	h.Insert(9);
	h.Insert(8);

	h.Print();

	h.Delete();
	h.Delete();

	h.Print();


	h.Sort();

	h.Print();


	return 0;
}