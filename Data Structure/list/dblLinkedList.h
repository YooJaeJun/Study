#pragma once
#include "node2List.h"
class dblLinkedList {
	node2 org;	// 헤드 노드
public:
	dblLinkedList() : org(0) { }
	~dblLinkedList() {
		while (false == isEmpty()) {
			delete remove(0);
		}
	}
	node2* getHead() { return org.getNext(); }
	bool isEmpty() { return getHead() == nullptr; }
	
	node2* getEntry(int pos) {
		node2* n = &org;
		for (int i = -1; i < pos; i++, n = n->getNext()) {
			if (n == nullptr) {
				break;
			}
		}
		return n;
	}
	void insert(int pos, node2* n) {
		node2* prev = getEntry(pos - 1);
		if (prev != nullptr) {
			prev->insertNext(n);
		}
	}
	//
	node2* remove(int pos) {
		node2* n = getEntry(pos);
		return n->remove();
	}
	node2* find(int val) {
		for (node2* p = getHead(); p != nullptr; p = p->getNext()) {
			if (p->hasData(val)) {
				return p;
			}
		}
		return nullptr;
	}
	//
	void replace(int pos, node2* n) {
		node2* prev = getEntry(pos - 1);
		if (prev != nullptr) {
			delete prev->getNext()->remove();
			prev->insertNext(n);
		}
	}
	int size() {
		int count = 0;
		for (node2* p = getHead(); p != nullptr; p = p->getNext()) {
			count++;
		}
		return count;
	}
	void display() {
		printf("[이중연결리스트 항목 수 = %d]", size());
		for (node2* p = getHead(); p != nullptr; p = p->getNext()) {
			p->display();
		}
		printf("\n");
	}
	void clear() {
		while (false == isEmpty()) {
			delete remove(0);
		}
	}
};