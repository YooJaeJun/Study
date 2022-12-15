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
	int n = 7;
	vi v{ 5,2,4,1,3,7,6 };

	function<void(int, int)> QuickSort = [&](int l, int r)
	{
		if (l >= r) return;

		int pivot = l;
		int j = pivot;

		for (int i = l + 1; i <= r; i++)
		{
			if (v[i] < v[pivot])
			{
				j++;
				swap(v[i], v[j]);
			}
		}
		swap(v[l], v[j]);
		pivot = j;

		QuickSort(l, pivot - 1);
		QuickSort(pivot + 1, r);
	};
	QuickSort(0, n - 1);

	forn(i, n) cout << v[i] << ' ';
}

int32_t main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t = 1;
	// cin >> t;
	while (t--) solution();
	return 0;
}