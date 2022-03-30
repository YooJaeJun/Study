#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

void solution() {
	ll x1, y1, x2, y2, x3, y3, x4, y4;
	cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
	
	double t, s;
	// 직선의 방정식 공식 참고
	double under = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
	if (under == 0) {
		// 완전 내접
		if (x1 <= x3 &&
			y1 <= y3 &&
			x2 >= x4 &&
			y2 >= y4) {
		}
		// 일부 내접
		else if (x1 <= x3 &&
			x2 >= x1) {
		}
		// 평행
		else {
			cout << 0;
			return;
		}
	}
	double t_ = (x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3);
	double s_ = (x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3);
	t = t_ / under;
	s = s_ / under;

	// 공식상 t와 s가 0과 1 사이여야 교차 판단.
	if (t < 0.0f || t > 1.0f || s < 0.0f || s > 1.0f) {
		cout << 0;
		return;
	}
	// 교차
	double xAns = x1 + t * (x2 - x1);
	double yAns = y1 + t * (y2 - y1);
	
	cout << 1 << '\n';
	cout << xAns << ' ' << yAns;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solution();
	return 0;
}