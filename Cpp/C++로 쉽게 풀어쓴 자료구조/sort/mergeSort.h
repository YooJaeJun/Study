#pragma once

const int maxSize = 1024;

static void merge(int a[], int left, int mid, int right) {
	int i, j, k = left, l;
	static int sorted[maxSize];

	// 분할된 a의 합병
	for (i = left, j = mid + 1; i <= mid && j <= right;) {
		sorted[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];
	}
	// 한쪽에 남아있는 레코드의 일괄 복사
	if (i > mid) {
		for (l = j; l <= right; l++, k++) {
			sorted[k] = a[l];
		}
	}
	else {
		for (l = i; l <= mid; l++, k++) {
			sorted[k] = a[l];
		}
	}
	// 배열 sorted[]의 리스트를 배열 a[]로 재복사
	for (l = left; l <= right; l++) {
		a[l] = sorted[l];
	}
}

// 합병 정렬 알고리즘을 이용해 int 배열을 오름차순으로 정렬하는 함수
void mergeSort(int a[], int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;	// 리스트의 균등 분할
		mergeSort(a, left, mid);		// 부분 리스트 정렬
		mergeSort(a, mid + 1, right);	// 부분 리스트 정렬
		merge(a, left, mid, right);		// 합병
	}
}