#include <bits/stdc++.h>
using namespace std;
#define int int64_t
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
#define yes cout << "YES\n";
#define no cout << "NO\n";
const int maxn = 200;
const double mod = 1e9 + 7;

// 이분매칭

// n: A그룹 크기, m: B그룹 크기
// A[i], B[i]: 각 정점이 매칭된 반대편 정점 번호
int n, m, A[maxn], B[maxn];
// adj[i]: A[i]와 인접한 그룹 B의 정점들
vi adj[maxn];
bool visited[maxn];

// a그룹에 속한 정점 a를 이분 매칭시켜서 성공하면 true
bool dfs(int a)
{
	visited[a] = true;
	for (int b : adj[a])
	{
		// 반대편이 매칭되지 않았거나
		// 매칭되어 있었지만 원래 매칭되어 있던 정점을 다른 정점과 매칭시킬 수 있으면 true
		if (B[b] == -1 or false == visited[B[b]] and dfs(B[b]))
		{
			A[a] = b;
			B[b] = a;
			return true;
		}
	}
	// 매칭 실패
	return false;
}

void solution()
{
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		int s;
		cin >> s;
		for (int j = 0; j < s; j++)
		{
			int k;
			cin >> k;
			adj[i].push_back(k - 1);
		}
	}

	int match = 0;
	// 초기값: -1
	fill(A, A + n, -1);
	fill(B, B + m, -1);
	for (int i = 0; i < n; i++)
	{
		// 아직 매칭되지 않은 그룹 A 정점에 대해 매칭 시도
		if (A[i] == -1)
		{
			// visited 배열 초기화
			fill(visited, visited + n, false);
			if (dfs(i)) match++;
		}
	}
	cout << match;
}

int32_t main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t = 1;
	// cin >> t;
	for (int i = 0; i != t; i++) solution();
	return 0;
}