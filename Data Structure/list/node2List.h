#pragma once
#include <iostream>
class node2 {
	node2* prev;
	node2* next;
	int data;
public:
	node2(int val = 0) : data(val), prev(nullptr), next(nullptr) {}
	node2* getPrev() { return prev; }
	node2* getNext() { return next; }
	void setPrev(node2* p) { prev = p; }
	void setNext(node2* n) { next = n; }
	void display() { printf("<%d>", data); }
	bool hasData(int val) { return data == val; }
	
	void insertNext(node2* n) {
		if (n != nullptr) {
			n->prev = this;
			n->next = next;
			if (next != nullptr) { next->prev = n; }
			next = n;
		}
	}
	node2* remove() {
		if (prev != nullptr) { prev->next = next; }
		if (next != nullptr) { next->prev = prev; }
		return this;
	}
};