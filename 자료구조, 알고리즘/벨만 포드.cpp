#include <bits/stdc++.h>
using namespace std;
//#define int int64_t
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vector<int>>;

struct edge {
	int start, end, val;
	edge(int a, int b, int c) : start(a), end(b), val(c) {}
};

int n, m, w;
vector<edge> nodes;
vi dist;

void bellman_ford() {
	for (int i = 0; i < n - 1; i++) {
		for (auto& node : nodes) {
			// if (dist[node.start] == INT_MAX) continue;
			// 방문하지 않은 정점에 대해서도 최단거리를 갱신한다면 ==> 시작 정점이 어디더라도 정답
			dist[node.end] = min(dist[node.end], dist[node.start] + node.val);
		}
	}
	for (auto& node : nodes) {
		// if (dist[node.start] == INT_MAX) continue;
		// 위와 동일
		if (dist[node.start] + node.val < dist[node.end]) {
			cout << "YES" << '\n';
			return;
		}
	}
	cout << "NO" << '\n';
}

void solution() {
	cin >> n >> m >> w;

	for (int i = 0; i != m; i++) {
		int s, e, t;
		cin >> s >> e >> t;
		nodes.push_back(edge(s, e, t));
		nodes.push_back(edge(e, s, t));
	}
	for (int i = 0; i != w; i++) {
		int s, e, t;
		cin >> s >> e >> t;
		nodes.push_back(edge(s, e, -t));
	}

	// dist = vi(n + 1, 0);
	dist = vi(n + 1, INT_MAX);
	dist[1] = 0;

	bellman_ford();
}

int32_t main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t = 1;
	cin >> t;
	for (int i = 0; i != t; i++) { solution(); }
	return 0;
}