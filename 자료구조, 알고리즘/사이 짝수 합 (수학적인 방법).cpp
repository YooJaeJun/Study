//두 짝수 사이의 수 합 - 풀이1
#include <stdio.h>

void ScanErrorCheck(int *n, int *m);
void EvenSum(int *n, int *m);

int main()
{
	int n, m;

	printf("두 정수 입력(1이상 10000이하, 둘째가 더 큰 정수) : ");

	ScanErrorCheck(&n, &m);
	EvenSum(&n, &m);

	return 0;
}

void ScanErrorCheck(int *n, int *m)
{
	while (1) {
		scanf_s("%d %d", n, m);

		if (*n < 1) {
			puts("1이상의 정수를 입력해주세요. (다시 입력)");
		}
		else if (*m > 10000) {
			puts("10000이하의 정수를 입력해주세요. (다시 입력)");
		}
		else if (*n > *m) {
			puts("첫 번째 정수는 두 번째 정수보다 작아야 합니다. (다시 입력)");
		}
		else {
			break;
		}
	}
}
void EvenSum(int *n, int *m)
{
	int sum = 0;
	for (int i = *n; i <= *m; i++) {
		if (i % 2 == 0) {
			sum += i;
		}
	}
	printf("%d", sum);
}



//두 짝수 사이의 수 합 - 풀이2
#include <stdio.h>

void ScanErrorCheck(int *n, int *m);
void EvenSum(int *n, int *m, int *sum);

int main()
{
	int n, m, sum = 0;

	printf("두 정수 입력(1이상 10000이하, 둘째가 더 큰 정수) : ");

	ScanErrorCheck(&n, &m);
	EvenSum(&n, &m, &sum);

	printf("%d", sum);
	return 0;
}
void EvenSum(int *n, int *m, int *sum)
{
	if (*n > *m) {
		return;
	}
	else {
		if (*n % 2 == 0) {
			*sum += *n;
		}
		*n = *n + 1;
		EvenSum(n, m, sum);
	}
}

void ScanErrorCheck(int *n, int *m)
{
	while (1) {
		scanf_s("%d %d", n, m);

		if (*n < 1) {
			puts("1이상의 정수를 입력해주세요. (다시 입력)");
		}
		else if (*m > 10000) {
			puts("10000이하의 정수를 입력해주세요. (다시 입력)");
		}
		else if (*n > *m) {
			puts("첫 번째 정수는 두 번째 정수보다 작거나 같아야 합니다. (다시 입력)");
		}
		else {
			break;
		}
	}
}



//용진님, 등차수열
//#define _CRT_SECURE_NO_WARNINGS
#include "Turboc.h"

//짝수 수열의 등차수열 공차 = 2

//등차수열의 일반항을 구하는 함수 = 첫항 + (k - 1)d  . d는 공차, k는 항 index
int GetTerm(int FirstTerm, int index)
{
	return FirstTerm + 2 * index - 2; //여기서 쓰인 공차d = 2
}

int main()
{
	int n = 1;
	int m = 10000;

	scanf_s("%d %d", &n, &m);

	//짝수 등차수열의 첫항도 짝수여야 되기때문에 홀수면 + 1
	if (n % 2 == 1)
	{
		++n;
	}

	//m과 같거나 m이 홀수일때 m-1의 짝수가 나오는 k번째 항을 구하는 로직
	 //n + 2k - 2 <= m
	 //2k <= m - n + 2
	 //k <= (m - n + 2)/2
	int MaxTermIndex = (m - n + 2) / 2;

	//등차수열의 합 공식 = k(첫항 + 마지막항) / 2 
	int result = (MaxTermIndex * GetTerm(n, 1) + MaxTermIndex * GetTerm(n, MaxTermIndex)) / 2;

	printf("Result = %d \n", result);

	return 0;
}