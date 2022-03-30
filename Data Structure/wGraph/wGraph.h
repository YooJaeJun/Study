#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "adjMatGraph.h"
const int INF = 9999;	// ���� INF �̻��̸� ������ ����

// ����ġ �׷����� ǥ���ϴ� Ŭ����
class wGraph : public adjMatGraph {
public:
	void insertEdge(int u, int v, int weight) {
		if (weight > INF) { weight = INF; }
		setEdge(u, v, weight);
	}
	bool hasEdge(int i, int j) { return (getEdge(i, j) < INF); }
	
	void load(const char* filename) {
		FILE* fp = fopen(filename, "r");
		if (fp != nullptr) {
			int n;
			fscanf(fp, "%d", &n);	// ������ ��ü ����
			for (int i = 0; i < n; i++) {
				char str[80];
				int val;
				fscanf(fp, "%s", str);	// ������ �̸�
				insertVertex(str[0]);	// ���� ����
				for (int j = 0; j < n; j++) {
					fscanf(fp, "%d", &val);	// ���� ����
					insertEdge(i, j, val);	// ���� ����
				}
			}
			fclose(fp);
		}
	}
};