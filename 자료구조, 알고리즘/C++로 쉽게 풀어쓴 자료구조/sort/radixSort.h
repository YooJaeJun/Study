#pragma once
#include <queue>
using namespace std;
const int buckets = 10;
const int digits = 4;

void radixSort(int list[], int n) {
	queue<int> q[buckets];
	int factor = 1;
	for (int d = 0; d < digits; d++) {
		int i;
		for (i = 0; i < n; i++) {	// �����͵��� �ڸ����� ���� ť�� ����
			q[(list[i] / factor) % 10].push(list[i]);
		}
		
		for (int b = i = 0; b < buckets; b++) {	// bucket���� ������ list�� ��ģ��.
			while (false == q[b].empty()) {
				list[i++] = q[b].front();
				q[b].pop();
			}
		}
		
		factor *= 10;	// �� ���� �ڸ����� ����.
	}
}