#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

intptr_t PointerPlusNum(intptr_t ptr1, ptrdiff_t num, size_t ptrsize)
{
	int* p = 0;
	p = ptr1 + (num * ptrsize);
	return p;
}

ptrdiff_t  PointerDiff(intptr_t ptr1, ptrdiff_t num, size_t ptrsize)
{
	ptrdiff_t diff = ptr1 / ptrsize - num / ptrsize;
	return diff;
}

int main()
{
	int* p1 = 4;
	int* p2 = 8;
	int num = 5;

	printf("%d\n", PointerDiff(p1, p2, sizeof(int)));
	printf("%d\n", PointerPlusNum(p1, num, sizeof(int)));
	return 0;
}

