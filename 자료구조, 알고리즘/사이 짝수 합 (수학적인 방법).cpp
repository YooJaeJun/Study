//�� ¦�� ������ �� �� - Ǯ��1
#include <stdio.h>

void ScanErrorCheck(int *n, int *m);
void EvenSum(int *n, int *m);

int main()
{
	int n, m;

	printf("�� ���� �Է�(1�̻� 10000����, ��°�� �� ū ����) : ");

	ScanErrorCheck(&n, &m);
	EvenSum(&n, &m);

	return 0;
}

void ScanErrorCheck(int *n, int *m)
{
	while (1) {
		scanf_s("%d %d", n, m);

		if (*n < 1) {
			puts("1�̻��� ������ �Է����ּ���. (�ٽ� �Է�)");
		}
		else if (*m > 10000) {
			puts("10000������ ������ �Է����ּ���. (�ٽ� �Է�)");
		}
		else if (*n > *m) {
			puts("ù ��° ������ �� ��° �������� �۾ƾ� �մϴ�. (�ٽ� �Է�)");
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



//�� ¦�� ������ �� �� - Ǯ��2
#include <stdio.h>

void ScanErrorCheck(int *n, int *m);
void EvenSum(int *n, int *m, int *sum);

int main()
{
	int n, m, sum = 0;

	printf("�� ���� �Է�(1�̻� 10000����, ��°�� �� ū ����) : ");

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
			puts("1�̻��� ������ �Է����ּ���. (�ٽ� �Է�)");
		}
		else if (*m > 10000) {
			puts("10000������ ������ �Է����ּ���. (�ٽ� �Է�)");
		}
		else if (*n > *m) {
			puts("ù ��° ������ �� ��° �������� �۰ų� ���ƾ� �մϴ�. (�ٽ� �Է�)");
		}
		else {
			break;
		}
	}
}



//������, ��������
//#define _CRT_SECURE_NO_WARNINGS
#include "Turboc.h"

//¦�� ������ �������� ���� = 2

//���������� �Ϲ����� ���ϴ� �Լ� = ù�� + (k - 1)d  . d�� ����, k�� �� index
int GetTerm(int FirstTerm, int index)
{
	return FirstTerm + 2 * index - 2; //���⼭ ���� ����d = 2
}

int main()
{
	int n = 1;
	int m = 10000;

	scanf_s("%d %d", &n, &m);

	//¦�� ���������� ù�׵� ¦������ �Ǳ⶧���� Ȧ���� + 1
	if (n % 2 == 1)
	{
		++n;
	}

	//m�� ���ų� m�� Ȧ���϶� m-1�� ¦���� ������ k��° ���� ���ϴ� ����
	 //n + 2k - 2 <= m
	 //2k <= m - n + 2
	 //k <= (m - n + 2)/2
	int MaxTermIndex = (m - n + 2) / 2;

	//���������� �� ���� = k(ù�� + ��������) / 2 
	int result = (MaxTermIndex * GetTerm(n, 1) + MaxTermIndex * GetTerm(n, MaxTermIndex)) / 2;

	printf("Result = %d \n", result);

	return 0;
}