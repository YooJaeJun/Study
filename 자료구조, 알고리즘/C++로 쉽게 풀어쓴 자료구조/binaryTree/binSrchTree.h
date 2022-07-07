#pragma once
// 이진 탐색 트리
#include "binaryTree.h"
class binSrchTree : public binaryTree {
public:
	binSrchTree() {}
	~binSrchTree() {}

	// 탐색 연산
	binaryNode* search(int key) {
		binaryNode* node = searchRecur(root, key);
		if (node != nullptr) {
			printf("탐색 성공: 키값이 %d인 노드 = 0x%x\n", node->getData(), node);
		}
		else {
			printf("탐색 실패: 키값이 %d인 노드 없음\n", key);
		}
		return node;
	}
	// n을 루트로 갖는 서브트리에서 key를 키값으로 갖는 노드 탐색 함수
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

	// 삽입 연산
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
	// r을 루트로 갖는 서브트리에 새로운 노드 n을 삽입하는 함수
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

	// 삭제 연산
	void remove(int key) {
		// 빈 트리
		if (isEmpty()) {
			return;
		}
		// 없앨 노드와 그 노드의 부모 노드를 찾는다.
		binaryNode* parent = nullptr;
		binaryNode* node = root;
		while (node != nullptr && node->getData() != key) {
			parent = node;
			node = (key < node->getData()) ? node->getLeft() : node->getRight();
		}
		// 없앨 노드가 트리에 없음.
		if (node == nullptr) {
			printf("Error: 키가 트리에 없음!");
			return;
		}
		// 없앨 노드가 트리에 있음.
		else remove(parent, node);
	}
	// parent를 부모로 갖는 노드 node를 이진 탐색 트리에서 삭제하는 함수
	void remove(binaryNode* parent, binaryNode* node) {
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
			binaryNode* child = (node->getLeft() != nullptr) ? node->getLeft() : node->getRight();
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
			binaryNode* succp = node;
			binaryNode* succ = node->getRight();
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
			node->setData(succ->getData());
			// 삭제할 노드를 후계 노드로 변경 : 실제로는 후계 노드가 제거됨
			node = succ;
		}
		//
		delete node;
	}
};