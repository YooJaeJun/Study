#include <iostream>
#include <random>
#include "selectionSort.h"
#include "insertionSort.h"
#include <cstring>	// memcpy()�� ���� <memory.h>�� �����ص� ��.
#include "bubbleSort.h"
#include "shellSort.h"
#include "mergeSort.h"
#include "quickSort.h"
#include "heapSort.h"
#include "radixSort.h"


// ���� �Լ��� �̿��Ͽ� int �迭�� 0~max-1�� ������ �������� ä��� �Լ�
static void initRandom(int list[], int n, int max = 1e9) {
	for (int i = 0; i < n; i++) {
		list[i] = rand() % max;
	}
}

// �迭�� ȭ�鿡 ���� ���� ����ϴ� �Լ�. ����Ʈ �Ű����� ���
static void printArray(int arr[], int n, const char* str = "Array") {
	printf("%s = ", str);
	for (int i = 0; i < n; i++)
		printf("%3d ", arr[i]);
	printf("\n");
}

int compare(const void* arg1, const void* arg2) {
	if (*(double*)arg1 > *(double*)arg2) return 1;
	else if (*(double*)arg1 < *(double*)arg2) return -1;
	else return 0;
}

// ���� �˰��� �׽�Ʈ�� ���� �� �Լ�
int main() {
	int list[16];
	int n = 16;
	initRandom(list, n);
	printArray(list, n, "Original");

	// selectionSort(list, n);
	// printArray(list, n, "Selection");
	
	//insertionSort(list, n);
	//printArray(list, n, "Insertion");
	/*
	int org[16] = {0,};
	memcpy(org, list, n * sizeof(int));	// ���� �� �迭 ������ ���
	insertionSortFn(list, n, ascend);	// �������� ��������
	printArray(list, n, "Insert-As");	// ���� �� �迭 ������ ���

	memcpy(org, list, n * sizeof(int));	// ���� �� �迭 ������ ���
	insertionSortFn(list, n, descend);	// �������� ��������
	printArray(list, n, "Insert-De");	// ���� �� �迭 ������ ���
	*/
	/*
	int count = 0;
	bubbleSort(list, n, count);
	printf("count: %i \n", count);
	printArray(list, n, "Bubble");
	*/
	
	//shellSort(list, n);
	//printArray(list, n, "Shell");

	//mergeSort(list, 0, n - 1);
	//printArray(list, n, "Merge");

	// quickSort(list, 0, n - 1);
	// printArray(list, n, "Quick");

	/*
	double listDouble[5]{ 2.1, 0.9, 1.6, 3.8, 1.2 };;
	qsort((void*)listDouble, 5, sizeof(double), compare);
	for (int i = 0; i < 5; i++) {
		printf("%f ", listDouble[i]);
	}
	*/

	/*
	heapSortDec(list, n);
	printArray(list, n, "Max Heap...");

	heapSortInc(list, n);
	printArray(list, n, "Min Heap...");
	*/

	radixSort(list, n);
	printArray(list, n, "Radix...");

	return 0;
}