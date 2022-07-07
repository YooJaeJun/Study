#pragma once
#include "srchAMGraph.h"

class connectedComponentGraph : public srchAMGraph {
	int label[maxVtxs];		// ������ ���� �ʵ� �߰�
public:
	// ���� �켱 Ž��
	void labelDFS(int v, int color) {
		visited[v] = true;
		label[v] = color;	// ���� ������ ����
		for (int w = 0; w < size; w++) {
			if (isLinked(v, w) && visited[w] == false) {
				labelDFS(w, color);
			}
		}
	}

	// �׷����� ���� ���� ���� �Լ�
	void findConnectedComponent() {
		int count = 0;	// ���� ������ ��
		for (int i = 0; i < size; i++) {
			if (visited[i] == false) {
				labelDFS(i, ++count);
			}
		}
		printf("�׷��� ���Ἲ�� ���� = %d\n", count);
		for (int i = 0; i < size; i++) {
			printf("%c=%d ", getVertex(i), label[i]);
		}
		printf("\n");
	}
};