#include <iostream>
using namespace std;

const int maxn = 10;

typedef int element;

class ArrayList
{
public:
	element buf[20];
	int size;
public:
	void init();
	bool isEmpty();
	bool isFull();
	void print();
	bool isInList(element other);
	int whereIsInList(element other);
	int getSize();
	void addLast(element other);
	void addPos(int pos, element other);
	void remove(element other);
	int searchLinear(element other);
	int searchLinearOnSorted(element other);
	int searchBinaryOnSorted(element other);
	int searchBinaryOnSortedRecursively(element other, int first, int last);
	friend int cmpfunc4Search(const void* a, const void* b);
	friend bool searchByC(ArrayList* list, element other);
	void sort();
	friend int cmpfunc4Sort(const void* a, const void* b);
	friend void SortByC(ArrayList* list);
};

void ArrayList::init()
{
	size = 0;
}

bool ArrayList::isEmpty()
{
	return size == 0;
}

bool ArrayList::isFull()
{
	return size == maxn;
}

void ArrayList::print()
{
	for (int i = 0; i < size; i++) cout << buf[i] << ' ';
	cout << '\n';
}

bool ArrayList::isInList(element other)
{
	for (int i = 0; i < size; i++) if (buf[i] == other) return true;
	return false;
}

int ArrayList::whereIsInList(element other)
{
	for (int i = 0; i < size; i++) if (buf[i] == other) return i;
	return -1;
}

int ArrayList::getSize()
{
	return size;
}

void ArrayList::addLast(element other)
{
	if (!isFull())
	{
		buf[size++] = other;
	}
	else cout << "Error: List Full\n";
}

void ArrayList::addPos(int pos, element other)
{
	if (!isFull() && pos >= 0 && pos <= size)
	{
		for (int i = size - 1; i >= pos; i--)
		{
			buf[i + 1] = buf[i];
		}
		buf[pos] = other;
		size++;
	}
	else cout << "Errow: List Full or Position Error\n";
}

void ArrayList::remove(element other)
{
	if (!isInList(other))
	{
		cout << "Error: not exists\n";
		return;
	}
	if (!isEmpty())
	{
		for (int i = 0; i < size; i++)
		{
			if (buf[i] == other)
			{
				for (int j = i + 1; j < size; j++)
				{
					buf[j - 1] = buf[j];
				}
				size--;
				return;
			}
		}
	}
	else cout << "Error: List Empty\n";
}

int ArrayList::searchLinear(element other)
{
	for (int i = 0; i < size; i++)
	{
		if (buf[i] == other) return i;
	}
	return -1;
}

int ArrayList::searchLinearOnSorted(element other)
{
	for (int i = 0; i < size; i++)
	{
		if (buf[i] == other) return i;
		else if (buf[i] > other) return -1;
	}
	return -1;
}

int ArrayList::searchBinaryOnSorted(element other)
{
	int first = 0;
	int last = size - 1;
	while (first <= last)
	{
		int middle = (first + last) / 2;

		if (buf[middle] == other) return middle;
		else if (buf[middle] < other) first = middle + 1;
		else last = middle - 1;
	}
	return -1;
}

int ArrayList::searchBinaryOnSortedRecursively(element other, int first, int last)
{
	if (last >= first)
	{
		int middle = (first + last) / 2;
		if (buf[middle] == other) 
			return middle;
		else if (buf[middle] < other) 
			return searchBinaryOnSortedRecursively(other, middle + 1, last);
		else 
			return searchBinaryOnSortedRecursively(other, first, middle - 1);
	}
	return -1;
}


int cmpfunc4Search(const void* a, const void* b)
{
	return (*(int*)a - *(int*)b);
}
bool searchByC(ArrayList* list, element other)
{
	int* result = (int*)bsearch(&other, list->buf, list->size, sizeof(int), cmpfunc4Search);
	return result;
}

void ArrayList::sort()
{
	element temp;

	if (isEmpty()) return;

	for (int i = 0; i < size - 1; i++)
	{
		int jmin = i;
		for (int j = i + 1; j < size; j++)
		{
			if (buf[j] < buf[jmin])
			{
				jmin = j;
			}
		}
		if (jmin != i)
		{
			temp = buf[i];
			buf[i] = buf[jmin];
			buf[jmin] = temp;
		}
	}
}

int cmpfunc4Sort(const void* a, const void* b)
{
	return (*(int*)a > *(int*)b);
}

void SortByC(ArrayList* list)
{
	qsort(list->buf, list->size, sizeof(int), cmpfunc4Sort);
}


int main()
{
	ArrayList list;
	list.init();
	list.print();

	list.addLast(1);
	list.addLast(2);
	list.addLast(3);
	list.print();

	list.remove(3);
	list.print();

	list.addPos(0, 8);
	list.print();


	list.remove(1);
	list.addLast(13);
	list.addLast(33);
	list.addLast(37);
	list.addLast(5);
	list.addLast(21);

	list.print();

	cout << "2는 " << list.searchLinear(2) << "번째.\n";

	SortByC(&list);
	list.print();
	cout << "2는 " << list.searchLinearOnSorted(2) << "번째.\n";
	cout << "2는 " << list.searchBinaryOnSorted(2) << "번째.\n";
	cout << "2는 " << list.searchBinaryOnSortedRecursively(2, 0, list.size) << "번째.\n";

	cout << "37은 " << list.searchLinearOnSorted(37) << "번째.\n";
	cout << "37은 " << list.searchBinaryOnSorted(37) << "번째.\n";
	cout << "37은 " << list.searchBinaryOnSortedRecursively(37, 0, list.size) << "번째.\n";

	if (searchByC(&list, 2)) cout << "2는 존재함.\n";
	else cout << "2는 미존재.\n";
}