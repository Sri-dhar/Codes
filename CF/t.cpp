#include <bits/stdc++.h>
using namespace std;

class Node
{
    int x;
    int height;
    Node(int x, int height)
    {
        this->height = height;
        this->x = x;
    }

    int compare(Node a)
    {
        if (this->x != a.x)
        {
            return this->x - a.x;
        }
        return this->height - a.height;
    }
};

class Solution
{
public:
    vector<vector<int>> getSkyline(vector<vector<int>> &buildings)
    {
        vector<vector<int>> res;
        if(buildings.size() == 0) return res;
        
    }
};
