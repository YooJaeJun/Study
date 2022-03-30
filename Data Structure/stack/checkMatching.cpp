#include <iostream>
#include "arrayStack.h"
using namespace std;


/// <summary>
/// 괄호 검사
/// </summary>
bool checkMatching(const char* filename) {
	errno_t err;
	FILE* fp;
	err = fopen_s(&fp, filename, "r");
	if (err != 0) {
		error("Error: 파일이 존재하지 않습니다.");
	}

	int nLine = 1;	//읽은 라인의 개수
	int nChar = 0;	//읽은 문자의 개수
	arrayStack stack;
	char ch;

	while ((ch = getc(fp)) != EOF) {
		if (ch == '\n') {
			nLine++;
		}
		nChar++;
		if (ch == '[' || ch == '(' || ch == '{') {
			stack.push(ch);
		}
		else if (ch == ']' || ch == ')' || ch == '}') {
			int prev = stack.pop();
			if (ch == ']' && prev != '['
				|| ch == ')' && prev != '{'
				|| ch == '}' && prev != '{') {
				break;
			}
		}
	}
	fclose(fp);
	printf("[%s] 파일 검사결과: \n", filename);
	if (!stack.isEmpty()) {
		printf("Error: 문제발견!(라인수=%d, 문자수=%d)\n\n", nLine, nChar);
	}
	else {
		printf("OK: 괄호닫기정상(라인수=%d, 문자수=%d)\n\n", nLine, nChar);
	}
	return stack.isEmpty();
}

/*
void main() {
	checkMatching("스택괄호체크CheckMatching.cpp");
	checkMatching("스택배열arrayStack.h");
}
*/