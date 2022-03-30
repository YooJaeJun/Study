#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;


int a(int n) {
	return n * (n + 1) / 2;
}

int b(int n) {
	int sum = 0;
	for (int i = 1; i <= n; i++) {
		sum += i;
	}
	return sum;
}
int c(int n) {
	int sum = 0;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j != i; j++) {
			sum += 1;
		}
	}
	return sum;
}
void main() {
	clock_t start, end;
	double duration;
	start = clock();

	b(30000);


	end = clock();
	duration = (double)(end - start) / CLOCKS_PER_SEC;
	cout << duration;
}