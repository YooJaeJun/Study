#pragma once
#include "wGraph.h"
class wGraphDijkstra : public wGraph {
	int dist[maxVtxs];	// ���۳��κ����� �ִܰ�� �Ÿ�
	int found[maxVtxs];	// �湮�� ���� ǥ��
	
public:
	// �湮���� ���� ������ �߿��� �ִܰ�� �Ÿ��� ���� ���� ������ ã�� ��ȯ
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

	// Dijkstra�� �ִ� ��� �˰���: start �������� ������.
	void shortestPath(int start) {
		// �ʱ�ȭ
		for (int i = 0; i < size; i++) {
			dist[i] = getEdge(start, i);
			found[i] = false;
		}
		found[start] = true;	// ���۳�� �湮 ǥ��
		dist[start] = 0;	// ���� �Ÿ�
		for (int i = 0; i < size; i++) {	// ��� ������ s�� ���Ե��� ���� ������.
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

	void printDistance() {	// dist ���¸� ����ϴ� �Լ�
		for (int i = 0; i < size; i++) {
			printf("%5d", dist[i]);
		}
		printf("\n");

	}
};