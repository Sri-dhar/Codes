#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int res = INT_MAX;
    int tempfunc(string a, string b) {
        int n = a.size();
        int count = 0;
        for (int i = 0; i < n; i++)
            a[i] == b[i] ? count++ : 0;
        return count;
    }

    void bfs(vector<string>& words, string start, string end, int count) {
        if(start == end)res = min(res, count);
        for (int i=0; i<words.size(); i++) {
            string x = words[i];
            if (tempfunc(x, start) == 1) {
                string t = words[i];
                words[i] = "";
                bfs(words, t, end, count+1);
                words[i] = t;
            }
        }
    }

    int ladderLength(string beginWord, string endWord, vector<string>& words) {
        string start = beginWord, end = endWord;
        bfs(words, start, end, 0);
        return res == INT_MIN ? 0 : res+1;
    }
};

int main() {
    Solution s;
    vector<string> words = {"hot","dot","dog","lot","log","cog"};
    cout << s.ladderLength("hit", "cog", words) << endl;
    return 0;
}