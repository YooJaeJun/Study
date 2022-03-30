#include "arrayStack.h"

//객체의 우선순위 계산
inline int precedence(char op) {
	switch (op) {
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*': case '/': return 2;	//우선순위 높음
	}
	return -1;
}

//중위 표기 수식 -> 후위 표기 수식 변환
void infix2Postfix(FILE* fp = stdin) {
	char c, op;
	double val;
	arrayStack st;

	while ((c = getc(fp)) != '\n') {
		//피연산자면 그대로 출력
		if (c >= '0' && c <= '9') {		//연산항(숫자)의 시작이면
			ungetc(c, fp);		//문자를 돌려놓고
			fscanf_s(fp, "%lf", &val);	//double로 다시 읽음
			printf("%4.1f ", val);
		}
		// '('이면 스택에 삽입
		else if (c == '(') {
			st.push(c);
		}
		// ')'이면 '('가 나올 때까지 연산자 출력
		else if (c == ')') {
			while (!st.isEmpty()) {
				op = st.pop();
				if (op == '(') {
					break;
				}
				else {
					printf("%c ", op);
				}
			}
		}
		// 연산자('+', '-', '/', '*')이면 우선순위 비교 처리
		else if (c == '+' || c == '-' || c == '*' || c == '/') {
			while (!st.isEmpty()) {
				op = st.peek();
				if (precedence(c) <= precedence(op)) {
					printf("%c ", op);
					st.pop();
				}
				else {
					break;
				}
			}
			st.push(c);
		}
	}
	while (!st.isEmpty()) {
		printf("%c ", st.pop());
	}
	printf("\n");
}

void main() {
	printf("수식 입력 (Infix) = ");
	infix2Postfix();
}