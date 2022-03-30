#include "arrayStack.h"

//��ü�� �켱���� ���
inline int precedence(char op) {
	switch (op) {
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*': case '/': return 2;	//�켱���� ����
	}
	return -1;
}

//���� ǥ�� ���� -> ���� ǥ�� ���� ��ȯ
void infix2Postfix(FILE* fp = stdin) {
	char c, op;
	double val;
	arrayStack st;

	while ((c = getc(fp)) != '\n') {
		//�ǿ����ڸ� �״�� ���
		if (c >= '0' && c <= '9') {		//������(����)�� �����̸�
			ungetc(c, fp);		//���ڸ� ��������
			fscanf_s(fp, "%lf", &val);	//double�� �ٽ� ����
			printf("%4.1f ", val);
		}
		// '('�̸� ���ÿ� ����
		else if (c == '(') {
			st.push(c);
		}
		// ')'�̸� '('�� ���� ������ ������ ���
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
		// ������('+', '-', '/', '*')�̸� �켱���� �� ó��
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
	printf("���� �Է� (Infix) = ");
	infix2Postfix();
}