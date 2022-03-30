#pragma once
class threadedBinNode {
	int data;
	threadedBinNode* left;
	threadedBinNode* right;
public:
	bool bThread;
	threadedBinNode(int val, threadedBinNode* l, threadedBinNode* r, bool bTh)
		: data(val), left(l), right(r), bThread(bTh) {
	}
	
	int getData() { return data; }
	void setRight(threadedBinNode* r) { right = r; }
	threadedBinNode* getLeft() { return left; }
	threadedBinNode* getRight() { return right; }
};