#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void solution() {
	int n, m;
	cin >> n >> m;
	vector<int> idxs(n);
	vector<string> strs(n);
	for (int i = 0; i != n; i++) {
		cin >> strs[i] >> idxs[i];
	}

	for (int i = 0; i != m; i++) {
		int n;
		cin >> n;
		int idx = lower_bound(idxs.begin(), idxs.end(), n) - idxs.begin();
		cout << strs[idx] << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int testCaseNum = 1;
	//cin >> testCaseNum;
	for (int i = 0; i != testCaseNum; i++) { solution(); }
	return 0;
}