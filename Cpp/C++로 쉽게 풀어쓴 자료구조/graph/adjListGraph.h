#pragma once
#define _CRT_SECURE_NO_WARNINGS
// ���� ����Ʈ�� �̿��� �׷��� Ŭ����
#include <cstdio>
#include "node.h"
const int maxVtxs = 256;	// ǥ�� ������ �ִ� ������ ����

class adjListGraph {
protected:
	int size;					// ������ ����
	char vertices[maxVtxs];		// ���� ���� (���뿡 ���� Ȯ�� �ʿ�)
	node* adj[maxVtxs];	// �� ������ ���� ����Ʈ

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

	// ���� ���� ����
	void insertVertex(char val) {
		if (false == isFull()) { 
			vertices[size] = val;
			adj[size++] = nullptr;
		}
		else { printf("Error: �׷��� ���� ���� �ʰ�\n"); }
	}

	// ���� ���� ����
	void insertEdge(int u, int v) {
		adj[u] = new node(v, adj[u]);	// ���� ����Ʈ�� �߰�
		//adj[v] = new node(u, adj[v]);	// ���� �׷��� ==> �ּ� ó����
	}

	// �׷��� ������ ����� (ȭ���̳� ���Ͽ� ���)
	void display(FILE* fp = stdout) {
		printf("%d\n", size);					// ������ ���� ���
		for (int i = 0; i < size; i++) {		// �� ���� ���� ���
			printf("%c ", getVertex(i));		// ������ �̸� ���
			for (node* v = adj[i]; v != nullptr; v = v->getLink()) {
				// ������ ����
				// printf("%c", getVertex(v->getId()));	// ���� �̸�('A'..)�� ���� ���� ��
				printf("%3d", v->getId());		// �ε����� ���� ���� ��
			}
			printf("\n");
		}
	}

	node* adjacent(int v) { return adj[v]; }

	void load(const char* filename) {
		FILE* fp = fopen(filename, "r");
		if (fp != nullptr) {
			int n;
			fscanf_s(fp, "%d", &n);		// ������ ��ü ����
			for (int i = 0; i < n; i++) {
				char str[80];
				fscanf(fp, "%s", str);	// ������ �̸�
				insertVertex(str[0]);	// ���� ����
				for (int j = 0; j < n; j++) {
					int val;
					fscanf(fp, "%d", &val);	// ���� ����
					if (val != 0) {		// ������ ������
						insertEdge(i, j);		// ���� ����
					}
				}
			}
			fclose(fp);
		}
	}
};