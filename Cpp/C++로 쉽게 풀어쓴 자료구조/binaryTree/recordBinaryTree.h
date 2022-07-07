#pragma once
#include "recordBinaryNode.h"
class recordBinaryTree {
protected:
	recordBinaryNode* root;
public:
	recordBinaryTree() : root(nullptr) {}
	bool isEmpty() { return root == nullptr; }
	void inorder(recordBinaryNode* node) {
		if (node != nullptr) {
			inorder(node->getLeft());
			node->display();
			inorder(node->getRight());
		}
	}
};