#pragma once
// ���� ���� Ŭ����

class vertexSets {
	int parent[maxVtxs];	// �θ� ������ id
	int nSets;	// ������ ����

public:
	vertexSets(int n) : nSets(n) {
		for (int i = 0; i < nSets; i++) {
			parent[i] = -1;		// ��� ������ ������ ���տ� ����
		}
	}
	
	bool isRoot(int i) { return parent[i] < 0; }	// parent[i]�� -1�̸� ���� ������ ��Ʈ�� ��.

	int findSet(int v) {	// v�� ���� ������ ã�� ��ȯ
		while (false == isRoot(v)) { v = parent[v]; }
		return v;
	}

	void unionSets(int s1, int s2) {
		parent[s1] = s2;
		nSets--;
	}
};