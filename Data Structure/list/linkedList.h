#pragma once
#include "nodeList.h"
class linkedList {
	node org;	// ��� ���(��� �����Ͱ� �ƴ�)
public:
	linkedList() : org(0) {}
	~linkedList() { clear(); }
	void clear() { 
		while (false == isEmpty()) {
			delete remove(0);
		}
	}
	node* getHead() { return org.getLink(); }
	bool isEmpty() { return getHead() == nullptr; }
	// pos��° �׸� ��ȯ
	node* getEntry(int pos) {
		node* n = &org;
		for (int i = -1; i < pos; i++, n = n->getLink()) {
			if (n == nullptr) {
				break;
			}
		}
		return n;
	}
	// ����Ʈ�� � ��ġ�� �׸� ����
	void insert(int pos, node* n) {
		node* prev = getEntry(pos - 1);
		if (prev != nullptr) {
			prev->insertNext(n);
		}
	}
	// ����Ʈ�� � ��ġ�� �׸� ����
	node* remove(int pos) {
		node* prev = getEntry(pos - 1);
		return prev->removeNext();
	}
	// Ž�� �Լ�
	node* find(int val) {
		for (node* p = getHead(); p != nullptr; p = p->getLink()) {
			if (p->hasData(val)) {
				return p;
			}
		}
		return nullptr;
	}
	// ����Ʈ�� pos��° ��带 �ٸ� ���� ��ü
	void replace(int pos, node* n) {
		node* prev = getEntry(pos - 1);
		if (prev != nullptr) {
			delete prev->removeNext();
			prev->insertNext(n);
		}
	}
	// ����Ʈ�� �׸� ���� ��ȯ
	int size() {
		int count = 0;
		for (node* p = getHead(); p != nullptr; p = p->getLink()) {
			count++;
		}
		return count;
	}

	void display() {
		printf("[��ü �׸� �� = %d : ", size());
		for (node* p = getHead(); p != nullptr; p = p->getLink()) {
			p->display();
		}
		printf("\n");
	}
};