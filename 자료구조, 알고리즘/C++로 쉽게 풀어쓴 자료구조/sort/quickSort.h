#pragma once

inline void swap2(int& x, int& y) {
	int t = x;
	x = y;
	y = t;
}

static int partition(int a[], int left, int right) {
	int low = left;
	int high = right;
	int pivot = a[left];	// 피벗 설정

	while (low < high) {
		while (high > low && a[high] >= pivot) {	// 왼쪽 리스트에서 피벗보다 큰 레코드 선택
			high--;
		}
		while (low < high && a[low] <= pivot) {	// 오른쪽 리스트에서 피벗보다 작은 레코드 선택
			low++;
		}
		if (low < high) {	// 선택된 두 레코드 교환
			swap2(a[low], a[high]);
		}
	}

	a[left] = a[low];
	a[low] = pivot;
	//swap2(a[left], a[high]);	// 인덱스 j가 가리키는 레코드와 피벗 교환
	return low;
}

// 퀵 정렬 알고리즘을 이용해 배열의 left ~ right 항목들을 오름차순으로 정렬하는 함수
void quickSort(int a[], int left, int right) {
	if (left < right) {		// 정렬 범위가 2개 이상인 경우
		int q = partition(a, left, right);	// 좌우로 분할
		quickSort(a, left, q - 1);	// 왼쪽 부분리스트를 퀵 정렬
		quickSort(a, q + 1, right);	// 오른쪽 부분리스트를 퀵 정렬
	}
}