#pragma once
#include <iostream>

class binaryNode {
protected:
	int data;
	binaryNode* left;
	binaryNode* right;
public:
	binaryNode(int val = 0, binaryNode* l = nullptr, binaryNode* r = nullptr) 
		: data(val), left(l), right(r) { }
	void setData(int val) { data = val; }
	void setLeft(binaryNode* l) { left = l; }
	void setRight(binaryNode* r) { right = r; }
	int getData() { return data; }
	binaryNode* getLeft() { return left; }
	binaryNode* getRight() { return right; }
	bool isLeaf() { return left == nullptr && right == nullptr; }	// 단말 노드인지 체크: 자식 모두 없는지
	void inorder() {
		if (left != nullptr) { left->inorder(); }
		printf("%d", data);
		if (right != nullptr) { right->inorder(); }
	}

	binaryNode* search(int key) {
		if (key == data) {
			return this;
		}
		else if (key < data && left != nullptr) {
			return left->search(key);
		}
		else if (key > data && right != nullptr) {
			return right->search(key);
		}
		else {
			return nullptr;
		}
	}
};