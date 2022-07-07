#pragma once
#include <queue>
#include <functional>
using namespace std;

// STL�� �켱���� ť�� �̿��� �������� ����, �ִ��� ���
void heapSortDec(int a[], int n) {
	priority_queue<int> maxHeap;
	for (int i = 0; i < n; i++) {
		maxHeap.push(a[i]);
	}
	// MaxHeap�� �̿��� ������������ �����ϱ� ���� �ݺ���
	for (int i = 0; i < n; i++) {
		a[i] = maxHeap.top();
		maxHeap.pop();
	}
}

// STL�� �켱���� ť�� �̿��� �������� ����. �ּ��� ���.
void heapSortInc(int a[], int n) {
	priority_queue<int, vector<int>, greater<int>> minHeap;
	for (int i = 0; i < n; i++) {
		minHeap.push(a[i]);
	}
	// MinHeap�� �̿��� ������������ �����ϱ� ���� �ݺ���
	for (int i = 0; i < n; i++) {
		a[i] = minHeap.top();
		minHeap.pop();
	}
}