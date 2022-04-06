#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

string strSum(string s1, string s2) {
	int siz = 0;
	if (s1.size() < s2.size()) {
		swap(s1, s2);	// s1을 큰 쪽으로
	}
	siz = s1.size();
	int coef = 0;
	string ans;
	for (int i = siz - 1; i >= 0; i--) {
		int x = 0;

		x = i >= s1.size() - s2.size() ?	// 사이즈 큰 수 기준 맞춰 각 자리수 더하기
			s1[i] - '0' + s2[i - (s1.size() - s2.size())] - '0' + coef :
			s1[i] - '0' + coef;

		ans = to_string(x % 10) + ans;	// 더하기 결과

		x /= 10;
		if (x == 0) coef = 0;
		else coef = 1;	// 다음 자리수에 1 더하기용
	}
	if (coef == 1) 
		ans = '1' + ans;

	return ans;
}

vector<vector<string>> memo;

string comb(long long n, long long m) {
	if (memo[n][m] != "") return memo[n][m];
	if (m == 1) return to_string(n);
	else if (m == 0 || n == m) return "1";
	memo[n][m] = strSum(comb(n - 1, m - 1), comb(n - 1, m));
	return memo[n][m];
}

void solution() {
	long long n, m;
	cin >> n >> m;
	memo.resize(n + 1);
	for (auto& elem : memo) {
		elem.resize(m + 1);
	}
	cout << comb(n, m);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int testCaseNum = 1;
	// cin >> testCaseNum;
	for (int i = 0; i != testCaseNum; i++) { solution(); }
	return 0;
}







// 다른 사람 풀이
/*#include <iostream>
#include <vector>
using namespace std;

string arr[105][105];

string add(string num1, string num2) {
	string num = "";
	int sum = 0;
	int size = max(num1.size(), num2.size());

	for (int i = 0; i < size || sum; i++) {
		if (num1.size() > i) sum += num1[i] - '0';
		if (num2.size() > i) sum += num2[i] - '0';
		num += sum % 10 + '0';
		sum /= 10;	//합이 10보다 컸으면 다음 자리수에 넘겨주기
	}
	return num;
}

string combi(int n, int m) {
	arr[0][0] = "1";
	arr[1][0] = arr[1][1] = "1";
	for (int i = 2; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			if (i == j || j == 0) {
				arr[i][j] = "1";
			}
			else {
				arr[i][j] = add(arr[i - 1][j - 1], arr[i - 1][j]);
			}
		}
	}
}

void solution() {
	int n, m;
	cin >> n >> m;

	combi(n, m);

	for (int i = arr[n][m].size() - 1; i > 0; i--) {
		cout << arr[n][m][i];
	}
	return;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int testCaseNum = 1;
	//cin >> testCaseNum;
	for (int i = 0; i != testCaseNum; i++) { solution(); }
	return 0;
}*/