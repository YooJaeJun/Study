#include <iostream>
using namespace std;

int power(int x, int n) {
	if (n == 0) return 1;
	if (n % 2 == 0) {
		return power(x * x, n / 2);
	}
	else if (n % 2 != 0) {
		return x * power(x * x, (n - 1) / 2);
	}
}

void main() {
	cout << power(2, 6);
}