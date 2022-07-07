#include <queue>
using namespace std;


queue<int> q;

int fibonachi(int n) {
	int a = 0, b = 1;
	q.push(a);
	q.push(b);
	for (int i = 0; i != n - 2; i++) {
		a = q.front();
		q.pop();
		b = q.front();
		q.push(a + b);
	}
	return a + b;
}

void main() {
	printf("%d", fibonachi(5));
}