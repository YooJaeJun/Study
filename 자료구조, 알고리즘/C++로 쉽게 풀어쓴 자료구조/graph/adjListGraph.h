#pragma once
#define _CRT_SECURE_NO_WARNINGS
// 인접 리스트를 이용한 그래프 클래스
#include <cstdio>
#include "node.h"
const int maxVtxs = 256;	// 표현 가능한 최대 정점의 개수

class adjListGraph {
protected:
	int size;					// 정점의 개수
	char vertices[maxVtxs];		// 정점 정보 (응용에 따라 확장 필요)
	node* adj[maxVtxs];	// 각 정점의 인접 리스트

public:
	adjListGraph() : size(0) { }
	~adjListGraph() { reset(); }
	void reset() {
		for (int i = 0; i < size; i++) {
			if (adj[i] != nullptr) { delete adj[i]; }
		}
		size = 0;
	}
	bool isEmpty() { return size == 0; }
	bool isFull() { return size >= maxVtxs; }
	char getVertex(int i) { return vertices[i]; }

	// 정점 삽입 연산
	void insertVertex(char val) {
		if (false == isFull()) { 
			vertices[size] = val;
			adj[size++] = nullptr;
		}
		else { printf("Error: 그래프 정점 개수 초과\n"); }
	}

	// 간선 삽입 연산
	void insertEdge(int u, int v) {
		adj[u] = new node(v, adj[u]);	// 인접 리스트에 추가
		//adj[v] = new node(u, adj[v]);	// 방향 그래프 ==> 주석 처리함
	}

	// 그래프 정보를 출력함 (화면이나 파일에 출력)
	void display(FILE* fp = stdout) {
		printf("%d\n", size);					// 정점의 개수 출력
		for (int i = 0; i < size; i++) {		// 각 행의 정보 출력
			printf("%c ", getVertex(i));		// 정점의 이름 출력
			for (node* v = adj[i]; v != nullptr; v = v->getLink()) {
				// 인접한 정점
				// printf("%c", getVertex(v->getId()));	// 정점 이름('A'..)로 쓰고 싶을 때
				printf("%3d", v->getId());		// 인덱스로 쓰고 싶을 때
			}
			printf("\n");
		}
	}

	node* adjacent(int v) { return adj[v]; }

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
};