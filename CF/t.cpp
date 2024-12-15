#include<bits/stdc++.h>
using namespace std;

class Solution
{
public:
    void buildAdjacencyList(string &parentWord, string &currWord, unordered_set<string> &wordSet, unordered_map<string, vector<string>> &adj, queue<string> &q, unordered_set<string> &visited)
    {
        for (auto i = 0; i < currWord.size(); i++)
        {
            char original = currWord[i];
            for (char ch = 'a'; ch <= 'z'; ch++)
            {
                if (ch == original)
                    continue;
                string newWord = currWord;
                newWord[i] = ch;
                if (wordSet.find(newWord) != wordSet.end())
                {
                    if (visited.find(newWord) == visited.end())
                    {
                        q.emplace(newWord);
                        visited.insert(newWord);
                    }
                    adj[newWord].emplace_back(parentWord);
                }
            }
        }
    }

    void findPaths(int level, string &currWord, vector<string> &ds, unordered_map<string, vector<string>> &adj, vector<vector<string>> &res)
    {
        if (level == 0)
        {
            res.emplace_back(ds);
            return;
        }
        for (auto &word : adj[currWord])
        {
            ds[level - 1] = word;
            findPaths(level - 1, word, ds, adj, res);
        }
    }

    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &wordList)
    {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        if (wordSet.find(endWord) == wordSet.end())
            return {};

        queue<string> q;
        q.emplace(beginWord);
        wordSet.erase(beginWord);

        int level = 1;
        vector<vector<string>> res;
        unordered_map<string, vector<string>> adj;

        while (!q.empty())
        {
            int sz = q.size();
            unordered_set<string> visited;

            for (int i = 0; i < sz; i++)
            {
                string parentWord = q.front();
                q.pop();

                if (parentWord == endWord)
                {
                    vector<string> ds(level);
                    ds[level - 1] = endWord;
                    findPaths(level - 1, parentWord, ds, adj, res);
                    return res;
                }

                buildAdjacencyList(parentWord, parentWord, wordSet, adj, q, visited);
            }
            level++;
            for (auto &word : visited)
                wordSet.erase(word);
        }

        return res;
    }
};