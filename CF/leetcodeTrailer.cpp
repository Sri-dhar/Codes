#include <bits/stdc++.h>
using namespace std;

auto init = []()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 'c';
}();

class Solution
{
public:
    bool isSimilar(string a, string b)
    {
        int n = a.size();
        int count = 0;
        for (int i = 0; i < n; i++)
        {
            if (a[i] != b[i])
            {
                count++;
            }
        }
        return count == 2;
    }

    int numSimilarGroups(vector<string> &strs)
    {
        int n = strs.size(); 
        vector<int> parent(n);
        iota(parent.begin(), parent.end(), 0);

        function<int(int)> find = [&](int x) {
            return parent[x] == x ? x : parent[x] = find(parent[x]);
        };

        auto unite = [&](int x, int y) {
            x = find(x);
            y = find(y);
            if (x != y)
            {
                parent[x] = y;
            }
        };

        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (isSimilar(strs[i], strs[j]))
                {
                    unite(i, j);
                }
            }
        }

        unordered_set<int> groups;
        for (int i = 0; i < n; i++)
        {
            groups.insert(find(i));
        }

        return groups.size();
    }
};

int main()
{
    Solution s;
    vector<string> strs = {"tars", "rats", "arts", "star"};
    cout << s.numSimilarGroups(strs) << endl;
    return 0;
}