#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

#define SWAP(a, b) { int t; t=a; a=b; b=t; }

//병합 정렬
void merge_sort(int data[], int start, int mid, int end) {
	int i = start;
	int j = mid + 1;
	int k = start;
	int temp[9];

	while (i <= mid && j <= end) {
		if (data[i] <= data[j]) {
			temp[k] = data[i++];
		}
		else {
			temp[k] = data[j++];
		}
		k++;
	}
	if (i > mid) {
		for (int t = j; t <= end; t++) {
			temp[k++] = data[t];
		}
	}
	else {
		for (int t = i; t <= mid; t++) {
			temp[k++] = data[t];
		}
	}
	//정렬된 배열을 삽입
	for (int t = start; t <= end; t++) {
		data[t] = temp[t];
	}
}
void merge(int data[], int start, int end) {
	if (start < end) {
		int mid = (start + end) / 2;
		merge(data, start, mid);	//좌측 정렬
		merge(data, mid + 1, end);	//우측 정렬
		merge_sort(data, start, mid, end);
	}
}


//병합 정렬 - b 필요, 바텀업
void copy_array(int b[], int a[], int n) {
	for (int i = 0; i < n; i++) {
		a[i] = b[i];
	}
}
void bottom_up_merge(int a[], int iLeft, int iRight, int iEnd, int b[]) {
	int i = iLeft;
	int j = iRight;
	for (int k = iLeft; k < iEnd; k++) {
		if (i < iRight && (j >= iEnd || a[i] <= a[j])) {
			b[k] = a[i++];
		}
		else {
			b[k] = a[j++];
		}
	}
}
void bottom_up_merge_sort(int a[], int b[], int n) {
	for (int width = 1; width < n; width = 2 * width) {
		for (int i = 0; i < n; i = i + 2 * width) {
			bottom_up_merge(a, i, min(i + width, n), min(i + 2 * width, n), b);
		}
		copy_array(b, a, n);
	}
}

//병합 정렬 - b 필요, 탑다운
void top_down_merge_sort(int a[], int low, int high, int b[]) {
	//1 이미 정렬됨
	if (low >= high) return;
	//2 분할
	int mid = (low + high) / 2;
	//3 정복
	top_down_merge_sort(a, low, mid, b);
	top_down_merge_sort(a, mid + 1, high, b);
	//4 결합
	int i = low, j = mid + 1, k = low;
	for (; k <= high; ++k) {
		if (j > high) b[k] = a[i++];
		else if (i > mid) b[k] = a[j++];
		else if (a[i] <= a[j]) b[k] = a[i++];
		else b[k] = a[j++];
	}
	//5 복사
	for (i = low; i <= high; ++i) a[i] = b[i];
}


//퀵 정렬 - int 배열
void quick_sort(int a[], int low, int high) {
	if (low >= high) return;

	int i = low, j = low;
	int& pivot = a[high];
	for (; j < high; ++j) {
		if (a[j] < pivot) {
			swap(a[i++], a[j]);
		}
	}
	swap(a[i], pivot);

	quick_sort(a, low, i - 1);
	quick_sort(a, i + 1, high);
}

//표준 퀵소트 필요 함수
int compare(const void* a, const void* b) {
	if (*(char*)a == *(char*)b) return 0;
	if (*(char*)a > *(char*)b) return 1;
	return -1;
}

//퀵 정렬
void QuickSort(char* ar, int size) {
	int left, right;
	char key;

	//구간이 1이면 정렬 끝
	if (size <= 1) return;

	//기준값 결정 : 배열상의 제일 끝 요소
	key = ar[size - 1];
	for (left = 0, right = size - 2;; left++, right--) {
		while (ar[left] < key) { left++; }
		while (ar[right] > key) { right--; }
		if (left >= right) break;	//좌우가 만나면 끝
		SWAP(ar[left], ar[right]);
	}
	SWAP(ar[left], ar[size - 1]);	//기준값과 i위치의 값 교환

	QuickSort(ar, left);	//왼쪽 구간 정렬
	QuickSort(ar + left + 1, size - left - 1);	//오른쪽 구간 정렬
}


//삽입정렬
void InsertionSort(char* ar, int size) {
	int i, j;
	char temp;

	//두 번째 요소부터 끝까지 순회
	for (i = 1; i != size; i++) {
		//앞쪽으로 이동하면서 자기보다 큰 값을 한 칸씩 오른쪽으로 이동한다.
		for (temp = ar[i], j = i; j > 0; j--) {
			if (ar[j - 1] > temp) {
				ar[j] = ar[j - 1];
			}
			else {
				break;
			}
		}
		//자기보다 크지 않은 최초의 칸 자리에 자신을 삽입한다.
		ar[j] = temp;
	}
}

//선택정렬
void SelectionSort(char* ar, int size) {
	int minidx;
	int i, j;
	//배열 전체 순회
	for (i = 0; i != size - 1; i++) {
		//i 이후의 최소값을 찾는다.
		for (minidx = i, j = i + 1; j != size; j++) {
			if (ar[minidx] > ar[j]) {
				minidx = j;
			}
		}
		//최소값을 현재항과 교환.
		if (minidx != i) {
			SWAP(ar[minidx], ar[i]);
		}
	}
}
//버블정렬 플래그
void BubbleSort_flag(char* ar, int size) {
	bool is_change;

	for (int i = 0; i != size - 1; i++) {
		is_change = false;
		for (int j = 1; j != size - i; j++) {
			if (ar[j - 1] > ar[j]) {
				SWAP(ar[j - 1], ar[j]);
				is_change = true;
			}
		}
		if (!is_change) break;
	}
}
//버블정렬
void BubbleSort(char* ar, int size) {
	for (int i = 0; i != size - 1; i++) {
		for (int j = 1; j != size - i; j++) {
			if (ar[j - 1] > ar[j]) {
				SWAP(ar[j - 1], ar[j]);
			}
		}
	}
}

int main() {
	/*
	char str[] = "complete";

	printf("정렬 전의 문자열 : %s\n", str);
	InsertionSort(str, strlen(str));
	printf("정렬된 문자열 : %s\n", str);

	int a[] = { 5,2,4,6,1,3,19,8,7,11 };
	quick_sort(a, 0, 9);
	for (int i = 0; i != 10; i++) {
		printf("정렬된 int 배열 : %d\n", a[i]);
	}*/

	int data[8] = { 3,6,7,1,2,4,8,5 };
	merge(data, 0, 7);
	for (int i = 0; i != 8; i++) {
		cout << data[i] << " ";
	}
	return 0;
}