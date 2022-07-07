#pragma once
#include "nodeQueue.h"

class linkedQueue {
	node* front;
	node* rear;
public:
	linkedQueue() : front(nullptr), rear(nullptr) {}
	~linkedQueue() { while (!isEmpty()) delete dequeue(); }
	bool isEmpty() { return front == nullptr; }

	void enqueue(node* p) {
		if (isEmpty()) { front = rear = p; }
		else {
			rear->setLink(p);
			rear = p;
		}
	}
	node* dequeue() {
		if (isEmpty()) return nullptr;
		node* p = front;
		front = front->getLink();
		if (front == nullptr) { rear = nullptr; }
		return p;
	}
	node* peek() { return front; }
	void display() {
		printf("[Å¥ ³»¿ë] : ");
		for (node* p = front; p != nullptr; p = p->getLink()) {
			p->display();
		}
		printf("\n");
	}
};