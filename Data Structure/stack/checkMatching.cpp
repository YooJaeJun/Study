#include <iostream>
#include "arrayStack.h"
using namespace std;


/// <summary>
/// ��ȣ �˻�
/// </summary>
bool checkMatching(const char* filename) {
	errno_t err;
	FILE* fp;
	err = fopen_s(&fp, filename, "r");
	if (err != 0) {
		error("Error: ������ �������� �ʽ��ϴ�.");
	}

	int nLine = 1;	//���� ������ ����
	int nChar = 0;	//���� ������ ����
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
	printf("[%s] ���� �˻���: \n", filename);
	if (!stack.isEmpty()) {
		printf("Error: �����߰�!(���μ�=%d, ���ڼ�=%d)\n\n", nLine, nChar);
	}
	else {
		printf("OK: ��ȣ�ݱ�����(���μ�=%d, ���ڼ�=%d)\n\n", nLine, nChar);
	}
	return stack.isEmpty();
}

/*
void main() {
	checkMatching("���ð�ȣüũCheckMatching.cpp");
	checkMatching("���ù迭arrayStack.h");
}
*/