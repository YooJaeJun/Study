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
	int getSize();
	void addPos(int pos, element data);
	void addFirst(element data);
	void addLast(element data);
	Node* create(element e, Node* next);
	void remove(element data);
	void dispose();	// 모두 삭제
	bool isEmpty();
	bool isInList(element elem);
	void print();
};

void LinkedList::init()
{
	head = nullptr;
	size = 0;
}

int LinkedList::getSize()
{
	return size;
}

void LinkedList::addPos(int pos, element data)
{
	if (pos > size + 1 || pos < 1)
	{
		cout << "Error: pos is out of range\n";
		exit(1);
	}
	else
	{
		Node* newNode = create(data, nullptr);

		if (pos == 1)
		{
			newNode->next = head;
			head = newNode;
		}
		else
		{
			Node* temp = head;
			for (int i = 1; i < pos - 1; i++)
				temp = temp->next;

			newNode->next = temp->next;
			temp->next = newNode;
		}
		size++;
	}
}

void LinkedList::addFirst(element data)
{
	addPos(1, data);
}

void LinkedList::addLast(element data)
{
	addPos(size + 1, data);
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

void LinkedList::remove(element data)
{
	Node* cursor = head;
	Node* prev = nullptr;

	if (cursor->data == data)
	{
		head = cursor->next;
		free(cursor);
		size--;
	}
	else
	{
		while (cursor != nullptr)
		{
			if (cursor->data == data) break;
			prev = cursor;
			cursor = cursor->next;
		}
		if (cursor != nullptr)
		{
			prev->next = cursor->next;
			free(cursor);
			size--;
		}
	}
}

void LinkedList::dispose()
{
	Node* temp;
	Node* cursor = head;
	head = nullptr;

	while (cursor != nullptr)
	{
		temp = cursor->next;
		free(cursor);
		cursor = temp;
	}
	size = 0;
}

bool LinkedList::isEmpty()
{
	return head == nullptr;
}

bool LinkedList::isInList(element elem)
{
	Node* cursor = head;
	while (cursor != nullptr)
	{
		if (cursor->data == elem) return true;
		cursor = cursor->next;
	}
	return false;
}

void LinkedList::print()
{
	Node* current = head;
	while (current != nullptr)
	{
		cout << "--> " << current->data << ' ';
		current = current->next;
	}
	cout << '\n';
}


int main()
{
	LinkedList list;

	list.init();
	list.print();

	list.addFirst(10);
	list.print();

	list.addFirst(20);
	list.print();

	list.addPos(1, 30);
	list.print();

	list.addPos(2, 40);
	list.print();

	list.addLast(50);
	list.print();

	list.remove(20);
	list.print();

	list.remove(10);
	list.print();

	list.remove(50);
	list.print();

	list.remove(30);
	list.print();

	list.addFirst(90);
	list.print();

	list.addPos(10, 80);
	list.print();

	list.dispose();
	list.print();
}