#pragma once
#include "heapNode.h"
const int maxElement = 200;
class maxHeap {
	heapNode node[maxElement];
	int size;
public:
	maxHeap() : size(0) {}
	bool isEmpty() { return size == 0; }
	bool isFull() { return size == maxElement - 1; }

	heapNode& getParent(int i) { return node[i / 2]; }
	heapNode& getLeft(int i) { return node[i * 2]; }
	heapNode& getRight(int i) { return node[i * 2 + 1]; }

	void insert(int key) {
		if (isFull()) { return; }
		int i = ++size;	// ������ �� ũ�� ��ġ���� ����

		// Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
		while (i != 1 &&	// ��Ʈ�� �ƴϰ�
			key > getParent(i).getKey()) {	// �θ� ��庸�� Ű���� ũ��
			node[i] = getParent(i);		// �θ� �ڽĳ��� �����
			i /= 2;		// �� ���� ���� ���
		}
		node[i].setKey(key);	// ���� ��ġ�� ������ ����.

	}

	heapNode remove() {
		if (isEmpty()) { return NULL; }
		heapNode item = node[1];		// ��Ʈ���(�������)
		heapNode last = node[size--];	// ���� ���������
		int parent = 1;					// ������ ����� ��ġ�� ��Ʈ�� ������
		int child = 2;					// ��Ʈ�� ���� �ڽ� ��ġ
		while (child <= size) {			// �� Ʈ���� ����� �ʴ� ����
			// ���� ����� �ڽ� ��� �� �� ū �ڽĳ�带 ã��
			if (child < size &&
				getLeft(parent).getKey() < getRight(parent).getKey()) {
				child++;	// child: �� ū �ڽ� ����� �ε���
			}
			// ������ ��尡 �� ū �ڽĺ��� ũ�� ==> �̵� �Ϸ�
			if (last.getKey() >= node[child].getKey()) { break; }

			// �ƴϸ� ==> �� �ܰ� �Ʒ��� �̵�
			node[parent] = node[child];
			parent = child;
			child *= 2;
		}
		node[parent] = last;	// ������ ��带 ���� ��ġ�� ����
		return item;			// ��Ʈ ��带 ��ȯ
	}
	
	heapNode find() { return node[1]; }

	void display() {
		for (int i = 1, level = 1; i <= size; i++) {
			if (i == level) {
				printf("\n");
				level *= 2;
			}
			node[i].display();
		}
		printf("\n-------------------");
	}
};