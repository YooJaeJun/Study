#pragma once

inline void swap1(int& x, int& y) {
	int t = x;
	x = y;
	y = t;
}

void bubbleSort(int a[], int n, int& count) {
	for (int i = n - 1; i > 0; i--) {
		bool flag = false;	// � ��ĵ���� �ڷ��� ��ȭ�� �� ���� ������ �� �̻� ��ĵ���� �ʾƵ� �ȴ�.
		for (int j = 0; j < i; j++) {
			count++;
			// �յ��� ���ڵ带 ���� �� ��ü
			if (a[j] > a[j + 1]) {
				swap1(a[j], a[j + 1]);
				flag = true;
			}
		}
		if (flag == false) {
			break;
		}
	}
}