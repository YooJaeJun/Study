#pragma once
#include "wGraph.h"

class wGraphFloyd : public wGraph {
	int a[maxVtxs][maxVtxs];	// 최단경로 거리
	
public:
	void shortestPathFloyd() {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				a[i][j] = getEdge(i, j);
			}
		}

		for (int k = 0; k < size; k++) {
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					if (a[i][k] + a[k][j] < a[i][j]) {
						a[i][j] = a[i][k] + a[k][j];
					}
				}
			}
			printA();
		}
	}

	void printA() {
		printf("================================\n");
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (a[i][j] == INF) { printf(" INF "); }
				else { printf("%4d ", a[i][j]); }
			}
			printf("\n");
		}
	}
};