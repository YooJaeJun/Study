#pragma once
#include "heapNode.h"
const int maxElement = 200;
class minHeap {
	heapNode node[maxElement];
	int size;
public:
	minHeap() : node(), size(0) {}

	bool isEmpty() { return size == 0; }
	bool isFull() { return size == maxElement - 1; }

	heapNode& getParent(int i) { return node[i / 2]; }
	heapNode& getLeft(int i) { return node[i * 2]; }
	heapNode& getRight(int i) { return node[i * 2 + 1]; }

	// »ðÀÔ
	void insert(int key,int u, int v) {
		if (isFull()) { return; }
		int i = ++size;
		while (i != 1 &&
			key < getParent(i).getKey()) {
			node[i] = getParent(i);
			i /= 2;
		}
		node[i].setKey(key, u, v);
	}

	// »èÁ¦
	heapNode remove() {
		if (isEmpty()) { return {-1, -1, -1}; }
		heapNode item = node[1];
		heapNode last = node[size--];
		int parent = 1;
		int child = 2;
		while (child <= size) {
			if (child < size &&
				getLeft(parent).getKey() > getRight(parent).getKey()) {
				child++;
			}
			if (last.getKey() <= node[child].getKey()) { break; }

			node[parent] = node[child];
			parent = child;
			child *= 2;
		}
		node[parent] = last;
		return item;
	}
};