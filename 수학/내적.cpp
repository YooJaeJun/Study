#include <string>
#include <vector>

using namespace std;

const int dot_prod(const vector<int> a, const vector<int> b) {
	int sum = 0;
	for (int i = 0; i != a.size(); i++) {
		sum += a[i] * b[i];
	}
	return sum;
}

int solution(vector<int> a, vector<int> b) {
	int answer = 1234567890;
	answer = dot_prod(a, b);
	return answer;
}