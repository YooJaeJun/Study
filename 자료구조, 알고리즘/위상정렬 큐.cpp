#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int maxIdx = 10;
int n, inDegree[maxIdx];
vector<int> a[maxIdx];

void topologySort() {
	int result[maxIdx];
	queue<int> q;

	// ���� ������ 0�� ��带 ť�� ����.
	for (int i = 1; i <= n; i++) {
		if (inDegree[i] == 0) q.push(i);
	}
	// ���� ������ ������ ����Ƿ��� ��Ȯ�� n���� ��带 �湮
	for (int i = 1; i <= n; i++) {
		// n���� �湮�ϱ� ���� ť�� ��ٸ� ����Ŭ�� �߻��� ��.
		if (q.empty()) {
			printf("����Ŭ�� �߻��߽��ϴ�.");
			return;
		}
		int x = q.front();
		q.pop();
		result[i] = x;
		for (int i = 0; i < a[x].size(); i++) {
			int y = a[x][i];
			if (--inDegree[y] == 0) {
				q.push(y);
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		cout << result[i];
	}
}

void solution() {
	n = 7;
	a[1].push_back(2);
	inDegree[2]++;
	a[1].push_back(5);
	inDegree[5]++;
	a[2].push_back(3);
	inDegree[3]++;
	a[3].push_back(4);
	inDegree[4]++;
	a[4].push_back(6);
	inDegree[6]++;
	a[5].push_back(6);
	inDegree[6]++;
	a[6].push_back(7);
	inDegree[7]++;

	topologySort();
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int testCaseNum = 1;
	// cin >> testCaseNum;
	for (int i = 0; i != testCaseNum; i++) { solution(); }
	return 0;
}