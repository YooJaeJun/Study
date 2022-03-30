#pragma once
#include <iostream>
#include "threadedBinNode.h"
class threadedBinTree {
	threadedBinNode* root;
public:
	threadedBinTree() : root(nullptr) {}
	void setRoot(threadedBinNode* node) { root = node; }
	bool isEmpty() { return root == nullptr; }

	// 스레드 방싞의 inorder 방문 함수
	void threadedInorder() {
		if (false == isEmpty()) {
			printf("스레드 이진트리: ");
			threadedBinNode* q = root;
			while (q->getLeft()) {
				q = q->getLeft();	// 가장 왼쪽노드로 이동
			}
			do {
				printf("%c ", q->getData());
				q = findSuccessor(q);	// 후속자 함수 호출
			} while (q);
			printf("\n");
		}
	}

	threadedBinNode* findSuccessor(threadedBinNode* p) {
		threadedBinNode* q = p->getRight();	// 오른쪽 자식 포인터

		// 만약 오른쪽 포인터가 nullptr이거나 스레드이면, 오른쪽 포인터를 반환
		if (q == nullptr || p->bThread) { return q; }
		// 만약 오른쪽 자식이면 다시 가장 왼쪽 노드로 이동
		while (q->getLeft() != nullptr) { q = q->getLeft(); }
		return q;
	}
};