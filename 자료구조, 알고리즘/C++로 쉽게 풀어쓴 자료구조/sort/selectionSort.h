#pragma once

inline void swap(int& x, int& y) {
	int t = x;
	x = y;
	y = t;
}

void selectionSort(int a[], int n) {
	for (int i = 0; i < n - 1; i++) {
		int least = i;
		for (int j = i + 1; j < n; j++) {
			if (a[j] < a[least]) {
				least = j;
			}
		}
		swap(a[i], a[least]);
	}
}