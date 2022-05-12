#include <bits/stdc++.h>
using namespace std;
#define int int64_t
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vector<int>>;


void solution() {
	vector<string> input(3);
	input[0] = "1 Kim 79";
	input[1] = "2 Moon 100";
	input[2] = "3 Chan 78";

	for (int i = 0; i < input.size(); ++i)
	{
		int num, score;
		string name;
		stringstream ss;
		ss.str(input[i]);

		ss >> num;
		ss >> name;
		ss >> score;

		cout << num << " " << name << " " << score << endl;
	}
}

int32_t main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t = 1;
	// cin >> t;
	for (int i = 0; i != t; i++) { solution(); }
	return 0;
}