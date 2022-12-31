#include <bits/stdc++.h>
using namespace std;
#define int int64_t
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using db = deque<bool>;
using ddb = deque<deque<bool>>;
#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define forn1(i, n) for (int i = 1; i <= (int)n; i++)
#define inGrid() ((nr >= 0) and (nr < n) and (nc >= 0) and (nc < m))
int dr[4] = { 0,0,-1,1 };
int dc[4] = { -1,1,0,0 };	// ÁÂ¿ì»óÇÏ


void solution()
{
	int n;
	cin >> n;
	vi v(n);
	forn(i, n) cin >> v[i];
	bool isFirst = true;
	int idx = 0;

	forn(i, n - 1)
	{
		if (v[i] > v[i + 1])
		{
			isFirst = false;
			idx = i;
		}
	}
	if (isFirst)
	{
		cout << -1;
		return;
	}


	for (int i = n - 1; i > idx; i--)
	{
		if (v[i] < v[idx])
		{
			swap(v[idx], v[i]);
			sort(v.begin() + idx + 1, v.end(), greater<int>());
			break;
		}
	}

	for (auto& elem : v) cout << elem << ' ';
}

int32_t main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t = 1;
	// cin >> t;
	while (t--) solution();
	return 0;
}