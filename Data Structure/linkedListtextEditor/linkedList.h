#pragma once
#include "node.h"
class linkedList {
protected:
	node org = 0;
public:
	linkedList() { }
	~linkedList() { clear(); }
	void clear() {
		while (false == isEmpty()) {
			delete remove(0);
		} 
	}
	node* getHead() { return org.getLink(); }
	bool isEmpty() { return getHead() == nullptr; }
	node* getEntry(int pos) {
		node* n = &org;
		for (int i = -1; i < pos; i++, n = n->getLink()) {
			if (n == nullptr) { break; }
		}
		return n;
	}
	void insert(int pos, node* n) {
		node* prev = getEntry(pos - 1);
		if (prev != nullptr) {
			prev->insertNext(n);
		}
	}
	node* remove(int pos) {
		node* prev = getEntry(pos - 1);
		return prev->removeNext();
	}
	node* find(char* str) {
		for (node* p = getHead(); p != nullptr; p = p->getLink()) {
			if (p->hasData(str)) {
				return p;
			}
		}
		return nullptr;
	}
	void replace(int pos, node* n) {
		node* prev = getEntry(pos - 1);
		if (prev != nullptr) {
			delete prev->removeNext();
			prev->insertNext(n);
		}
	}
	int size() {
		int count = 0;
		for (node* p = getHead(); p != nullptr; p = p->getLink()) {
			count++;
		}
		return count;
	}
};