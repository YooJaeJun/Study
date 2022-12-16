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

	auto NextPermutation = [&](int n)
	{
		int i = n - 1;
		while (i > 0 and v[i - 1] >= v[i]) i--;
		if (i <= 0) return false;

		int j = n - 1;
		while (v[j] <= v[i - 1]) j--;
		swap(v[i - 1], v[j]);

		j = n - 1;
		while(i < j)
		{
			swap(v[i], v[j]);
			i++;
			j--;
		}
		return true;
	};

	if (NextPermutation(n))
	{
		forn(i, n) cout << v[i] << ' ';
	}
	else cout << -1;
}

int32_t main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t = 1;
	// cin >> t;
	while (t--) solution();
	return 0;
}