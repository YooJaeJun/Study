#pragma once
// 힙에 저장할 노드 클래스
#include <cstdio>
class heapNode {
	int key;
public:
	heapNode(int k = 0) : key(k) {}
	void setKey(int k) { key = k; }
	int getKey() { return key; }
	void display() { printf("%4d", key); }
};