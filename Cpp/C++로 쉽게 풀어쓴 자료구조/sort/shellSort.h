#pragma once
#include <iostream>

// 배열을 화면에 보기 좋게 출력하는 함수. 디폴트 매개변수 사용
static void printArray1(int arr[], int n, const char* str = "Array") {
	printf("%s = ", str);
	for (int i = 0; i < n; i++)
		printf("%3d", arr[i]);
	printf("\n");
}

// gap 만큼 떨어진 요소들을 삽입 정렬. 정렬의 범위는 first에서 last
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

// 셸 정렬 알고리즘을 이용해 int 배열을 오름차순으로 정렬하는 함수
void shellSort(int a[], int n) {
	for (int gap = n / 2; gap > 0; gap /= 2) {
		printArray1(a, n, "Shell...");
		if (gap % 2 == 0) gap++;
		for (int i = 0; i < gap; i++) {
			sortGapInsertion(a, i, n - 1, gap);
		}
	}
}