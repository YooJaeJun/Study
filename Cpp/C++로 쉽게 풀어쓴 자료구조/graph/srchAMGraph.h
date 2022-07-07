#pragma once
// ���� ��ķ� ǥ���� �׷���
#include "adjMatGraph.h"
#include "circularQueue.h"

class srchAMGraph : public adjMatGraph {
protected:
	bool visited[maxVtxs];
public:
	void resetVisited() {	// ��� ������ �湮���� �ʾҴٰ� ����
		for (int i = 0; i < size; i++) {
			visited[i] = false;
		}
	}

	bool isLinked(int u, int v) { return getEdge(u, v) != 0; }

	// ���� �켱 Ž�� �Լ�
	void dfs(int v) {
		visited[v] = true;
		printf("%c ", getVertex(v));

		for (int w = 0; w < size; w++) {
			if (isLinked(v, w) && visited[w] == false) {
				dfs(w);
			}
		}
	}

	// �ʺ� �켱 Ž��
	void bfs(int v) {
		visited[v] = true;
		printf("%c ", getVertex(v));	// ������ �̸� ���

		circularQueue que;
		que.enqueue(v);	// ���� ������ ť�� ����

		while (false == que.isEmpty()) {
			int v = que.dequeue();	// ť�� ���� ����
			for (int w = 0; w < size; w++) {
				if (isLinked(v, w) && visited[w] == false) {
					visited[w] = true;
					printf("%c ", getVertex(w));	// ������ �̸� ���
					que.enqueue(w);
				}
			}
		}
	}
};