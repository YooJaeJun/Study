#pragma once

const int maxSize = 1024;

static void merge(int a[], int left, int mid, int right) {
	int i, j, k = left, l;
	static int sorted[maxSize];

	// ���ҵ� a�� �պ�
	for (i = left, j = mid + 1; i <= mid && j <= right;) {
		sorted[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];
	}
	// ���ʿ� �����ִ� ���ڵ��� �ϰ� ����
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
	// �迭 sorted[]�� ����Ʈ�� �迭 a[]�� �纹��
	for (l = left; l <= right; l++) {
		a[l] = sorted[l];
	}
}

// �պ� ���� �˰����� �̿��� int �迭�� ������������ �����ϴ� �Լ�
void mergeSort(int a[], int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;	// ����Ʈ�� �յ� ����
		mergeSort(a, left, mid);		// �κ� ����Ʈ ����
		mergeSort(a, mid + 1, right);	// �κ� ����Ʈ ����
		merge(a, left, mid, right);		// �պ�
	}
}