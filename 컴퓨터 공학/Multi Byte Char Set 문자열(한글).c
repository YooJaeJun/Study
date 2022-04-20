#include <stdio.h>
#include <string.h>

int main() {
	char str[] = "ABC한글";
	int siz = sizeof(str);
	int len = strlen(str);

	printf("배열의 크기: %d\n", siz);
	printf("문자열 길이: %d\n", len);

	for (int i = 0; i != 8; i++) {	// 6, 7, 8 해보기
		fputc(str[i], stdout);
	}

	return 0;
}