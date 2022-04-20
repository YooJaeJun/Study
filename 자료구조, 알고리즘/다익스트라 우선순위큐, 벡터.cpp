#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int n = 6;
int inf = 99999999;

vector<pair<int, int>> nodes[7] =
{
{{0, 0,}},
{{2, 2}, {3, 5}, {4, 1}},
{{1, 2}, {3, 3}, {4, 2}},
{{1, 5}, {2, 3}, {4, 3}, {5, 1}, {6, 5}},
{{1, 1}, {2, 2}, {3, 3}, {5, 1}},
{{3, 1}, {4, 1}, {6, 2}},
{{3, 5}, {5, 2}}
};

bool visited[7];	// 방문
vector<int> dist(7);	// 거리

void dijk(int start) {
	dist[start] = 0;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;	// 가중치, 노드 Idx
	pq.push({ 0, start });
	// 가까운 순서대로 처리
	while (pq.empty() == false) {
		// 짧은 것이 먼저 오도록 한다.
		int distance = pq.top().first;
		int cur = pq.top().second;
		pq.pop();
		// 최단 거리가 아닌 경우 스킵
		if (dist[cur] < distance) continue;
		for (int i = 0; i < nodes[cur].size(); i++) {
			// 선택된 노드를 인접 노드로 거쳐서 가는 비용
			int nextDistance = distance + nodes[cur][i].first;
			// 선택된 노드의 인접 노드
			int next = nodes[cur][i].second;
			// 기존의 최소 비용보다 더 저렴하다면 교체
			if (nextDistance < dist[next]) {
				dist[next] = nextDistance;
				pq.push({ nextDistance, next });
			}
		}
	}
}

void solution() {
	for (int i = 0; i != dist.size(); i++) {
		dist[i] = inf;
	}
	dijk(1);
	for (int i = 1; i <= n; i++) {
		cout << dist[i] << ' ';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int testCaseNum = 1;
	//cin >> testCaseNum;
	for (int i = 0; i != testCaseNum; i++) { solution(); }
	return 0;
}






#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n = 6;
int inf = 99999999;

int nodes[6][6] = {
	{0,2,5,1,inf,inf},
	{2,0,3,2,inf,inf},
	{5,3,0,3,1,5},
	{1,2,3,0,1,inf},
	{inf,inf,1,1,0,2},
	{inf,inf,5,inf,2,0},
};
bool visited[6];	// 방문
int dist[6];	// 거리

int getMinNode() {
	int min = inf;
	int idx = 0;
	for (int i = 0; i < n; i++) {
		if (min > dist[i] && visited[i] == false) {
			min = dist[i];
			idx = i;
		}
	}
	return idx;
}

void dijk(int start) {
	for (int i = 0; i < n; i++) {
		dist[i] = nodes[start][i];
	}
	visited[start] = true;
	for (int i = 0; i < n - 2; i++) {
		int cur = getMinNode();
		visited[cur] = true;
		for (int j = 0; j < 6; j++) {
			if (visited[j] == false) {
				if (dist[cur] + nodes[cur][j] < dist[j]) {
					dist[j] = dist[cur] + nodes[cur][j];
				}
			}
		}
	}
}

void solution() {
	dijk(0);
	for (int i = 0; i < n; i++) {
		cout << dist[i] << ' ';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int testCaseNum = 1;
	//cin >> testCaseNum;
	for (int i = 0; i != testCaseNum; i++) { solution(); }
	return 0;
}