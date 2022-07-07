#pragma once

inline void swap2(int& x, int& y) {
	int t = x;
	x = y;
	y = t;
}

static int partition(int a[], int left, int right) {
	int low = left;
	int high = right;
	int pivot = a[left];	// �ǹ� ����

	while (low < high) {
		while (high > low && a[high] >= pivot) {	// ���� ����Ʈ���� �ǹ����� ū ���ڵ� ����
			high--;
		}
		while (low < high && a[low] <= pivot) {	// ������ ����Ʈ���� �ǹ����� ���� ���ڵ� ����
			low++;
		}
		if (low < high) {	// ���õ� �� ���ڵ� ��ȯ
			swap2(a[low], a[high]);
		}
	}

	a[left] = a[low];
	a[low] = pivot;
	//swap2(a[left], a[high]);	// �ε��� j�� ����Ű�� ���ڵ�� �ǹ� ��ȯ
	return low;
}

// �� ���� �˰����� �̿��� �迭�� left ~ right �׸���� ������������ �����ϴ� �Լ�
void quickSort(int a[], int left, int right) {
	if (left < right) {		// ���� ������ 2�� �̻��� ���
		int q = partition(a, left, right);	// �¿�� ����
		quickSort(a, left, q - 1);	// ���� �κи���Ʈ�� �� ����
		quickSort(a, q + 1, right);	// ������ �κи���Ʈ�� �� ����
	}
}