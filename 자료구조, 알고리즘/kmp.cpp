#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n;
    string m;
    int q;
    cin >> n >> m >> q;

    vector<pair<int, int>> cuts(q);

    for (int i = 0; i < q; i++)
        cin >> cuts[i].first >> cuts[i].second;

    for (auto& elem : cuts)
    {
        string str = m.substr(elem.first, elem.second - elem.first + 1);
        int start = 0, end = 0;

        for (int i = 0; i < str.size(); i++)
        {
            if (str[i] == '*')
            {
                start = i;
                break;
            }
        }

        for (int i = str.size() - 1; i >= 0; i--)
        {
            if (str[i] == '*')
            {
                end = i;
                break;
            }
        }

        str = str.substr(start, end - start + 1);
        int sum = 0;

        for (auto& ch : str)
        {
            if (ch >= '0' && ch <= '9')
                sum += ch - '0';
        }

        cout << sum << '\n';
    }

    return 0;
}