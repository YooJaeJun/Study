#pragma once
#include <cstdio>

class heapNode {
	int key;	// key 값: 간선의 가중치
	int v1;		// 정점1
	int v2;		// 정점2
	
public:
	heapNode() {}
	heapNode(int k, int u, int v) : key(k), v1(u), v2(v) {}

	void setKey(int k) { key = k; }
	void setKey(int k, int u, int v) { key = k;	v1 = u; v2 = v; }

	int getKey() { return key; }
	int getV1() { return v1; }
	int getV2() { return v2; }
};