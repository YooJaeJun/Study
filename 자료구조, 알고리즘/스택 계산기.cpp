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
		// 숫자 - 그대로 출력하고 뒤에 공백 하나를 출력한다.
		if (isdigit(*m)) {
			while (isdigit(*m) || *m == '.') *p++ = *m++;
			*p++ = ' ';
		}
		else
			// 연산자 - 스택에 있는 자기보다 높은 연산자를 모두 꺼내 출력하고 자신은 푸시한다.
			if (strchr("^*/+-", *m)) {
				while (!cS.empty() && GetPriority(cS.top()) >= GetPriority(*m)) {
					*p++ = cS.top();
					cS.pop();
				}
				cS.push(*m++);
			}
			else
				// 여는 괄호 - 푸시한다.
				if (*m == '(') {
					cS.push(*m++);
				}
				else
					// 닫는 괄호 - 여는 괄호가 나올 때까지 팝해서 출력하고 여는 괄호는 버린다.
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
	// 스택에 남은 연산자들 모두 꺼낸다.
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
		// 숫자는 스택에 넣는다.
		if (isdigit(*p)) {
			num = atof(p);
			dS.push(num);
			for (; isdigit(*p) || *p == '.'; p++) { ; }
		}
		else {
			// 연산자는 스택에서 두 수를 꺼내 연산하고 다시 푸시한다.
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
			// 연산 후 또는 연산자가 아닌 경우 다음 문자로
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
		printf("수식을 입력하세요(끝낼 때 0) : ");
		gets_s(exp);
		if (strcmp(exp, "0") == 0) break;
		result = CalcExp(exp, &bError);
		if (bError) {
			puts("수식의 괄호짝이 틀립니다.");
		}
		else {
			printf("%s = %.2f\n", exp, result);
		}
	}
}