#include <stdio.h>
#include <string.h>

int main() {
	char str[] = "ABC�ѱ�";
	int siz = sizeof(str);
	int len = strlen(str);

	printf("�迭�� ũ��: %d\n", siz);
	printf("���ڿ� ����: %d\n", len);

	for (int i = 0; i != 8; i++) {	// 6, 7, 8 �غ���
		fputc(str[i], stdout);
	}

	return 0;
}