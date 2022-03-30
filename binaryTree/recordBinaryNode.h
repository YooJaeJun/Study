#pragma once
#include <iostream>
#include "record.h"

class recordBinaryNode : public record {
protected:
	recordBinaryNode* left;
	recordBinaryNode* right;
public:
	recordBinaryNode(const char* w = "", const char* m = "")
		: record(w, m), left(nullptr), right(nullptr) { }
	void setLeft(recordBinaryNode* l) { left = l; }
	void setRight(recordBinaryNode* r) { right = r; }
	recordBinaryNode* getLeft() { return left; }
	recordBinaryNode* getRight() { return right; }
	bool isLeaf() { return left == nullptr && right == nullptr; }
};