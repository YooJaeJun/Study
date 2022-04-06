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

	// 진입 차수가 0인 노드를 큐에 삽입.
	for (int i = 1; i <= n; i++) {
		if (inDegree[i] == 0) q.push(i);
	}
	// 위상 정렬이 완전히 수행되려면 정확히 n개의 노드를 방문
	for (int i = 1; i <= n; i++) {
		// n개를 방문하기 전에 큐가 빈다면 사이클이 발생한 것.
		if (q.empty()) {
			printf("사이클이 발생했습니다.");
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