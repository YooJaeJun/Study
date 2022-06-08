#include <bits/stdc++.h>
using namespace std;
#define int int64_t
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vector<int>>;


vector<int> getPi(string p)
{
    int m = (int)p.size(), j = 0;
    vector<int> pi(m, 0);
    for (int i = 1; i < m; ++i)
    {
        while (j > 0 && p[i] != p[j])
            j = pi[j - 1];
        if (p[i] == p[j])
            pi[i] = ++j;
    }
    return pi;
}

vector<int> kmp(string s, string p)
{
    vector<int> ans;
    auto pi = getPi(p);
    int n = (int)s.size(), m = (int)p.size(), j = 0;
    for (int i = 0; i < n; ++i)
    {
        while (j > 0 && s[i] != p[j])
            j = pi[j - 1];
        if (s[i] == p[j])
        {
            if (j == m - 1)
            {
                ans.push_back(i - m + 1);
                j = pi[j];
            }
            else
            {
                j++;
            }
        }
    }
    return ans;
}

string solution(string m, vector<string> musicinfos) {
    // 제목, 재생된 시간 (제일 긴 음악 판정)
    string ansTitle;
    int ansIterCnt;

    for (auto& info : musicinfos)
    {
        // 시간 구하기 (반복용)
        string start;
        start += info[6]; start += info[7];
        string end;
        end += info[0]; end += info[1];
        int minute = stoi(start) - stoi(end);

        start = ""; end = "";
        start += info[9]; start += info[10];
        end += info[3]; end += info[4];

        int sec = stoi(start) - stoi(end);
        if (sec < 0)
        {
            --minute;
            sec += 60;
        }

        // 타이틀 저장
        string title;
        int noteIdx = 12;
        for (int i = 12; info[i] != ','; ++i)
        {
            title += info[i];
            noteIdx = i;
        }
        noteIdx += 2;

        // 악보 반복
        string note;
        int iterCnt = minute * 60 + sec;
        int iterCntOrigin = iterCnt;
        int cur = noteIdx;

        while (iterCnt--)
        {
            note += info[cur];

            if (info[cur + 1] == '#')
                iterCnt++;

            if (cur == info.size() - 1)
                cur = noteIdx;
            else
                cur++;
        }

        // kmp 알고리즘
        vector<int> idxs = kmp(note, m);

        // 고려1. 찾았어도 뒤에 #이 있으면 안 됨.
        // 고려2. #이 붙었으면 다음 인덱스부터 또 검사해야 됨
        for (auto& idx : idxs)
        {
            if (note[idx + m.size()] != '#')
            {
                if (ansTitle.empty()) {
                    ansTitle = title;
                    ansIterCnt = iterCntOrigin;
                }
                else
                {
                    if (ansIterCnt < iterCntOrigin)
                    {
                        ansTitle = title;
                        ansIterCnt = iterCntOrigin;
                    }
                }
            }
        }
    }

    if (ansTitle.empty()) return "(None)";
    else return ansTitle;
}

int32_t main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t = 1;
	// cin >> t;
    for (int i = 0; i != t; i++) { solution("A#", {"12:00,12:01,HELLO,A#" }); }
	return 0;
}