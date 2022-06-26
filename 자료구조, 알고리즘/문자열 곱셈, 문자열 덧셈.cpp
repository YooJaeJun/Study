#include <bits/stdc++.h> 
using namespace std;

class Solution {
public:
    string sum(string num1, string num2) {
        int p = num1.size() - 1;
        int q = num2.size() - 1;
        string ret;
        int carry = 0;
        while (p >= 0 or q >= 0)
        {
            int sum = carry;
            if (p >= 0) sum += num1[p--] - '0';
            if (q >= 0) sum += num2[q--] - '0';
            carry = 0;
            if (sum >= 10) carry = 1;
            sum %= 10;
            ret += to_string(sum);
        }
        if (carry == 1) ret += '1';
        reverse(ret.begin(), ret.end());
        return ret;
    }

    string multiply(string num1, string num2) {
        // 문자열 곱셈
        string cur;
        if (num1.size() < num2.size()) swap(num1, num2);    // n1>n2
        int digit = 0;
        for (int i = num2.size() - 1; i >= 0; i--)
        {
            string s;
            int carry = 0;

            for (int j = num1.size() - 1; j >= 0; j--)
            {
                int sum = carry + ((num1[j] - '0') * (num2[i] - '0'));
                carry = sum / 10;
                sum %= 10;
                s += to_string(sum);
            }
            if (carry >= 1) s += to_string(carry);
            reverse(s.begin(), s.end());
            for (int j = 0; j < digit; j++)
            {
                s += '0';
            }
            digit++;
            if (cur.empty()) cur = s;
            else cur = sum(cur, s);
        }
        
        // 앞자리 0없애기
        while (cur.size() >= 2 and cur.front() == '0') cur.erase(cur.begin());
        return cur;
    }
};

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    Solution s;
    s.multiply("123456789", "987654321");

    return 0;
}