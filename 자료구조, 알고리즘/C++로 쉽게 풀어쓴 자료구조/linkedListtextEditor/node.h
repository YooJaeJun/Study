#pragma once
#include "line.h"
class node : public line {
	node* link;
public:
	node(char* str) : line(str), link(nullptr) {}
	void setLink(node* p) { link = p; }
	node* getLink() { return link; }
	void insertNext(node* p) {
		if (p != nullptr) {
			p->link = link;
			link = p;
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