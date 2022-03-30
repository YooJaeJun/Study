#include <iostream>
#include "operandStack.h"
using namespace std;


/// <summary>
/// ��Ģ���� ���� ǥ�� ����
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
		else if (c >= '0' && c <= '9') {	//�ǿ�����(����)�� �����̸�
			ungetc(c, fp);	//���ڸ� �Է� ���ۿ� �����ְ�
			double val;
			fscanf_s(fp, "%lf", &val);	//double�� �ٽ� ����
			st.push(val);
		}
	}
	return st.pop();
}

/*
void main() {
	printf("���� �Է� (Postfix)= ");
	printf("��� ��� => %f\n", calcPostfixExpr());
}
*/