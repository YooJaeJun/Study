#pragma once
#include "srchAMGraph.h"

class connectedComponentGraph : public srchAMGraph {
	int label[maxVtxs];		// 정점의 색상 필드 추가
public:
	// 깊이 우선 탐색
	void labelDFS(int v, int color) {
		visited[v] = true;
		label[v] = color;	// 현재 정점의 색상
		for (int w = 0; w < size; w++) {
			if (isLinked(v, w) && visited[w] == false) {
				labelDFS(w, color);
			}
		}
	}

	// 그래프의 연결 성분 검출 함수
	void findConnectedComponent() {
		int count = 0;	// 연결 성분의 수
		for (int i = 0; i < size; i++) {
			if (visited[i] == false) {
				labelDFS(i, ++count);
			}
		}
		printf("그래프 연결성분 개수 = %d\n", count);
		for (int i = 0; i < size; i++) {
			printf("%c=%d ", getVertex(i), label[i]);
		}
		printf("\n");
	}
};