#pragma once
#include <iostream>

// �迭�� ȭ�鿡 ���� ���� ����ϴ� �Լ�. ����Ʈ �Ű����� ���
static void printArray1(int arr[], int n, const char* str = "Array") {
	printf("%s = ", str);
	for (int i = 0; i < n; i++)
		printf("%3d", arr[i]);
	printf("\n");
}

// gap ��ŭ ������ ��ҵ��� ���� ����. ������ ������ first���� last
static void sortGapInsertion(int a[], int first, int last, int gap) {
	int i, j, key;
	for (i = first + gap; i <= last; i += gap) {
		key = a[i];
		for (j = i - gap; j >= first && key < a[j]; j -= gap) {
			a[j + gap] = a[j];
		}
		a[j + gap] = key;
	}
}

// �� ���� �˰����� �̿��� int �迭�� ������������ �����ϴ� �Լ�
void shellSort(int a[], int n) {
	for (int gap = n / 2; gap > 0; gap /= 2) {
		printArray1(a, n, "Shell...");
		if (gap % 2 == 0) gap++;
		for (int i = 0; i < gap; i++) {
			sortGapInsertion(a, i, n - 1, gap);
		}
	}
}