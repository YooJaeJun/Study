#pragma once
#include "adjListGraph.h"
#include "arrayStack.h"

class topoSortGraph : public adjListGraph {
	int inDeg[maxVtxs];	// 정점의 진입차수
public:
	// 방향성 간선 삽입 연산
	void insertDirEdge(int u, int v) {
		adj[u] = new node(v, adj[u]);
	}

	// 위상정렬을 수행한다.
	void topoSort() {
		// 모든 정점들의 진입 차수를 계산
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
		
		// 진입 차수가 0인 정점을 스택에 삽입
		arrayStack s;
		for (int i = 0; i < size; i++) {
			if (inDeg[i] == 0) { s.push(i); }
		}

		// 위상 순서를 생성
		while (s.isEmpty() == false) {
			int w = s.pop();
			printf("%c ", getVertex(w) + 'A');	// 정점 출력
			node* node = adj[w];			// 각 정점의 진입 차수를 변경
			while (node != nullptr) {
				int u = node->getId();
				inDeg[u]--;		// 진입 차수를 감소
				if (inDeg[u] == 0) {	// 진입 차수가 0인 정점을 push
					s.push(u);
				}
				node = node->getLink();	// 다음 정점
			}
		}
		printf("\n");
	}
};