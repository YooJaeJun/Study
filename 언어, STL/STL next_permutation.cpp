#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        do {
            res.push_back(nums);
        } while (next_permutation(nums.begin(), nums.end()));
        return res;
    }
};

void main() {
    Solution s;
    vector<int> v{ 2,2,1,1 };
    vector<vector<int>> vv = s.permuteUnique(v);
    for (int i = 0; i != vv.size(); i++) {
        for (int j = 0; j != vv[i].size(); j++) {
            cout << vv[i][j] << ' ';
        }
        cout << '\n';
    }
}