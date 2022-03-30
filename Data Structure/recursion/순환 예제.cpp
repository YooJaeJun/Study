#include <iostream>

int sum(int n) {
	if (n == 1) return 1;
	return n + sum(n - 1);
}

float devideSum(float n) {
	if (n == 1) return 1;
	return 1 / n + devideSum(n - 1);
}

void asterisk(int i) {
	if (i > 1) {
		asterisk(i / 2);
		asterisk(i / 2);
	}
	printf("*");
}

void main() {
	//std::cout << sum(5);
	//std::cout << devideSum(5);
	asterisk(5);
}