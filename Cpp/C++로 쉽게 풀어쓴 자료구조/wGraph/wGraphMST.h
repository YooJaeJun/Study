#pragma once
// 최소 신장트리(MST) 기능이 추가된 가중치 그래프 클래스
#include "minHeap.h"
#define _CRT_SECURE_NO_WARNINGS
#include "wGraph.h"
#include "vertextSets.h"

class wGraphMST : public wGraph {
public:
	void kruskal() {
		minHeap heap;
		// 힙에 모든 간선 삽입
		for (int i = 0; i < size - 1; i++) {
			for (int j = i + 1; j < size; j++) {
				if (hasEdge(i, j)) {
					heap.insert(getEdge(i, j), i, j);
				}
			}
		}

		vertexSets set(size);	// size 개의 집합을 만듦
		int edgeAccepted = 0;	// 선택된 간선의 수
		while (edgeAccepted < size - 1) {	// 간선의 수 < (size - 1)
			heapNode e = heap.remove();		// 최소 힙에서 삭제
			int uset = set.findSet(e.getV1());	// 정점 u의 집합 번호
			int vset = set.findSet(e.getV2());	// 정점 v의 ~

			if (uset != vset) {		// 서로 속한 집합이 다르면
				printf("간선 추가: %c - %c (비용:%d)\n",
					getVertex(e.getV1()), getVertex(e.getV2()),
					e.getKey());
				set.unionSets(uset, vset);	// 두 개의 집합을 합함.
				edgeAccepted++;
			}

		}
	}

	void prim(int s) {
		bool selected[maxVtxs];		// 정점이 이미 포함되었는가
		int dist[maxVtxs];	// 거리
		for (int i = 0; i < size; i++) {	// 배열 초기화
			dist[i] = INF;
			selected[i] = false;
		}
		dist[s] = 0;	// 시작 정점

		for (int i = 0; i < size; i++) {
			// 포함되지 않은 정점들 중에서 MST와의 거리가 최소인 정점
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

	// MST에 포함되지 않은 정점들 중에서, MST와의 거리(dist)가 최소인 정점 선택
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