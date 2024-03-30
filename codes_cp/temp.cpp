#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int Max;
    unordered_map<int, vector<int>> dp;

    int hash(int i, int j) {
        return i * 100 + j;
    }

    int getValid(string &s) {
        long long valid = 0;
        stack<long long> st;
        st.push({s[0] - '0'});
        for (int i = 1; i < s.length(); ++i) {
            if (isdigit(s[i])) {
                if (s[i - 1] == '*') {
                    long long mul = 1ll * st.top() * (s[i] - '0');
                    st.pop();
                    st.push(mul);
                } else {
                    st.push({s[i] - '0'});
                }
            }
        }

        while (st.size()) {
            valid += st.top();
            st.pop();
        }
        return valid;
    }

    vector<int> check(int i, int j, string &s) {
        if (i == j) return {(s[i] - '0')};

        int hashed = hash(i, j);
        if (!dp.count(hashed)) {
            unordered_set<int> possible;
            for (int k = i; k <= j - 2; k += 2) {
                vector<int> res1 = check(i, k, s), res2 = check(k + 2, j, s);
                for (auto &val1 : res1) {
                    for (auto &val2 : res2) {
                        int val = s[k + 1] == '*' ? val1 * val2 : val1 + val2;
                        if (val <= Max) {
                            possible.insert(val);
                        }
                    }
                }
            }

            dp[hashed] = vector<int>(possible.begin(), possible.end());
        }
        return dp[hashed];
    }

    int scoreOfStudents(string s, vector<int>& answers) {
        dp.clear();
        Max = 1000;
        vector<int> possible_ans = check(0, s.length() - 1, s);
        unordered_set<int> can(possible_ans.begin(), possible_ans.end());
        int actual_ans = getValid(s);
        int return_val = 0;

        for (auto &val : answers) {
            if (val == actual_ans) {
                return_val += 5;
            } else if (can.count(val)) {
                return_val += 2;
            }
        }

        return return_val;
    }
};

int main() {
    Solution solution;
    string s = "2+3*4+5";
    vector<int> answers = {19,25,29,45};
    int score = solution.scoreOfStudents(s, answers);
    cout << "Score: " << score << endl;
    return 0;
}