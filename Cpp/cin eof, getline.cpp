#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum kindStr {
	small, big, num, space
};

void solution() {
	while (cin.eof() == false) {
		string s;
		getline(cin, s);
		vector<int> v(4);
		for (auto& ch : s) {
			if (ch >= 'a' && ch <= 'z') {
				v[small]++;
			}
			else if (ch >= 'A' && ch <= 'Z') {
				v[big]++;
			}
			else if (ch >= '0' && ch <= '9') {
				v[num]++;
			}
			else if (ch == ' ') {
				v[space]++;
			}
		}
		int sum = 0;
		for (auto& elem : v) {
			sum += elem;
		}
		if (sum != 0) {
			for (auto& elem : v) {
				cout << elem << ' ';
			}
			cout << '\n';
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int testCaseNum = 1;
	//cin >> testCaseNum;
	for (int i = 0; i != testCaseNum; i++) { solution(); }
	return 0;
}