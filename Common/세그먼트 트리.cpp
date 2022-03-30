#include <iostream>
#include <vector>
using namespace std;

vector<int> tree;
vector<int> inputs;

// ���׸�Ʈ Ʈ��
// ���� �� Ʈ�� ����
int init(int start, int end, int node) {
	if (start == end) { return tree[node] = inputs[start]; }
	int mid = (start + end) / 2;
	return tree[node] = init(start, mid, node * 2) + init(mid + 1, end, node * 2 + 1);
}
// ������ ���ϱ�
int sum(int start, int end, int node, int left, int right) {
	if (left > end || right < start) { return 0; }	// ���� ��
	if (left <= start && end <= right) { return tree[node]; }	// ���� ��
	int mid = (start + end) / 2;
	return sum(start, mid, node * 2, left, right) + sum(mid + 1, end, node * 2 + 1, left, right);
}
// Ư�� ���Ұ� ����
void update(int start, int end, int node, int index, int dif) {
	if (index < start || index > end) { return; }	// ���� ��
	// ���� ��==> �ٸ� ���ҵ� ����
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
	cout << "0���� 12������ ���� ��: " << sum(0, n - 1, 1, 0, 12) << '\n';
	cout << "3���� 8������ ���� ��: " << sum(0, n - 1, 1, 3, 8) << '\n';
	cout << "�ε��� 5�� ���Ҹ� -5��ŭ ����" << '\n';
	update(0, n - 1, 1, 5, -5);
	cout << "3���� 8������ ���� ��: " << sum(0, n - 1, 1, 3, 8) << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solution();
	return 0;
}