#include <iostream>
#include <random>
#include "selectionSort.h"
#include "insertionSort.h"
#include <cstring>	// memcpy()를 위함 <memory.h>를 포함해도 됨.
#include "bubbleSort.h"
#include "shellSort.h"
#include "mergeSort.h"
#include "quickSort.h"
#include "heapSort.h"
#include "radixSort.h"


// 랜덤 함수를 이용하여 int 배열을 0~max-1의 값으로 무작위로 채우는 함수
static void initRandom(int list[], int n, int max = 1e9) {
	for (int i = 0; i < n; i++) {
		list[i] = rand() % max;
	}
}

// 배열을 화면에 보기 좋게 출력하는 함수. 디폴트 매개변수 사용
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

// 정렬 알고리즘 테스트를 위한 주 함수
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
	memcpy(org, list, n * sizeof(int));	// 정렬 전 배열 내용을 출력
	insertionSortFn(list, n, ascend);	// 오름차순 선택정렬
	printArray(list, n, "Insert-As");	// 정렬 후 배열 내용을 출력

	memcpy(org, list, n * sizeof(int));	// 정렬 전 배열 내용을 출력
	insertionSortFn(list, n, descend);	// 오름차순 선택정렬
	printArray(list, n, "Insert-De");	// 정렬 후 배열 내용을 출력
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