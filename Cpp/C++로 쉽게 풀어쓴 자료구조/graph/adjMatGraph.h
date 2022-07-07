#pragma once
#define _CRT_SECURE_NO_WARNINGS
// 인접 행렬을 이용한 그래프 클래스
#include <cstdio>
const int maxVtxs = 256;	// 표현 가능한 최대 정점의 개수

class adjMatGraph {
protected:
	int size;					// 정점의 개수
	char vertices[maxVtxs];		// 정점의 이름
	int adj[maxVtxs][maxVtxs];	// 인접 행렬

public:
	adjMatGraph() { reset(); }
	char getVertex(int i) { return vertices[i]; }
	int getEdge(int i, int j) { return adj[i][j]; }
	void setEdge(int i, int j, int val) { adj[i][j] = val; }

	bool isEmpty() { return size == 0; }
	bool isFull() { return size == maxVtxs - 1; }

	// 그래프 초기화 => 공백 상태의 그래프
	void reset() {
		size = 0;
		for (int i = 0; i < maxVtxs; i++) {
			for (int j = 0; j < maxVtxs; j++) {
				setEdge(i, j, 0);
			}
		}
	}

	// 정점 삽입 연산
	void insertVertex(char name) {
		if (false == isFull()) { vertices[size++] = name; }
		else { printf("Error: 그래프 정점 개수 초과\n"); }
	}

	// 간선 삽입 연산: 무방향 크래프의 경우임. (방향, 가중치 그래프에서는 수정)
	void insertEdge(int u, int v) {
		setEdge(u, v, 1);
		setEdge(v, u, 1);
	}

	// 그래프 정보를 출력함 (화면이나 파일에 출력)
	void display(FILE* fp = stdout) {
		fprintf(fp, "%d\n", size);				// 정점의 개수 출력
		for (int i = 0; i < size; i++) {		// 각 행의 정보 출력
			fprintf(fp, "%c ", getVertex(i));	// 정점의 이름 출력
			for (int j = 0; j < size; j++) {	// 간선 정보 출력
				fprintf(fp, "%3d", getEdge(i, j));
			}
			fprintf(fp, "\n");
		}
	}

	void load(const char* filename) {
		FILE* fp = fopen(filename, "r");
		if (fp != nullptr) {
			int n;
			fscanf_s(fp, "%d", &n);		// 정점의 전체 개수
			for (int i = 0; i < n; i++) {
				char str[80];
				fscanf(fp, "%s", str);	// 정점의 이름
				insertVertex(str[0]);	// 정점 삽입
				for (int j = 0; j < n; j++) {
					int val;
					fscanf(fp, "%d", &val);	// 간선 정보
					if (val != 0) {		// 간선이 있으면
						insertEdge(i, j);		// 간선 삽입
					}
				}
			}
			fclose(fp);
		}
	}

	// 파일 저장 함수
	void store(const char* filename) {
		FILE* fp = fopen(filename, "w");
		if (fp != nullptr) {
			display(fp);
			fclose(fp);
		}
	}
};