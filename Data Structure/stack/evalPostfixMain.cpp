#include <iostream>
#include "operandStack.h"
using namespace std;


/// <summary>
/// 사칙연산 후위 표기 수식
/// </summary>
double calcPostfixExpr(FILE *fp = stdin) {
	char c;
	operandStack st;

	while ((c = getc(fp)) != '\n') {
		if (c == '+' || c == '-' || c == '*' || c == '/') {
			double val2 = st.pop();
			double val1 = st.pop();
			switch (c) {
			case '+': st.push(val1 + val2);	break;
			case '-': st.push(val1 - val2);	break;
			case '*': st.push(val1 * val2);	break;
			case '/': st.push(val1 / val2);	break;
			}
		}
		else if (c >= '0' && c <= '9') {	//피연산자(숫자)의 시작이면
			ungetc(c, fp);	//문자를 입력 버퍼에 돌려주고
			double val;
			fscanf_s(fp, "%lf", &val);	//double로 다시 읽음
			st.push(val);
		}
	}
	return st.pop();
}

/*
void main() {
	printf("수식 입력 (Postfix)= ");
	printf("계산 결과 => %f\n", calcPostfixExpr());
}
*/