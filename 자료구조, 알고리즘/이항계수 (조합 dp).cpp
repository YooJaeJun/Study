#include <bits/stdc++.h>
using namespace std;
#define int int64_t
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using db = deque<bool>;
#define yes cout << "YES\n";
#define no cout << "NO\n";
#define forn(i, n) for (int i = 0; i < (int)n; i++)
const int maxn = 1e9 + 7;
const int mod = 10'007;

int n, k;
vvi memo;

// 탑다운 하향식
int comb(int n, int k)
{
	if (k == 0 or k == n) return 1;
	if (memo[n][k]) return memo[n][k];
	return memo[n][k] = (comb(n - 1, k) + comb(n - 1, k - 1)) % mod;
}

void solution()
{
	cin >> n >> k;
	memo = vvi(n + 1, vi(n + 1));
	cout << comb(n, k);
}


// 바텀업 상향식
/*
void solution()
{
	cin >> n >> k;
	memo = vvi(n + 1, vi(n + 1));
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= min(i, k); j++)
		{
			if (j == 0 or j == i) memo[i][j] = 1;
			else memo[i][j] = (memo[i - 1][j - 1] + memo[i - 1][j]) % mod;
		}
	}
	cout << memo[n][k];
}
*/

int32_t main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t = 1;
	// cin >> t;
	for (int i = 0; i != t; i++) solution();
	return 0;
}