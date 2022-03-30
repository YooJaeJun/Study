#pragma once
#include "recordBinaryTree.h"
class recordBinSrchTree : public recordBinaryTree {
public:
	// 이진 탐색 트리의 탐색 연산
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

	// 이진 탐색 트리의 삽입 연산
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

	// 이집 탐색 트리의 삭제 연산
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
		// case 1 삭제할 노드 == 단말 노드
		if (node->isLeaf()) {
			if (parent == nullptr) {	// node == root. 공백상태가 됨.
				root = nullptr;
			}
			else {		// 아닌 경우는 parent의 해당 자식을 null
				if (parent->getLeft() == node) {
					parent->setLeft(nullptr);
				}
				else {
					parent->setRight(nullptr);
				}
			}
		}
		// case 2 삭제할 노드 == 왼쪽이나 오른쪽 자식만 갖는 경우
		else if (node->getLeft() == nullptr || node->getRight() == nullptr) {
			// 삭제할 노드의 유일한 자식 노드 => child
			recordBinaryNode* child = (node->getLeft() != nullptr) ? node->getLeft() : node->getRight();
			// 삭제할 노드가 루트이면 ==> child가 새로운 root가 됨.
			if (node == root) {
				root = child;
			}
			// 아니면 ==> 부모 노드의 자식으로 자식 노드 child를 직접 연결
			else {
				if (parent->getLeft() == node) {
					parent->setLeft(child);
				}
				else {
					parent->setRight(child);
				}
			}
		}
		// case 3 삭제할 노드 == 두 개의 자식 모두 있는 경우
		else {
			// 삭제하려는 노드의 오른쪽 서브트리에서 가장 작은 노드를 탐색
			// succ => 후계 노드: 오른쪽 서브트리에서 가장 key가 작은 노드
			// succp => 후계 노드의 부모 노드
			recordBinaryNode* succp = node;
			recordBinaryNode* succ = node->getRight();
			while (succ->getLeft() != nullptr) {
				succp = succ;
				succ = succ->getLeft();
			}
			// 후계 노드의 부모와 후계 노드의 오른쪽 자식을 직접 연결
			if (succp->getLeft() == succ) {
				succp->setLeft(succ->getRight());
			}
			else {	// 후계 노드가 삭제할 노드의 바로 오른쪽 자식인 경우
				succp->setRight(succ->getRight());
			}
			// 후계 노드 정보를 삭제할 노드에 복사
			//node->setData(succ->getData());
			// 삭제할 노드를 후계 노드로 변경 : 실제로는 후계 노드가 제거됨
			node = succ;
		}
		//
		delete node;
	}
};