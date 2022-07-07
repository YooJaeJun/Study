#pragma once
// ���� Ž�� Ʈ��
#include "binaryTree.h"
class binSrchTree : public binaryTree {
public:
	binSrchTree() {}
	~binSrchTree() {}

	// Ž�� ����
	binaryNode* search(int key) {
		binaryNode* node = searchRecur(root, key);
		if (node != nullptr) {
			printf("Ž�� ����: Ű���� %d�� ��� = 0x%x\n", node->getData(), node);
		}
		else {
			printf("Ž�� ����: Ű���� %d�� ��� ����\n", key);
		}
		return node;
	}
	// n�� ��Ʈ�� ���� ����Ʈ������ key�� Ű������ ���� ��� Ž�� �Լ�
	binaryNode* searchRecur(binaryNode* n, int key) {
		if (n == nullptr) { return nullptr; }
		if (key == n->getData()) {
			return n;
		}
		else if (key < n->getData()) {
			return searchRecur(n->getLeft(), key);
		}
		else {
			return searchRecur(n->getRight(), key);
		}
	}
	binaryNode* searchIter(binaryNode* n, int key) {
		while (n != nullptr) {
			if (key == n->getData()) {
				return n;
			}
			else if (key < n->getData()) {
				n = n->getLeft();
			}
			else {
				n = n->getRight();
			}
		}
		return nullptr;
	}

	// ���� ����
	void insert(binaryNode* n) {
		if (n == nullptr) {
			return;
		}
		if (isEmpty()) {
			root = n;
		}
		else {
			insertRecur(root, n);
		}
	}
	// r�� ��Ʈ�� ���� ����Ʈ���� ���ο� ��� n�� �����ϴ� �Լ�
	void insertRecur(binaryNode* r, binaryNode* n) {
		if (n->getData() == r->getData()) {
			return;
		}
		else if (n->getData() < r->getData()) {
			if (r->getLeft() == nullptr) {
				r->setLeft(n);
			}
			else {
				insertRecur(r->getLeft(), n);
			}
		}
		else {
			if (r->getRight() == nullptr) {
				r->setRight(n);
			}
			else {
				insertRecur(r->getRight(), n);
			}
		}
	}

	// ���� ����
	void remove(int key) {
		// �� Ʈ��
		if (isEmpty()) {
			return;
		}
		// ���� ���� �� ����� �θ� ��带 ã�´�.
		binaryNode* parent = nullptr;
		binaryNode* node = root;
		while (node != nullptr && node->getData() != key) {
			parent = node;
			node = (key < node->getData()) ? node->getLeft() : node->getRight();
		}
		// ���� ��尡 Ʈ���� ����.
		if (node == nullptr) {
			printf("Error: Ű�� Ʈ���� ����!");
			return;
		}
		// ���� ��尡 Ʈ���� ����.
		else remove(parent, node);
	}
	// parent�� �θ�� ���� ��� node�� ���� Ž�� Ʈ������ �����ϴ� �Լ�
	void remove(binaryNode* parent, binaryNode* node) {
		// case 1 ������ ��� == �ܸ� ���
		if (node->isLeaf()) {
			if (parent == nullptr) {	// node == root. ������°� ��.
				root = nullptr;
			}
			else {		// �ƴ� ���� parent�� �ش� �ڽ��� null
				if (parent->getLeft() == node) {
					parent->setLeft(nullptr);
				}
				else {
					parent->setRight(nullptr);
				}
			}
		}
		// case 2 ������ ��� == �����̳� ������ �ڽĸ� ���� ���
		else if (node->getLeft() == nullptr || node->getRight() == nullptr) {
			// ������ ����� ������ �ڽ� ��� => child
			binaryNode* child = (node->getLeft() != nullptr) ? node->getLeft() : node->getRight();
			// ������ ��尡 ��Ʈ�̸� ==> child�� ���ο� root�� ��.
			if (node == root) {
				root = child;
			}
			// �ƴϸ� ==> �θ� ����� �ڽ����� �ڽ� ��� child�� ���� ����
			else {
				if (parent->getLeft() == node) {
					parent->setLeft(child);
				}
				else {
					parent->setRight(child);
				}
			}
		}
		// case 3 ������ ��� == �� ���� �ڽ� ��� �ִ� ���
		else {
			// �����Ϸ��� ����� ������ ����Ʈ������ ���� ���� ��带 Ž��
			// succ => �İ� ���: ������ ����Ʈ������ ���� key�� ���� ���
			// succp => �İ� ����� �θ� ���
			binaryNode* succp = node;
			binaryNode* succ = node->getRight();
			while (succ->getLeft() != nullptr) {
				succp = succ;
				succ = succ->getLeft();
			}
			// �İ� ����� �θ�� �İ� ����� ������ �ڽ��� ���� ����
			if (succp->getLeft() == succ) {
				succp->setLeft(succ->getRight());
			}
			else {	// �İ� ��尡 ������ ����� �ٷ� ������ �ڽ��� ���
				succp->setRight(succ->getRight());
			}
			// �İ� ��� ������ ������ ��忡 ����
			node->setData(succ->getData());
			// ������ ��带 �İ� ���� ���� : �����δ� �İ� ��尡 ���ŵ�
			node = succ;
		}
		//
		delete node;
	}
};