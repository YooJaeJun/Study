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
		for (i = 0; i < n; i++) {	// 데이터들을 자릿수에 따라 큐에 삽입
			q[(list[i] / factor) % 10].push(list[i]);
		}
		
		for (int b = i = 0; b < buckets; b++) {	// bucket에서 꺼내어 list로 합친다.
			while (false == q[b].empty()) {
				list[i++] = q[b].front();
				q[b].pop();
			}
		}
		
		factor *= 10;	// 그 다음 자릿수로 간다.
	}
}