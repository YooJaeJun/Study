#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int inf = 9999999;
int n, m;
vector<vector<int>> dist;

void floyd() {
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}
}

void solution() {
	cin >> n >> m;
	dist.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		dist[i].resize(n + 1, inf);
		dist[i][i] = 0;
	}
	for (int i = 1; i <= m; i++) {
		int u, v, w; 
		cin >> u >> v >> w;
		dist[u][v] = min(dist[u][v], w);
	}
	
	floyd();
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (dist[i][j] == inf) cout << 0 << ' ';
			else cout << dist[i][j] << ' ';
		}
		cout << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int testCaseNum = 1;
	//cin >> testCaseNum;
	for (int i = 0; i != testCaseNum; i++) { solution(); }
	return 0;
}