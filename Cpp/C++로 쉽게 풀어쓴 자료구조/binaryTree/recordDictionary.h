#pragma once
#include "recordBinSrchTree.h"
class recordDictionary : public recordBinSrchTree {
public:
	void printAllWords() {
		printf(" >> ���� �ܾ���:\n");
		if (false == isEmpty()) { inorder(root); }
	}
	void searchWord(const char* word) {
		recordBinaryNode* node = search(word);
		if (node != nullptr) {
			printf(">> ");
			node->display();
		}
		else { printf(" >> ��ϵ��� ���� �ܾ�: %s\n", word); }
	}
	void searchMeaning(const char* m) {
		recordBinaryNode* node = (isEmpty()) ? nullptr : searchByMeaning(root, m);
		if (node != nullptr) {
			printf(" >> ");
			node->display();
		}
		else { printf(" >> ��ϵ��� ���� �ǹ�: %s\n", m); }
	}
	recordBinaryNode* searchByMeaning(recordBinaryNode* node, const char* m) {
		if (node == nullptr || node->compareMeaning(m) == 0) { return node;	}
		recordBinaryNode* theNode = searchByMeaning(node->getLeft(), m);
		if (theNode != nullptr) { return theNode; }
		return searchByMeaning(node->getRight(), m);
	}
};
