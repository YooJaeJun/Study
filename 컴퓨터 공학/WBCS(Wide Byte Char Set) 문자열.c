#include <stdio.h>
#include <string.h>

// main �Լ��� ���α׷� ���� �� ���޵Ǵ� ���ڿ��� MBCS ������� ����
// wmain �Լ��� WBCS(�����ڵ� ���)
int wmain(int argc, wchar_t* argv[]) {	
	typedef unsigned short wchar_t;
	wchar_t str[] = L"ABC";	// �����ڵ� ��� ���ڿ� ����

	int siz = sizeof(str);	// ������
	int len = strlen(str);

	printf("�迭�� ũ��: %d\n", siz);	// 8
	printf("���ڿ� ����(strlen): %d\n", len);	// "1" strlen�� SBCS(�ƽ�Ű �ڵ� ���) ���ڿ� ó�� ���
	len = wcslen(str);
	printf("���ڿ� ����(wcslen): %d\n", len);	// "3" wcslen�� WBCS(�����ڵ� ���) ���ڿ� ó�� ���

	wprintf(L"wprintf (wcslen): %d\n", len);	// �����ڵ� ��� ó���� ����

	printf("\n");
	
	for (int i = 0; i < argc; i++) {
		fputws(argv[i], stdout);
		fputws(L"\n", stdout);
	}
	return 0;
}