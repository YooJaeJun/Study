#pragma once
#include "adjListGraph.h"
#include "arrayStack.h"

class topoSortGraph : public adjListGraph {
	int inDeg[maxVtxs];	// ������ ��������
public:
	// ���⼺ ���� ���� ����
	void insertDirEdge(int u, int v) {
		adj[u] = new node(v, adj[u]);
	}

	// ���������� �����Ѵ�.
	void topoSort() {
		// ��� �������� ���� ������ ���
		for (int i = 0; i < size; i++ ) {
			inDeg[i] = 0;
		}
		for (int i = 0; i < size; i++) {
			node* node = adj[i];
			while (node != nullptr) {
				inDeg[node->getId()]++;
				node = node->getLink();
			}
		}
		
		// ���� ������ 0�� ������ ���ÿ� ����
		arrayStack s;
		for (int i = 0; i < size; i++) {
			if (inDeg[i] == 0) { s.push(i); }
		}

		// ���� ������ ����
		while (s.isEmpty() == false) {
			int w = s.pop();
			printf("%c ", getVertex(w) + 'A');	// ���� ���
			node* node = adj[w];			// �� ������ ���� ������ ����
			while (node != nullptr) {
				int u = node->getId();
				inDeg[u]--;		// ���� ������ ����
				if (inDeg[u] == 0) {	// ���� ������ 0�� ������ push
					s.push(u);
				}
				node = node->getLink();	// ���� ����
			}
		}
		printf("\n");
	}
};