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

// �̺и�Ī

// n: A�׷� ũ��, m: B�׷� ũ��
// A[i], B[i]: �� ������ ��Ī�� �ݴ��� ���� ��ȣ
int n, m, A[maxn], B[maxn];
// adj[i]: A[i]�� ������ �׷� B�� ������
vi adj[maxn];
bool visited[maxn];

// a�׷쿡 ���� ���� a�� �̺� ��Ī���Ѽ� �����ϸ� true
bool dfs(int a)
{
	visited[a] = true;
	for (int b : adj[a])
	{
		// �ݴ����� ��Ī���� �ʾҰų�
		// ��Ī�Ǿ� �־����� ���� ��Ī�Ǿ� �ִ� ������ �ٸ� ������ ��Ī��ų �� ������ true
		if (B[b] == -1 or false == visited[B[b]] and dfs(B[b]))
		{
			A[a] = b;
			B[b] = a;
			return true;
		}
	}
	// ��Ī ����
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
	// �ʱⰪ: -1
	fill(A, A + n, -1);
	fill(B, B + m, -1);
	for (int i = 0; i < n; i++)
	{
		// ���� ��Ī���� ���� �׷� A ������ ���� ��Ī �õ�
		if (A[i] == -1)
		{
			// visited �迭 �ʱ�ȭ
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