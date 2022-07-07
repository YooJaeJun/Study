#pragma once
#include "wGraph.h"
class wGraphDijkstra : public wGraph {
	int dist[maxVtxs];	// 시작노드로부터의 최단경로 거리
	int found[maxVtxs];	// 방문한 정점 표시
	
public:
	// 방문하지 않은 정점들 중에서 최단경로 거리가 가장 작은 정점을 찾아 반환
	int chooseVertex() {
		int min = INF;
		int minpos = -1;
		for (int i = 0; i < size; i++) {
			if (dist[i] < min && false == found[i]) {
				min = dist[i];
				minpos = i;
			}
		}
		return minpos;
	}

	// Dijkstra의 최단 경로 알고리즘: start 정점에서 시작함.
	void shortestPath(int start) {
		// 초기화
		for (int i = 0; i < size; i++) {
			dist[i] = getEdge(start, i);
			found[i] = false;
		}
		found[start] = true;	// 시작노드 방문 표시
		dist[start] = 0;	// 최초 거리
		for (int i = 0; i < size; i++) {	// 모든 정점이 s에 포함되지 않을 때까지.
			printf("Step%2d:", i + 1);
			printDistance();
			int u = chooseVertex();
			found[u] = true;
			for (int w = 0; w < size; w++) {
				if (found[w] == false) {
					if (dist[u] + getEdge(u, w) < dist[w]) {
						dist[w] = dist[u] + getEdge(u, w);
					}
				}
			}
		}
	}

	void printDistance() {	// dist 상태를 출력하는 함수
		for (int i = 0; i < size; i++) {
			printf("%5d", dist[i]);
		}
		printf("\n");

	}
};