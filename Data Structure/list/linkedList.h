#pragma once
#include "nodeList.h"
class linkedList {
	node org;	// 헤드 노드(헤드 포인터가 아님)
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
	// pos번째 항목 반환
	node* getEntry(int pos) {
		node* n = &org;
		for (int i = -1; i < pos; i++, n = n->getLink()) {
			if (n == nullptr) {
				break;
			}
		}
		return n;
	}
	// 리스트의 어떤 위치에 항목 삽입
	void insert(int pos, node* n) {
		node* prev = getEntry(pos - 1);
		if (prev != nullptr) {
			prev->insertNext(n);
		}
	}
	// 리스트의 어떤 위치의 항목 삭제
	node* remove(int pos) {
		node* prev = getEntry(pos - 1);
		return prev->removeNext();
	}
	// 탐색 함수
	node* find(int val) {
		for (node* p = getHead(); p != nullptr; p = p->getLink()) {
			if (p->hasData(val)) {
				return p;
			}
		}
		return nullptr;
	}
	// 리스트의 pos번째 노드를 다른 노드로 교체
	void replace(int pos, node* n) {
		node* prev = getEntry(pos - 1);
		if (prev != nullptr) {
			delete prev->removeNext();
			prev->insertNext(n);
		}
	}
	// 리스트의 항목 개수 반환
	int size() {
		int count = 0;
		for (node* p = getHead(); p != nullptr; p = p->getLink()) {
			count++;
		}
		return count;
	}

	void display() {
		printf("[전체 항목 수 = %d : ", size());
		for (node* p = getHead(); p != nullptr; p = p->getLink()) {
			p->display();
		}
		printf("\n");
	}
};