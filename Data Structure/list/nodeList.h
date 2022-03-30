#pragma once
#include <iostream>
class node {
	node* link;
	int data;
public:
	node(int val = 0) : data(val), link(nullptr) {}
	node* getLink() { return link; }
	void setLink(node* next) { link = next; }
	void display() { printf("<%2d>", data); }
	bool hasData(int val) { return data == val; }

	void insertNext(node* n) {
		if (n != nullptr) {
			n->link = link;
			link = n;
		}
	}
	node* removeNext() {
		node* removed = link;
		if (removed != nullptr) {
			link = removed->link;
		}
		return removed;
	}
};