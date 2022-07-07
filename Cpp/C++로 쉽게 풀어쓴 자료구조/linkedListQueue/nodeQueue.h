#pragma once
#include <cstdio>
#include "student.h"

class nodeQueue {
	nodeQueue* link;
	int data;
public:
	nodeQueue(int val = 0) : data(val), link(nullptr) {}
	nodeQueue* getLink() { return link; }
	void setLink(nodeQueue* next) { link = next; }
	void display() { printf("<%d>", data); }
};

class node : public student {
	node* link;
public:
	node(int id, const char* name, const char* dept)
		: student(id, name, dept) {
		link = nullptr;
	}
	~node() {}
	node* getLink() { return link; }
	void setLink(node* p) { link = p; }
};
