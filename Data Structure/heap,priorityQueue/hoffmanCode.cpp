#pragma once
#include "minHeap.h"

void makeTree(int freq[], int n) {
	minHeap heap;
	for (int i = 0; i < n; i++) {
		heap.insert(freq[i]);	// 모든 노드 삽입
	}
	for (int i = 1; i < n; i++) {
		heapNode e1 = heap.remove();					// 최소 노드 삭제
		heapNode e2 = heap.remove();					// 다음 최소 노드 삭제
		heap.insert(e1.getKey() + e2.getKey());			// 합한 노드 추가
		printf("(%d+%d)\n", e1.getKey(), e2.getKey());
	}
}

void main() {
	int freq[] = { 15, 12, 8, 6, 4 };
	makeTree(freq, 5);
}