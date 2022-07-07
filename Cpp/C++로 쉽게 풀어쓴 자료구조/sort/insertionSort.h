#pragma once

void insertionSort(int a[], int n)
{
	for (int i = 1; i < n; i++) {
		int key = a[i];
		int j;
		for (j = i - 1; j >= 0 && a[j] > key; j--) {
			a[j + 1] = a[j];	// 레코드의 오른쪽 이동
		}
		a[j + 1] = key;
	}
}

inline int ascend(int x, int y) { return y - x; }	// 오름차순 비교함수
inline int descend(int x, int y) { return x - y; }	// 내림차순 비교함수

// 함수 포인터를 매개변수로 받는 삽입정렬 함수
void insertionSortFn(int a[], int n, int (*f)(int, int)) {
	for (int i = 1; i < n; i++) {
		int key = a[i];
		int j;
		for (j = i - 1; j >= 0 && f(a[j], key) < 0; j--) {
			a[j + 1] = a[j];
		}
		a[j + 1] = key;
	}
}
