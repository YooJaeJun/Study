#pragma once
#include "minHeap.h"

void makeTree(int freq[], int n) {
	minHeap heap;
	for (int i = 0; i < n; i++) {
		heap.insert(freq[i]);	// ��� ��� ����
	}
	for (int i = 1; i < n; i++) {
		heapNode e1 = heap.remove();					// �ּ� ��� ����
		heapNode e2 = heap.remove();					// ���� �ּ� ��� ����
		heap.insert(e1.getKey() + e2.getKey());			// ���� ��� �߰�
		printf("(%d+%d)\n", e1.getKey(), e2.getKey());
	}
}

void main() {
	int freq[] = { 15, 12, 8, 6, 4 };
	makeTree(freq, 5);
}