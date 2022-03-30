#include <iostream>

void hanoiTower(int n, char from, char tmp, char to) {
	if (n == 1) {
		printf("원판 1을 %c에서 %c으로 옭긴다.\n", from, to);
	}
	else {
		hanoiTower(n - 1, from, to, tmp);
		printf("원판 %d을 %c에서 %c으로 옭긴다.\n", n, from, to);
		hanoiTower(n - 1, tmp, from, to);
	}
}

void main() {
	hanoiTower(4, 'A', 'B', 'C');
}