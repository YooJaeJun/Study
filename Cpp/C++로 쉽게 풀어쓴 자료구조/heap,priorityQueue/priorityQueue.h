#pragma once
#include <queue>
#include <functional>
using namespace std;

// STL의 우선순위 큐를 이용한 내림차순 정렬, 최대힙 사용
void heapSortDec(int a[], int n) {
	priority_queue<int> maxHeap;
	for (int i = 0; i < n; i++) {
		maxHeap.push(a[i]);
	}
	// MaxHeap을 이용해 내림차순으로 정렬하기 위한 반복문
	for (int i = 0; i < n; i++) {
		a[i] = maxHeap.top();
		maxHeap.pop();
	}
}

// STL의 우선순위 큐를 이용한 오름차순 정렬. 최소힙 사용.
void heapSortInc(int a[], int n) {
	priority_queue<int, vector<int>, greater<int>> minHeap;
	for (int i = 0; i < n; i++) {
		minHeap.push(a[i]);
	}
	// MinHeap을 이용해 오름차순으로 정렬하기 위한 반복문
	for (int i = 0; i < n; i++) {
		a[i] = minHeap.top();
		minHeap.pop();
	}
}