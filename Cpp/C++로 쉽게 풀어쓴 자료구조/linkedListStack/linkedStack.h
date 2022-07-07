#pragma once
#include "nodeStack.h"

class linkedStack {
	node* top;
public:
	linkedStack() { top = nullptr; }
	~linkedStack() { while (!isEmpty()) delete pop(); }
	bool isEmpty() { return top == nullptr; }
	void push(node* p) {
		if (isEmpty()) top = p;
		else {
			p->setLink(top);
			top = p;
		}
	}
	node* pop() {
		if (isEmpty()) { return nullptr; }
		node* p = top;
		top = top->getLink();
		return p;
	}
	node* peek() { return top; }
	void display() {
		printf("[LinkedStack]\n");
		for (node* p = top; p != nullptr; p = p->getLink()) {
			p->display();
		}
		printf("\n");
	}
};