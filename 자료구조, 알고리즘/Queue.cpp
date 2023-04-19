// Node.h
#pragma once
#include <iostream>

using Item = int;

struct Node
{
	Item item;
	struct Node* next;
};

// Queue.h
#pragma once
class Queue
{
private:
	struct Node 
	{ 
		Item item; 
		struct Node* next; 
	};
	enum { Q_SIZE = 10 };

	Node* front;
	Node* rear;
	int items;
	const int qsize;

public:
	Queue(int qs = Q_SIZE);
	~Queue();
	bool isempty() const;
	bool isfull() const;
	int queuecount() const;
	bool enqueue(const Item& item);
	bool dequeue(Item& item);

private:
	Queue(const Queue& q) : qsize(0) {}
	Queue& operator=(const Queue& q) { return *this; }
};


// Queue.cpp
// #include "Queue.h"

Queue::Queue(int qs) : qsize(qs)
{
	front = rear = nullptr;
	items = 0;
}

bool Queue::enqueue(const Item& item)
{
	if (isfull())
		return false;
	Node* add = new Node;

	add->item = item;
	add->next = nullptr;
	items++;
	if (front == nullptr)
		front = add;
	else
		rear->next = add;
	rear = add;
	return true;
}

bool Queue::dequeue(Item& item)
{
	if (front == nullptr)
		return false;
	item = front->item;
	items--;
	Node* temp = front;
	front = front->next;
	delete temp;
	if (items == 0)
		rear = nullptr;
	return true;
}

Queue::~Queue()
{
	Node* temp;
	while (front != nullptr)
	{
		temp = front;
		front = front->next;
		delete temp;
	}
}