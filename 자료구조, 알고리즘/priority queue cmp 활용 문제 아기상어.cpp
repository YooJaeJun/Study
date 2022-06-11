#include <bits/stdc++.h>
#include <unordered_map>
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
const double mod = 1e9 + 7;

struct coord
{
	int x, y, dist, depth;
	bool operator<(const coord other) const
	{
		if (x < other.x) return true;
		else if (x > other.x) return false;
		return y < other.y;
	}
};

struct sharktag
{
	coord cur;
	int size = 2;
	int curEaten;
	inline void eat()
	{
		if (++curEaten >= size)
		{
			curEaten = 0;
			++size;
		}
	}
};
sharktag shark;

int n;
int grid[20][20];
bool visited[20][20];
int dx[4] = { -1,0,0,1 };	// 상좌우하
int dy[4] = { 0,-1,1,0 };
int ans = 0;

struct cmp
{
	bool operator()(const coord c1, const coord c2)
	{
		if (c1.depth > c2.depth) return true;
		else if (c1.depth < c2.depth) return false;

		if (c1.x > c2.x) return true;
		else if (c1.x < c2.x) return false;
		
		return c1.y > c2.y;
	}
};

coord search(int sx, int sy)
{
	priority_queue<coord, vector<coord>, cmp> pq;
	pq.push({ sx, sy, 0, 0 });
	visited[sx][sy] = true;
	for (int i = 0; i < n; i++)
	{
		fill(visited[i], visited[i] + n, false);
	}

	while (false == pq.empty())
	{
		int x = pq.top().x;
		int y = pq.top().y;
		int dist = pq.top().dist;
		int depth = pq.top().depth;
		pq.pop();

		if (grid[x][y] != 0 and grid[x][y] < shark.size)
		{
			shark.eat();
			shark.cur.x = x;
			shark.cur.y = y;
			grid[x][y] = 0;
			ans += dist;
			return { x, y };
		}

		for (int i = 0; i < 4; i++)
		{
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
			if (grid[nx][ny] > shark.size) continue;
			if (visited[nx][ny]) continue;
			visited[nx][ny] = true;
			pq.push({ nx, ny, dist + 1, depth + 1 });
		}
	}
	return { -1, -1 };
}

void solution()
{
	cin >> n;
	forn(i, n)
	{
		forn(j, n)
		{
			cin >> grid[i][j];
			if (grid[i][j] == 9)
			{
				shark.cur.x = i;
				shark.cur.y = j;
				grid[i][j] = 0;	// shark 위치는 구조체 멤버로
			}
		}
	}

	coord next;
	do
	{
		next = search(shark.cur.x, shark.cur.y);
	} while (next.x != -1 and next.y != -1);

	cout << ans;
}

int32_t main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t = 1;
	// cin >> t;
	for (int i = 0; i != t; i++) solution();
	return 0;
}