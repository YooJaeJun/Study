#pragma once
// ���� ������ ��� Ŭ����
#include <cstdio>
class heapNode {
	int key;
public:
	heapNode(int k = 0) : key(k) {}
	void setKey(int k) { key = k; }
	int getKey() { return key; }
	void display() { printf("%4d", key); }
};