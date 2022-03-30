#include <Turboc.h>
#include <math.h>
#include <stack>
using namespace std;

int GetPriority(int op)
{
	switch (op) {
	case '(':
		return 0;
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	case '^':
		return 3;
	}
	return 100;
}
void MakePostfix(char *Post, const char *Mid)
{
	const char *m = Mid;
	char *p = Post;
	char c;
	stack<char> cS;
	while (*m) {
		// ���� - �״�� ����ϰ� �ڿ� ���� �ϳ��� ����Ѵ�.
		if (isdigit(*m)) {
			while (isdigit(*m) || *m == '.') *p++ = *m++;
			*p++ = ' ';
		}
		else
			// ������ - ���ÿ� �ִ� �ڱ⺸�� ���� �����ڸ� ��� ���� ����ϰ� �ڽ��� Ǫ���Ѵ�.
			if (strchr("^*/+-", *m)) {
				while (!cS.empty() && GetPriority(cS.top()) >= GetPriority(*m)) {
					*p++ = cS.top();
					cS.pop();
				}
				cS.push(*m++);
			}
			else
				// ���� ��ȣ - Ǫ���Ѵ�.
				if (*m == '(') {
					cS.push(*m++);
				}
				else
					// �ݴ� ��ȣ - ���� ��ȣ�� ���� ������ ���ؼ� ����ϰ� ���� ��ȣ�� ������.
					if (*m == ')') {
						for (;;) {
							c = cS.top();
							cS.pop();
							if (c == '(') break;
							*p++ = c;
						}
						m++;
					}
					else {
						m++;
					}
	}
	// ���ÿ� ���� �����ڵ� ��� ������.
	while (!cS.empty()) {
		*p++ = cS.top();
		cS.pop();
	}
	*p = 0;
}
double CalcPostfix(const char *Post)
{
	const char *p = Post;
	double num;
	double left, right;
	stack<double> dS;
	while (*p) {
		// ���ڴ� ���ÿ� �ִ´�.
		if (isdigit(*p)) {
			num = atof(p);
			dS.push(num);
			for (; isdigit(*p) || *p == '.'; p++) { ; }
		}
		else {
			// �����ڴ� ���ÿ��� �� ���� ���� �����ϰ� �ٽ� Ǫ���Ѵ�.
			if (strchr("^*/+-", *p)) {
				right = dS.top();
				dS.pop();
				left = dS.top();
				dS.pop();
				switch (*p) {
				case '+':
					dS.push(left + right);
					break;
				case '-':
					dS.push(left - right);
					break;
				case '*':
					dS.push(left*right);
					break;
				case '/':
					if (right == 0.0) {
						dS.push(0.0);
					}
					else {
						dS.push(left / right);
					}
					break;
				case '^':
					dS.push(pow(left, right));
					break;
				}
			}
			// ���� �� �Ǵ� �����ڰ� �ƴ� ��� ���� ���ڷ�
			p++;
		}
	}
	if (!dS.empty()) {
		num = dS.top();
		dS.pop();
	}
	else {
		num = 0.0;
	}
	return num;
}
double CalcExp(const char *exp, BOOL *bError = NULL)
{
	char Post[256];
	const char *p;
	int count;
	if (bError != NULL) {
		for (p = exp, count = 0; *p; p++) {
			if (*p == '(') count++;
			if (*p == ')') count--;
		}
		*bError = (count != 0);
	}
	MakePostfix(Post, exp);
	return CalcPostfix(Post);
}
void main()
{
	char exp[256];
	BOOL bError;
	double result;
	const char *p = strchr("^*/+-", NULL);
	strcpy_s(exp, "2.2+3.5*4.1"); printf("%s = %.2f\n", exp, CalcExp(exp));
	strcpy_s(exp, "(34+93)*2-(43/2)"); printf("%s = %.2f\n", exp, CalcExp(exp));
	strcpy_s(exp, "1+(2+3)/4*5+2^10+(6/7)*8"); printf("%s = %.2f\n", exp, CalcExp(exp));
	for (;;) {
		printf("������ �Է��ϼ���(���� �� 0) : ");
		gets_s(exp);
		if (strcmp(exp, "0") == 0) break;
		result = CalcExp(exp, &bError);
		if (bError) {
			puts("������ ��ȣ¦�� Ʋ���ϴ�.");
		}
		else {
			printf("%s = %.2f\n", exp, result);
		}
	}
}