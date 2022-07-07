#pragma once
// �ּ� ����Ʈ��(MST) ����� �߰��� ����ġ �׷��� Ŭ����
#include "minHeap.h"
#define _CRT_SECURE_NO_WARNINGS
#include "wGraph.h"
#include "vertextSets.h"

class wGraphMST : public wGraph {
public:
	void kruskal() {
		minHeap heap;
		// ���� ��� ���� ����
		for (int i = 0; i < size - 1; i++) {
			for (int j = i + 1; j < size; j++) {
				if (hasEdge(i, j)) {
					heap.insert(getEdge(i, j), i, j);
				}
			}
		}

		vertexSets set(size);	// size ���� ������ ����
		int edgeAccepted = 0;	// ���õ� ������ ��
		while (edgeAccepted < size - 1) {	// ������ �� < (size - 1)
			heapNode e = heap.remove();		// �ּ� ������ ����
			int uset = set.findSet(e.getV1());	// ���� u�� ���� ��ȣ
			int vset = set.findSet(e.getV2());	// ���� v�� ~

			if (uset != vset) {		// ���� ���� ������ �ٸ���
				printf("���� �߰�: %c - %c (���:%d)\n",
					getVertex(e.getV1()), getVertex(e.getV2()),
					e.getKey());
				set.unionSets(uset, vset);	// �� ���� ������ ����.
				edgeAccepted++;
			}

		}
	}

	void prim(int s) {
		bool selected[maxVtxs];		// ������ �̹� ���ԵǾ��°�
		int dist[maxVtxs];	// �Ÿ�
		for (int i = 0; i < size; i++) {	// �迭 �ʱ�ȭ
			dist[i] = INF;
			selected[i] = false;
		}
		dist[s] = 0;	// ���� ����

		for (int i = 0; i < size; i++) {
			// ���Ե��� ���� ������ �߿��� MST���� �Ÿ��� �ּ��� ����
			int u = getMinVertex(selected, dist);

			selected[u] = true;
			if (dist[u] == INF) { return; }

			printf("%c ", getVertex(u));
			for (int v = 0; v < size; v++) {
				if (getEdge(u, v) != INF) {
					if (false == selected[v] && getEdge(u, v) < dist[v]) {
						dist[v] = getEdge(u, v);
					}
				}
			}
		}
		printf("\n");
	}

	// MST�� ���Ե��� ���� ������ �߿���, MST���� �Ÿ�(dist)�� �ּ��� ���� ����
	int getMinVertex(bool* selected, int* dist) {
		int minv = 0;
		int mindist = INF;
		for (int v = 0; v < size; v++) {
			if (false == selected[v] && dist[v] < mindist) {
				mindist = dist[v];
				minv = v;
			}
		}
		return minv;
	}
};