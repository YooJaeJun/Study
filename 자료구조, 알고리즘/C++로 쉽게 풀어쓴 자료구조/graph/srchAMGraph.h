#pragma once
// 인접 행렬로 표현된 그래프
#include "adjMatGraph.h"
#include "circularQueue.h"

class srchAMGraph : public adjMatGraph {
protected:
	bool visited[maxVtxs];
public:
	void resetVisited() {	// 모든 정점을 방문하지 않았다고 설정
		for (int i = 0; i < size; i++) {
			visited[i] = false;
		}
	}

	bool isLinked(int u, int v) { return getEdge(u, v) != 0; }

	// 깊이 우선 탐색 함수
	void dfs(int v) {
		visited[v] = true;
		printf("%c ", getVertex(v));

		for (int w = 0; w < size; w++) {
			if (isLinked(v, w) && visited[w] == false) {
				dfs(w);
			}
		}
	}

	// 너비 우선 탐색
	void bfs(int v) {
		visited[v] = true;
		printf("%c ", getVertex(v));	// 정점의 이름 출력

		circularQueue que;
		que.enqueue(v);	// 시작 지점을 큐에 저장

		while (false == que.isEmpty()) {
			int v = que.dequeue();	// 큐에 정점 추출
			for (int w = 0; w < size; w++) {
				if (isLinked(v, w) && visited[w] == false) {
					visited[w] = true;
					printf("%c ", getVertex(w));	// 정점의 이름 출력
					que.enqueue(w);
				}
			}
		}
	}
};