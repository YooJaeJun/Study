#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdarg>	//가변인자함수용
#include <vector>
using namespace std;

vector<int> dat;

//가변인자함수 써보기
int min_(int repet_num, ...) {
	va_list ap;
	int arg;
	va_start(ap, repet_num);
	arg = va_arg(ap, int);
	int m = arg;	//최초 비교대상 초기화
	for (int i = 0; i < repet_num; ++i) {
		arg = va_arg(ap, int);
		m = (m < arg) ? m : arg;
	}
	va_end(ap);
	return m;
}
int dp(int x) {
	dat[0] = dat[1] = 0;
	//메모이제이션 dp[2] = 1; dp[4] = dp[2] + 1(횟수)
	for (int i = 2; i != x + 1; ++i) {
		if (!(i % 6)) {
			dat[i] = min_(3, dat[i / 3] + 1, dat[i / 2] + 1, dat[i - 1] + 1);	//반복횟수, 비교대상1,...
		}
		else if (!(i % 3)) {
			dat[i] = min_(2, dat[i / 3] + 1, dat[i - 1] + 1);
		}
		else if (!(i % 2)) {
			dat[i] = min_(2, dat[i / 2] + 1, dat[i - 1] + 1);
		}
		else {
			dat[i] = dat[i - 1] + 1;
		}
	}
	return dat[x];
}
int main() {
	int x;
	scanf("%d", &x);
	dat.resize(x + 1, 0);
	printf("%d", dp(x));

	return 0;
}