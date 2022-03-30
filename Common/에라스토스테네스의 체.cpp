#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int limit = 123456 * 2;
vector<bool> isPrime(limit + 1, true);

void checkPrime() {
	isPrime[0] = false;
	isPrime[1] = false;
	for (int i = 2; i < limit; i++) {
		if (isPrime[i] == false) { continue; }
		for (int j = 2; j * i <= limit; j++) {
			isPrime[j * i] = false;
		}
	}
}

void solution() {

	checkPrime();

	while (1) {
		int n;
		cin >> n;
		if (n == 0) { break; }

		int ans = 0;
		for (int i = n + 1; i <= 2 * n; i++) {
			if (isPrime[i]) {
				ans++;
			}
		}
		cout << ans << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solution();
	return 0;
}