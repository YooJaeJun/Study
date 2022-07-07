#pragma once

void insertionSort(int a[], int n)
{
	for (int i = 1; i < n; i++) {
		int key = a[i];
		int j;
		for (j = i - 1; j >= 0 && a[j] > key; j--) {
			a[j + 1] = a[j];	// ���ڵ��� ������ �̵�
		}
		a[j + 1] = key;
	}
}

inline int ascend(int x, int y) { return y - x; }	// �������� ���Լ�
inline int descend(int x, int y) { return x - y; }	// �������� ���Լ�

// �Լ� �����͸� �Ű������� �޴� �������� �Լ�
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
