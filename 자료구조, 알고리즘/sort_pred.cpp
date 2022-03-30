#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


class Solution {
public:
	void moveZeroes(vector<int>& nums) {
		stable_sort(nums.begin(), nums.end(), comp);
		for (auto& elem : nums) {
			cout << elem << ' ';
		}
	}
	struct {
		bool operator()(const int& n1, const int& n2) {
			return n2 == 0 ? 1 : 0;
		}
	} comp;
};


int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	Solution s;
	/*vector<int> v = { 2, 7, 11, 15 };
	for (int i = 0; i != s.twoSum(v, 9).size(); i++) {
		cout << s.twoSum(v, 9)[i] << ' ';
	}*/

	return 0;
}