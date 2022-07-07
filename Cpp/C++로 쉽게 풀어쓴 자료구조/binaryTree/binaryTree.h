#pragma once
#include "binaryNode.h"
#include "circularQueue.h"

class binaryTree {
protected:
	binaryNode* root;
public:
	binaryTree() : root(nullptr) {}
	void setRoot(binaryNode* node) { root = node; }
	binaryNode* getRoot() { return root; }
	bool isEmpty() { return root == nullptr; }

	void inorder() {
		printf("\ninorder: ");
		inorder(root);
	}
	void inorder(binaryNode* node) {
		if (node != nullptr) {
			inorder(node->getLeft());
			printf("[%d] ", node->getData());
			inorder(node->getRight());
		}
	}

	void preorder() {
		printf("\npreorder: ");
		preorder(root);
	}
	void preorder(binaryNode* node) {
		if (node != nullptr) {
			printf("[%d] ", node->getData());
			preorder(node->getLeft());
			preorder(node->getRight());
		}
	}
	
	void postorder() {
		printf("\npostorder: ");
		postorder(root);
	}
	void postorder(binaryNode* node) {
		if (node != nullptr) {
			postorder(node->getLeft());
			postorder(node->getRight());
			printf("[%d] ", node->getData());
		}
	}

	void levelorder() {
		printf("\nlevelorder: ");
		if (false == isEmpty()) {
			circularQueue q;
			q.enqueue(root);
			while (false == q.isEmpty()) {
				binaryNode* n = q.dequeue();
				if (n != nullptr) {
					printf("[%d] ", n->getData());
					q.enqueue(n->getLeft());
					q.enqueue(n->getRight());
				}
			}
			printf("\n");
		}
	}

	int getCount() {
		return isEmpty() ? 0 : getCount(root);
	}
	int getCount(binaryNode* node) {
		if (node == nullptr) { return 0; }
		return 1 + getCount(node->getLeft()) + getCount(node->getRight());
	}
	
	int getLeafCount() {
		return isEmpty() ? 0 : getLeafCount(root);
	}
	int getLeafCount(binaryNode* node) {
		if (node == nullptr) { return 0; }
		if (node->isLeaf()) { return 1; }
		else return getLeafCount(node->getLeft()) + getLeafCount(node->getRight());
	}

	int getHeight() {
		return isEmpty() ? 0 : getHeight(root);
	}
	int getHeight(binaryNode* node) {
		if (node == nullptr) { return 0; }
		int hLeft = getHeight(node->getLeft());
		int hRight = getHeight(node->getRight());
		return (hLeft > hRight) ? hLeft + 1 : hRight + 1;
	}

	// 수식트리 계산 함수
	int evaluate() { return evaluate(root); }
	int evaluate(binaryNode* node) {
		if (node == nullptr) { return 0; }
		if (node->isLeaf()) { return node->getData(); }
		else {
			int op1 = evaluate(node->getLeft());
			int op2 = evaluate(node->getRight());
			switch (node->getData()) 
			{
			case '+': return op1 + op2;
			case '-': return op1 - op2;
			case '*': return op1 * op2;
			case '/': return op1 / op2;
			}
			return 0;
		}
	}

	// 디렉터리 용량 계산 함수
	int calcSize() { return calcSize(root); }
	int calcSize(binaryNode* node) {
		if (node == nullptr) { return 0; }
		return node->getData() + calcSize(node->getLeft()) + calcSize(node->getRight());
	}
};