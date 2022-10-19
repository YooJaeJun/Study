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


class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        vector<int> dp(matrix[0].size() + 2);
        int before = 0, maxn = 0;

        for (int i = 1; i <= matrix.size(); i++)
        {
            for (int j = 1; j <= matrix[i].size(); j++)
            {
                int temp = dp[j];
                if (matrix[i - 1][j - 1] == '1')
                {
                    dp[j] = min(min(dp[j - 1], before), dp[j]) + 1;
                    maxn = max(maxn, dp[j]);
                }
                else
                {
                    dp[j] = 0;
                }
                before = temp;
            }
        }
        return maxn * maxn;
    }
};

int32_t main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t = 1;
	// cin >> t;
    Solution solution;
    vector<vector<char>> v = { {'1', '0'} };
	while (t--) solution.maximalSquare(v);
	return 0;
}