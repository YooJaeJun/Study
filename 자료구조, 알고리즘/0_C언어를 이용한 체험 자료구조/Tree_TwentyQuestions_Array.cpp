#include <iostream>
#include <string>
using namespace std;

template <typename T>
class BinaryTree
{
public:
	T* data;

public:
	int size = 0;
	int capacity = 2;

public:
	BinaryTree()
	{
		data = new T[capacity];
	}
	~BinaryTree()
	{
		delete[] data;
	}

	int leftChild(const int pos)
	{
		if (pos * 2 <= size) return pos * 2;
		else return 0;
	}

	int rightChild(const int pos)
	{
		if (pos * 2 + 1 <= size) return pos * 2 + 1;
		else return 0;
	}

	int parent(const int pos)
	{
		if (pos == 1) return 0;
		else return pos / 2;
	}

	void insert(const T e)
	{
		if (size >= capacity - 1)
		{
			cout << "capacity 늘림 " << capacity << " => " << capacity * 2 << '\n';
			capacity *= 2;
			T* temp = new T[capacity];
			copy(data, data + size + 1, temp);
			delete[] data;
			data = new T[capacity];
			copy(temp, temp + size + 1, data);
			delete[] temp;
		}

		data[++size] = e;
	}

	int value(int pos)
	{
		if (pos >= 0 && pos <= size)
		{
			return data[pos];
		}
	}

	void graphvizPrint(int node)
	{
		if (node > size) return;
		if (node != 1) cout << data[node / 2] << " => " << data[node] << '\n';

		graphvizPrint(node * 2);
		graphvizPrint(node * 2 + 1);
	}
};

/*
int main()
{
	BinaryTree<int> bt;

	for (int i = 1; i <= 8; i++)
	{
		bt.insert(i);
	}

	bt.graphvizPrint(1);
	cout << '\n';

	cout << "root is " << bt.value(1) << '\n';

	cout << "left: " << bt.value(bt.leftChild(1)) << " right: " << bt.value(bt.rightChild(1)) << '\n';
	cout << "left: " << bt.value(bt.leftChild(2)) << " right: " << bt.value(bt.rightChild(2)) << '\n';
	cout << "left: " << bt.value(bt.leftChild(3)) << " right: " << bt.value(bt.rightChild(3)) << '\n';
	cout << "left: " << bt.value(bt.leftChild(4)) << " right: " << bt.value(bt.rightChild(4)) << '\n';
	cout <<  "5의 부모는 " << bt.value(bt.parent(5)) << '\n';

	return 0;
}
*/

class Question
{
public:
	bool	isQuestion;	// true: 비 단말 노드
	string	msg;		// 내부 노드이면 질문, 단말 노드이면 결론

public:
	friend ostream& operator<<(ostream& os, const Question& other)
	{
		os << other.msg << '\n';
		return os;
	}
};

int main()
{
	BinaryTree<Question> bt;

	Question trainData[] = {
		{ true, "is animal? " },
		{ true, "has 2 legs? " },
		{ true, "is tall? " },
		{ true, "can fly? " },
		{ true, "is larger than human? " },
		{ true, "has needle leaf? " },
		{ true, "is flower? " },
		{ false, "It is a bird. " },
		{ false, "It is a chichken. " },
		{ false, "It is an elephant. " },
		{ false, "It is a dog. " },
		{ false, "It is a pine tree. " },
		{ false, "It is a bamboo. " },
		{ false, "It is an orchid. " },
		{ false, "It is an grass. " },
	};

	for (int i = 0; i < 15; i++)
	{
		bt.insert(trainData[i]);
	}

	bt.graphvizPrint(1);
	cout << '\n';

	int question = 1;
	string answer;

	do {
		cout << bt.data[question].msg;
		cout << "if YES, Enter 'y' or 'n': ";

		getline(cin, answer);

		if (answer == "y")
		{
			question = bt.leftChild(question);
		}
		else
		{
			question = bt.rightChild(question);
		}

	} while (bt.data[question].isQuestion);

	cout << bt.data[question].msg << '\n';
}