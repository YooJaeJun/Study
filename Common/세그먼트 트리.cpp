#include <iostream>
#include <vector>
using namespace std;

vector<int> tree;
vector<int> inputs;

// 세그먼트 트리
// 구간 합 트리 생성
int init(int start, int end, int node) {
	if (start == end) { return tree[node] = inputs[start]; }
	int mid = (start + end) / 2;
	return tree[node] = init(start, mid, node * 2) + init(mid + 1, end, node * 2 + 1);
}
// 구간합 구하기
int sum(int start, int end, int node, int left, int right) {
	if (left > end || right < start) { return 0; }	// 범위 밖
	if (left <= start && end <= right) { return tree[node]; }	// 범위 안
	int mid = (start + end) / 2;
	return sum(start, mid, node * 2, left, right) + sum(mid + 1, end, node * 2 + 1, left, right);
}
// 특정 원소값 수정
void update(int start, int end, int node, int index, int dif) {
	if (index < start || index > end) { return; }	// 범위 밖
	// 범위 안==> 다른 원소도 갱신
	tree[node] += dif;
	if (start == end) { return; }
	int mid = (start + end) / 2;
	update(start, mid, node * 2, index, dif);
	update(mid + 1, end, node * 2 + 1, index, dif);
}

void solution() {
	int n;
	/*cin >> n;*/
	n = 12;
	tree.resize(n * 4);
	inputs.resize(n);
	/*for (int i = 0; i != n; i++) {
		cin >> inputs[i];
	}*/
	inputs = { 1, 9, 3, 8, 4, 5, 5, 9, 10, 3, 4, 5 };

	init(0, n - 1, 1);
	cout << "0부터 12까지의 구간 합: " << sum(0, n - 1, 1, 0, 12) << '\n';
	cout << "3부터 8까지의 구간 합: " << sum(0, n - 1, 1, 3, 8) << '\n';
	cout << "인덱스 5의 원소를 -5만큼 수정" << '\n';
	update(0, n - 1, 1, 5, -5);
	cout << "3부터 8까지의 구간 합: " << sum(0, n - 1, 1, 3, 8) << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solution();
	return 0;
}