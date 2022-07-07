#include "threadedBinTree.h"
/*
void main() {
	threadedBinTree tree;
	//		G
	//	C		F
	//A   B   D   E
	threadedBinNode* n1 = new threadedBinNode('A', nullptr, nullptr, true);
	threadedBinNode* n2 = new threadedBinNode('B', nullptr, nullptr, true);
	threadedBinNode* n3 = new threadedBinNode('C', n1, n2, false);
	threadedBinNode* n4 = new threadedBinNode('D', nullptr, nullptr, true);
	threadedBinNode* n5 = new threadedBinNode('E', nullptr, nullptr, false);
	threadedBinNode* n6 = new threadedBinNode('F', n4, n5, false);
	threadedBinNode* n7 = new threadedBinNode('G', n3, n6, false);
	tree.setRoot(n7);
	// 스레드 설정
	n1->setRight(n3);
	n2->setRight(n7);
	n4->setRight(n6);
	// 중위 순회
	tree.threadedInorder();
}
*/