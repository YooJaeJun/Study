#pragma once
#include <iostream>
#include "threadedBinNode.h"
class threadedBinTree {
	threadedBinNode* root;
public:
	threadedBinTree() : root(nullptr) {}
	void setRoot(threadedBinNode* node) { root = node; }
	bool isEmpty() { return root == nullptr; }

	// ������ ����� inorder �湮 �Լ�
	void threadedInorder() {
		if (false == isEmpty()) {
			printf("������ ����Ʈ��: ");
			threadedBinNode* q = root;
			while (q->getLeft()) {
				q = q->getLeft();	// ���� ���ʳ��� �̵�
			}
			do {
				printf("%c ", q->getData());
				q = findSuccessor(q);	// �ļ��� �Լ� ȣ��
			} while (q);
			printf("\n");
		}
	}

	threadedBinNode* findSuccessor(threadedBinNode* p) {
		threadedBinNode* q = p->getRight();	// ������ �ڽ� ������

		// ���� ������ �����Ͱ� nullptr�̰ų� �������̸�, ������ �����͸� ��ȯ
		if (q == nullptr || p->bThread) { return q; }
		// ���� ������ �ڽ��̸� �ٽ� ���� ���� ���� �̵�
		while (q->getLeft() != nullptr) { q = q->getLeft(); }
		return q;
	}
};