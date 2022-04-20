#include <stdio.h>
#include <string.h>

// main 함수는 프로그램 실행 시 전달되는 문자열을 MBCS 기반으로 구성
// wmain 함수는 WBCS(유니코드 기반)
int wmain(int argc, wchar_t* argv[]) {	
	typedef unsigned short wchar_t;
	wchar_t str[] = L"ABC";	// 유니코드 기반 문자열 선언

	int siz = sizeof(str);	// 연산자
	int len = strlen(str);

	printf("배열의 크기: %d\n", siz);	// 8
	printf("문자열 길이(strlen): %d\n", len);	// "1" strlen은 SBCS(아스키 코드 기반) 문자열 처리 기반
	len = wcslen(str);
	printf("문자열 길이(wcslen): %d\n", len);	// "3" wcslen은 WBCS(유니코드 기반) 문자열 처리 기반

	wprintf(L"wprintf (wcslen): %d\n", len);	// 유니코드 기반 처리를 위함

	printf("\n");
	
	for (int i = 0; i < argc; i++) {
		fputws(argv[i], stdout);
		fputws(L"\n", stdout);
	}
	return 0;
}