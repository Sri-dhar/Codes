#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int width_global;
    vector<int> memo;
    vector<vector<int>> books_global;

    int helper(int idx)
    {
        if(idx == books_global.size()) return 0;
        if(memo[idx] != -1) return memo[idx];

        int returnVal;
        int maxi{}, width{};
        for(int i=idx; i<books_global.size() && (width+books_global[i][0]) <= width_global; i++){
            maxi = max(maxi, books_global[i][1]);
            width += books_global[i][0];
            returnVal = min(returnVal, helper(i+1));
        }

        return memo[idx] = returnVal;
    }

    int dp(vector<vector<int>> &books, int shelfWidth)
    {
        int n = books.size();
        vector<int> dp(n + 1, INT_MAX); 
        dp[0] = 0; 

        for (int i = 1; i <= n; ++i) {
            int width = 0, height = 0;

            for (int j = i; j > 0; --j) {
                width += books[j - 1][0];
                if (width > shelfWidth) break; 

                height = max(height, books[j - 1][1]); 
                dp[i] = min(dp[i], dp[j - 1] + height); 
            }
        }

        return dp[n];
    }

    int minHeightShelves(vector<vector<int>> &books, int shelfWidth)
    {
        return dp(books, shelfWidth);
    }
};