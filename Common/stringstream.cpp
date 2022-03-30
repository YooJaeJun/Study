#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

int main() {
	string str = "2019:06:30 12:00:30";
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == ':') {
			str[i] = ' ';
		}
	}

	vector<long long> time;
	long long num = 0;
	stringstream stream;
	stream.str(str);
	while (stream >> num) {
		time.push_back(num);
	}

	long long second = 0;
	second += time[0] * 365 * 24 * 60 * 60;	// 연
	second += time[1] * 30 * 24 * 60 * 60;	// 월
	second += time[2] * 24 * 60 * 60;		// 일
	second += time[3] * 60 * 60;			// 시
	second += time[4] * 60;					// 분
	second += time[5];						// 초

	cout << second << '\n';
	return 0;
}