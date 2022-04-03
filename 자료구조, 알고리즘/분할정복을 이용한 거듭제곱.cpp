#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

ll newPow(ll a, ll b, ll c) {
	if (b == 1) return a % c;
	ll x = newPow(a, b / 2, c);
	if (b % 2 == 0) return x % c * x % c;
	return x % c * x % c * (a % c) % c;
}

void solution() {
	ll a, b, c;
	cin >> a >> b >> c;
	cout << newPow(a, b, c);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int testCaseNum = 1;
	//cin >> testCaseNum;
	for (int i = 0; i != testCaseNum; i++) { solution(); }
	return 0;
}