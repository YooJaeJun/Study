#pragma once
#include <cstdio>

class heapNode {
	int key;	// key ��: ������ ����ġ
	int v1;		// ����1
	int v2;		// ����2
	
public:
	heapNode() {}
	heapNode(int k, int u, int v) : key(k), v1(u), v2(v) {}

	void setKey(int k) { key = k; }
	void setKey(int k, int u, int v) { key = k;	v1 = u; v2 = v; }

	int getKey() { return key; }
	int getV1() { return v1; }
	int getV2() { return v2; }
};