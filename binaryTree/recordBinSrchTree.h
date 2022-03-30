#pragma once
#include "recordBinaryTree.h"
class recordBinSrchTree : public recordBinaryTree {
public:
	// ���� Ž�� Ʈ���� Ž�� ����
	recordBinaryNode* search(const char* key) {
		return searchRecur(root, key);
	}
	recordBinaryNode* searchRecur(recordBinaryNode* n, const char* key) {
		if (n == nullptr) { return nullptr; }
		if (n->compare(key) == 0) { return n; }
		else if (n->compare(key) < 0) {
			return searchRecur(n->getLeft(), key);
		}
		else {
			return searchRecur(n->getRight(), key);
		}
	}

	// ���� Ž�� Ʈ���� ���� ����
	void insert(recordBinaryNode* n) {
		if (n == nullptr) { return; }
		if (isEmpty()) { root = n; }
		else { insertRecur(root, n); }
	}
	void insertRecur(recordBinaryNode* r, recordBinaryNode* n) {
		if (n->compare(r) == 0) { return; }
		else if (n->compare(r) > 0) {
			if (r->getLeft() == nullptr) { r->setLeft(n); }
			else { insertRecur(r->getRight(), n); }
		}
		else {
			if (r->getRight() == nullptr) { r->setRight(n); }
			else { insertRecur(r->getRight(), n); }
		}
	}

	// ���� Ž�� Ʈ���� ���� ����
	void remove(const char* data) {
		if (isEmpty()) { return; }
		recordBinaryNode* parent = nullptr;
		recordBinaryNode* node = root;
		while (node != nullptr && node->compare(data) != 0) {
			parent = node;
			node = (node->compare(data) < 0) ? node->getLeft() : node->getRight();
		}
		if (node != nullptr) { remove(parent, node); }
	}
	void remove(recordBinaryNode* parent, recordBinaryNode* node) {
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
			recordBinaryNode* child = (node->getLeft() != nullptr) ? node->getLeft() : node->getRight();
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
			recordBinaryNode* succp = node;
			recordBinaryNode* succ = node->getRight();
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
			//node->setData(succ->getData());
			// ������ ��带 �İ� ���� ���� : �����δ� �İ� ��尡 ���ŵ�
			node = succ;
		}
		//
		delete node;
	}
};