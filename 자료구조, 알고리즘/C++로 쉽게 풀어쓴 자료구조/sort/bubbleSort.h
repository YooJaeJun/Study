#pragma once

inline void swap1(int& x, int& y) {
	int t = x;
	x = y;
	y = t;
}

void bubbleSort(int a[], int n, int& count) {
	for (int i = n - 1; i > 0; i--) {
		bool flag = false;	// 어떤 스캔에서 자료의 변화가 한 번도 없으면 더 이상 스캔하지 않아도 된다.
		for (int j = 0; j < i; j++) {
			count++;
			// 앞뒤의 레코드를 비교한 후 교체
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