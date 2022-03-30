#include <iostream>

void hanoiTower(int n, char from, char tmp, char to) {
	if (n == 1) {
		printf("���� 1�� %c���� %c���� �ı��.\n", from, to);
	}
	else {
		hanoiTower(n - 1, from, to, tmp);
		printf("���� %d�� %c���� %c���� �ı��.\n", n, from, to);
		hanoiTower(n - 1, tmp, from, to);
	}
}

void main() {
	hanoiTower(4, 'A', 'B', 'C');
}