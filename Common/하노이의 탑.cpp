#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void move(int start, int end) {
	cout << start << ' ' << end << '\n';
}

void hanoi(int n, int start, int end) {
	if (n == 1) {
		move(start, end);
		return;
	}
	int via = 6 - start - end;
	hanoi(n - 1, start, via);
	move(start, end);
	hanoi(n - 1, via, end);
}

void solution() {
	int n;
	cin >> n;
	// È½¼ö 2^n - 1 
	// pow´Â Á¤È®µµ ³·´Ù°í..
	int cnt = 1;
	for (int i = 0; i != n; i++) {
		cnt *= 2;
	}
	cout << cnt - 1 << '\n';

	hanoi(n, 1, 3);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solution();
	return 0;
}