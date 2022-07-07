#pragma once
// ���� ����Ʈ�� ǥ���� �׷���
#include "adjListGraph.h"
#include "circularQueue.h"

class srchALGraph : public adjListGraph {
	bool visited[maxVtxs];
public:
	void resetVisited() {
		for (int i = 0; i < size; i++) {
			visited[i] = false;
		}
	}

	bool isLinked(int u, int v) {
		for (node* p = adj[u]; p != nullptr; p = p->getLink()) {
			if (p->getId() == v) { return true; }
		}
		return false;
	}

	//
	void dfs(int v) {
		visited[v] = true;
		printf("%c ", getVertex(v));	// ���� �̸� ���

		for (node* p = adj[v]; p != nullptr; p = p->getLink()) {
			if (visited[p->getId()] == false) {
				dfs(p->getId());	// ���� w���� dfs ���� ����
			}
		}
	}

	//
	void bfs(int v) {
		visited[v] = true;
		printf("%c ", getVertex(v));

		circularQueue que;
		que.enqueue(v);

		while (false == que.isEmpty()) {
			int v = que.dequeue();
			for (node* w = adj[v]; w != nullptr; w = w->getLink()) {
				int id = w->getId();
				if (visited[id] == false) {
					visited[id] = true;
					printf("%c ", getVertex(id));
					que.enqueue(id);
				}
			}
		}
	}
};