#include <iostream>
using namespace std;

typedef int element;

class Node
{
public:
	element data;
	Node* next;
};

class LinkedList
{
public:
	Node* head;
	int size;
public:
	void init();
	bool isEmpty();
	void print();
	bool isInList(element elem);
	Node* create(element e, Node* next);
	void add(element data);
};

void LinkedList::init()
{
	head = nullptr;
	size = 0;
}

bool LinkedList::isEmpty()
{
	return head == nullptr;
}

void LinkedList::print()
{
	if (head == nullptr)
	{
		cout << "List is empty\n";
		return;
	}

	Node* cursor = head;
	do {
		cout << "--> " << cursor->next->data;
		cursor = cursor->next;
	} while (cursor != head);
	cout << '\n';
}

bool LinkedList::isInList(element elem)
{
	if (head == nullptr) return false;

	Node* cursor = head;
	do {
		if (cursor->next->data == elem) return true;
		cursor = cursor->next;
	} while (cursor != head);
	return false;
}

Node* LinkedList::create(element e, Node* next)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == nullptr)
	{
		cout << "Error: creating a new node.\n";
		exit(1);
	}
	newNode->data = e;
	newNode->next = next;
	return newNode;
}

void LinkedList::add(element data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == nullptr)
	{
		cout << "Error: Memory Allocation Error\n";
		exit(0);
	}
	newNode->data = data;

	if (head == nullptr)
	{
		head = newNode;
		newNode->next = newNode;
	}
	else
	{
		newNode->next = head->next;
		head->next = newNode;
		head = newNode;
	}
	size++;
}


int main()
{
	int data[] = { 1,2,3,4,5,6,7,8,9,10 };
	LinkedList list;
	list.init();
	list.print();
	for (int i = 0; i < sizeof(data) / sizeof(int); i++)
	{
		list.add(data[i]);
		list.print();
	}
}
