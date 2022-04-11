#include <iostream>
#include <vector>
#include <string>
using namespace std;

string binarySum(string n1, string n2) {	// Ç×»ó n1.size() >= n2.size()
	int siz = n1.size();
	string n;
	int coef = 0;

	for (int i = 0; i != siz; i++) {
		int sum = 0;
		sum = i < n2.size() ?
			n1[siz - 1 - i] - '0' + n2[n2.size() - 1 - i] - '0' + coef :
			n1[siz - 1 - i] - '0' + coef;
		n = to_string(sum % 2) + n;
		coef = sum >= 2 ? 1 : 0;
	}
	if (coef == 1) 
		n = '1' + n;

	return n;
}

void solution() {
	string s;
	cin >> s;
	string coef = s;
	for (int i = 0; i != 16; i++) {
		s = binarySum(s, coef);
	}
	cout << s;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int testCaseNum = 1;
	// cin >> testCaseNum;
	for (int i = 0; i != testCaseNum; i++) { solution(); }
	return 0;
}