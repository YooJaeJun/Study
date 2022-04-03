#include <iostream>
#include <vector>
#include <string>
using namespace std;

void solution() {
	int a, b, n;
	cin >> a >> b >> n;
	int rest = a % b;
	a /= b;
	for (int i = 2; i <= n + 1; i++) {
		rest *= 10;
		a = rest / b;
		rest %= b;
	}
	cout << a;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int testCaseNum = 1;
	//cin >> testCaseNum;
	for (int i = 0; i != testCaseNum; i++) { solution(); }
	return 0;
}