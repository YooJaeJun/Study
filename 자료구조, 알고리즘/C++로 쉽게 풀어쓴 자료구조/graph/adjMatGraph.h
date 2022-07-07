#pragma once
#define _CRT_SECURE_NO_WARNINGS
// ���� ����� �̿��� �׷��� Ŭ����
#include <cstdio>
const int maxVtxs = 256;	// ǥ�� ������ �ִ� ������ ����

class adjMatGraph {
protected:
	int size;					// ������ ����
	char vertices[maxVtxs];		// ������ �̸�
	int adj[maxVtxs][maxVtxs];	// ���� ���

public:
	adjMatGraph() { reset(); }
	char getVertex(int i) { return vertices[i]; }
	int getEdge(int i, int j) { return adj[i][j]; }
	void setEdge(int i, int j, int val) { adj[i][j] = val; }

	bool isEmpty() { return size == 0; }
	bool isFull() { return size == maxVtxs - 1; }

	// �׷��� �ʱ�ȭ => ���� ������ �׷���
	void reset() {
		size = 0;
		for (int i = 0; i < maxVtxs; i++) {
			for (int j = 0; j < maxVtxs; j++) {
				setEdge(i, j, 0);
			}
		}
	}

	// ���� ���� ����
	void insertVertex(char name) {
		if (false == isFull()) { vertices[size++] = name; }
		else { printf("Error: �׷��� ���� ���� �ʰ�\n"); }
	}

	// ���� ���� ����: ������ ũ������ �����. (����, ����ġ �׷��������� ����)
	void insertEdge(int u, int v) {
		setEdge(u, v, 1);
		setEdge(v, u, 1);
	}

	// �׷��� ������ ����� (ȭ���̳� ���Ͽ� ���)
	void display(FILE* fp = stdout) {
		fprintf(fp, "%d\n", size);				// ������ ���� ���
		for (int i = 0; i < size; i++) {		// �� ���� ���� ���
			fprintf(fp, "%c ", getVertex(i));	// ������ �̸� ���
			for (int j = 0; j < size; j++) {	// ���� ���� ���
				fprintf(fp, "%3d", getEdge(i, j));
			}
			fprintf(fp, "\n");
		}
	}

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

	// ���� ���� �Լ�
	void store(const char* filename) {
		FILE* fp = fopen(filename, "w");
		if (fp != nullptr) {
			display(fp);
			fclose(fp);
		}
	}
};