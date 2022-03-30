#pragma once
#include "nodeQueue.h"
class studentQueue {
	node* front;
	node* rear;
public:
	studentQueue() { front = nullptr; rear = nullptr; }
	~studentQueue() {
		while (!isEmpty()) { front = nullptr; }
	}
	bool isEmpty() {
		return front == nullptr;
	}
	void enqueue(node* n) {
		if (isEmpty()) { front = rear = n; }
		else {
			rear->setLink(n);
			rear = n;
		}
	}
	node* dequeue() {
		if (isEmpty()) { return nullptr; }
		node* p = front;
		front = front->getLink();
		if (front == nullptr) { rear = nullptr; }
		return p;
	}
	node* peek() { return front; }
	void display() {
		printf("[전체 학생 정보]\n");
		for (node* p = front; p != nullptr; p = p->getLink()) {
			p->display();
		}
		printf("\n");
	}
};