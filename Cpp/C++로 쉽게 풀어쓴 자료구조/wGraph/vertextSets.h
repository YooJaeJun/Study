#pragma once
// 정점 집합 클래스

class vertexSets {
	int parent[maxVtxs];	// 부모 정점의 id
	int nSets;	// 집합의 개수

public:
	vertexSets(int n) : nSets(n) {
		for (int i = 0; i < nSets; i++) {
			parent[i] = -1;		// 모든 정점이 고유의 집합에 속함
		}
	}
	
	bool isRoot(int i) { return parent[i] < 0; }	// parent[i]가 -1이면 정점 집합의 루트가 됨.

	int findSet(int v) {	// v가 속한 집합을 찾아 반환
		while (false == isRoot(v)) { v = parent[v]; }
		return v;
	}

	void unionSets(int s1, int s2) {
		parent[s1] = s2;
		nSets--;
	}
};